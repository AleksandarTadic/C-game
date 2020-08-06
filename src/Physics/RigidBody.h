#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Vector2D.h"

#define UNIT_MASS 1.0f
#define GRAVITY 9.8f

#define FORWARD 1
#define BACKWARD -1

#define UPWARD -1
#define DOWNWARD 1


class RigidBody {
    public:
        RigidBody() {
            m_Mass = UNIT_MASS;
            m_Gravity = GRAVITY;
        }

        /// Setter Gravity and Mass
        inline void SetMass(float mass){m_Mass = mass;}
        inline void SetGravity(float gravity){m_Gravity = gravity;}

        /// Force
        inline void ApplyForce(Vector2D F) {m_Force = F;}
        inline void ApplyForceX(float Fx){m_Force.X = Fx;}
        inline void ApplyForceY(float Fy){m_Force.Y = Fy;}
        inline void UnSetForce(){m_Force = Vector2D(0, 0);}

        ///Friction
        inline void ApplyFriction(Vector2D Fr){m_Friction = Fr;}
        inline void UnSetFriction(){m_Friction = Vector2D(0, 0);}

        /// Getters
        inline float getMass(){return m_Mass;}
        inline Vector2D Position(){return m_Position;}
        inline Vector2D Velocity(){return m_Velocity;}
        inline Vector2D Acceleration(){return m_Accelaration;}

        /// update
        void Update(float dt){
            m_Accelaration.X = (m_Force.X + m_Friction.X)/m_Mass;
            m_Accelaration.Y = m_Gravity + m_Force.Y/m_Mass;
            m_Velocity.X = m_Accelaration.X*dt;
            m_Velocity.Y = m_Accelaration.Y*dt;
            m_Position.X = m_Velocity.X*dt;
            m_Position.Y = m_Velocity.Y*dt;
        }

    private:
        float m_Mass;
        float m_Gravity;

        Vector2D m_Force;
        Vector2D m_Friction;

        Vector2D m_Position;
        Vector2D m_Velocity;
        Vector2D m_Accelaration;

};

#endif // RIGIDBODY_H
