#include "Enemy.h"
#include "Camera.h"
#include "CollisionHandler.h"
#include "TextureManager.h"

Enemy::Enemy(Properties* props): Character(props){
    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(3.5f);

    m_Collider = new Collider();
    m_Collider->SetBuffer(-25, -20, 10, 0);


    m_Animation = new SpriteAnimation();
    m_Animation->SetProps(m_TextureID, 1, 5, 80);
}

void Enemy::Draw(){
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, 1.8, 1.8, m_Flip=SDL_FLIP_HORIZONTAL);
    /// test
//    Vector2D cam = Camera::GetInstance()->GetPosition();
//    SDL_Rect box = m_Collider->Get();
//    box.x -= cam.X;
//    box.y -= cam.Y;
//    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}

void Enemy::Update(float dt){

    /// X-Axis movements
    m_RigidBody->Update(dt);
    m_LastSafePosition.X = m_Transform->X;
    m_Transform->X += m_RigidBody->Position().X;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 38, 30);
    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
        m_Transform->X = m_LastSafePosition.X;
    }
    /// Y-Axis movements
    m_RigidBody->Update(dt);
    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->Y += m_RigidBody->Position().Y;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 38, 30);
    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
        m_Transform->Y = m_LastSafePosition.Y;
    }

    m_Animation->Update(dt);
}

void Enemy::Clean(){
    TextureManager::GetInstance()->Drop(m_TextureID);
}

