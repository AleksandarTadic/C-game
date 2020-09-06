#include "Warrior.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Input.h"
#include "Camera.h"
#include "CollisionHandler.h"

#include "GameMap.h"
#include "MapParser.h"

Warrior::Warrior(Properties* props): Character(props) {
    m_IsRunning = false;
    m_IsJumping = false;
    m_IsFalling = false;
    m_IsGrounded = false;
    m_IsAttacking = false;
    m_IsCrouching = false;

    m_Flip = SDL_FLIP_NONE;
    m_JumpTime = JUMP_TIME;
    m_JumpForce = JUMP_FORCE;
    m_AttackTime = ATTACK_TIME;

    m_Collider = new Collider();
    m_Collider->SetBuffer(0,0,0,0);

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(5.1f);

    m_Animation = new SpriteAnimation(true);
    m_Animation->SetProps(m_TextureID, 2, 8, 100);
}

void Warrior::Draw() {
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height,1, 1, m_Flip);

    ///  box test collision
//    Vector2D cam = Camera::GetInstance()->GetPosition();
//    SDL_Rect box = m_Collider->Get();
//    box.x -= cam.X;
//    box.y -= cam.Y;
//    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}

void Warrior::Update(float dt) {
    m_IsRunning = false;
    m_IsCrouching = false;
    m_RigidBody->UnSetForce();

    Camera::GetInstance()->setMapWidthHeight(CollisionHandler::GetInstance()->GetColCount()*CollisionHandler::GetInstance()->GetTileSize(), CollisionHandler::GetInstance()->GetRowCount()*CollisionHandler::GetInstance()->GetTileSize());

    /// Run Forward
    if(Input::GetInstance()->GetAxisKey(HORIZONTAL) == FORWARD && !m_IsAttacking) {
        /// Player cant exit map on end
        if(m_Origin->X < CollisionHandler::GetInstance()->GetColCount()*CollisionHandler::GetInstance()->GetTileSize()-m_Collider->Get().w) {
            m_RigidBody->ApplyForceX(FORWARD*RUN_FORCE);
            m_Flip = SDL_FLIP_NONE;
            m_IsRunning = true;
        }
    }
    /// Run Backward
    if(Input::GetInstance()->GetAxisKey(HORIZONTAL) == BACKWARD && !m_IsAttacking) {
        /// Player cant exit map on start
        if(m_Origin->X > 0+m_Collider->Get().w) {
            m_RigidBody->ApplyForceX(BACKWARD*RUN_FORCE);
            m_Flip = SDL_FLIP_HORIZONTAL;
            m_IsRunning = true;
        }
    }
//    /// s
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S)) {
        m_RigidBody->UnSetForce();
        m_IsCrouching = true;
    }
    /// Attack
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_K)) {
        m_RigidBody->UnSetForce();
        m_IsAttacking = true;
    }
    /// Jump
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && m_IsGrounded){
        ///player cant jump in air
        if(!m_IsJumping) {
            m_IsJumping = true;
            m_IsGrounded = false;
            m_RigidBody->ApplyForceY(UPWARD*m_JumpForce);
        }
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && m_IsJumping && m_JumpTime > 0){
        m_JumpTime -= dt;
        m_RigidBody->ApplyForceY(UPWARD*m_JumpForce);

    } else {
        m_IsJumping = false;
        m_JumpTime = JUMP_TIME;
    }

    /// move on x axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.X = m_Transform->X;
    m_Transform->X += m_RigidBody->Position().X;
    m_Collider->Set(m_Transform->X+34, m_Transform->Y+14, 28, 48);

    if(CollisionHandler::GetInstance()->MapCollision((m_Collider->Get()))) {
        m_Transform->X = m_LastSafePosition.X;
    }

    /// move on y axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->Y += m_RigidBody->Position().Y;
    m_Collider->Set(m_Transform->X+34, m_Transform->Y+14, 28, 48);

    if(CollisionHandler::GetInstance()->MapCollision((m_Collider->Get()))) {
        m_IsGrounded = true;
        m_Transform->Y = m_LastSafePosition.Y;
    } else {
        m_IsGrounded = false;
    }

    /// Fall
    if(m_RigidBody->Velocity().Y > 0 && !m_IsGrounded) {
        m_IsFalling = true;
    } else {
        m_IsFalling = false;
    }

    /// Attack Timer
    if(m_IsAttacking && m_AttackTime > 0) {
        m_AttackTime -= dt;
    } else {
        m_IsAttacking = false;
        m_AttackTime = ATTACK_TIME;
    }

    if(m_Origin->Y+(m_Width / 2) > CollisionHandler::GetInstance()->GetRowCount()*CollisionHandler::GetInstance()->GetTileSize()) {
        m_Transform->X = 30;
        m_Transform->Y = 380;
        cout << "Player out of map!" << endl;
    }

    if(m_Origin->X > CollisionHandler::GetInstance()->GetColCount()*CollisionHandler::GetInstance()->GetTileSize()-m_Collider->Get().w && m_Origin->X < CollisionHandler::GetInstance()->GetColCount()*CollisionHandler::GetInstance()->GetTileSize()) {
        Engine::GetInstance()->LoadMap(MapParser::GetInstance()->GetNextMap());
        m_Transform->X = 30;
        m_Transform->Y = 380;
    }

    m_Origin->X = m_Transform->X + m_Width/2;
    m_Origin->Y = m_Transform->Y + m_Height/2;
    AnimationState();
    m_Animation->Update(dt);

}

void Warrior::AnimationState(){
    m_Animation->SetProps(m_TextureID, 1, 5, 100);

    if(m_IsRunning) {
        m_Animation->SetProps(m_TextureID, 2, 8, 100);
    }

    if(m_IsCrouching) {
        m_Animation->SetProps(m_TextureID, 6, 6, 100);
    }

    if(m_IsJumping) {
        m_Animation->SetProps(m_TextureID, 2, 2, 100);
    }

    if(m_IsFalling) {
        m_Animation->SetProps(m_TextureID, 9, 3, 100);
    }

    if(m_IsAttacking) {
        m_Animation->SetProps(m_TextureID, 4, 9, 100);
    }
}

void Warrior::Clean() {
    TextureManager::GetInstance()->Drop(m_TextureID);
}
