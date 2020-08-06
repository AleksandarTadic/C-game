#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "SDL.h"
#include <vector>
#include "TileLayer.h"
#include "GameMap.h"
#include "Engine.h"

class CollisionHandler{
    public:
        bool CheckCollision(SDL_Rect a, SDL_Rect b);
        bool MapCollision(SDL_Rect a);
        inline static CollisionHandler* GetInstance(){return s_Instance = (s_Instance != nullptr)? s_Instance : new CollisionHandler();}

        int GetRowCount(){return m_RowCount;}
        int GetColCount(){return m_ColCount;}
        int GetTileSize(){return m_TileSize;}

    private:
        CollisionHandler(){};
        TileMap m_CollisionTilemap;
        TileLayer* m_CollisionLayer;
        static CollisionHandler* s_Instance;
        int m_TileSize, m_RowCount, m_ColCount;
};

#endif // COLLISIONHANDLER_H
