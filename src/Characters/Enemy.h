#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include "Character.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Vector2D.h"
#include "SpriteAnimation.h"

class Enemy: public Character {
    public:
        Enemy(Properties* props);

        virtual void Draw();
        virtual void Clean();
        virtual void Update(float dt);

    private:
        Collider* m_Collider;
        RigidBody* m_RigidBody;
        SpriteAnimation* m_Animation;
        Vector2D m_LastSafePosition;
};

#endif // ENEMY_H
