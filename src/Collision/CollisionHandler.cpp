#include "CollisionHandler.h"
#include "Engine.h"

CollisionHandler* CollisionHandler::s_Instance = nullptr;

void CollisionHandler::SetCollisionMap(TileMap tilemap, int tilesize){
    m_CollisionTilemap = tilemap;
    m_TileSize = tilesize;
    m_RowCount = tilemap.size();
    m_ColCount = tilemap[0].size();
}

bool CollisionHandler::CheckCollision(SDL_Rect a, SDL_Rect b){
    bool x_overlaps = (a.x < b.x + b.w) && (a.x + a.w > b.x);
    bool y_overlaps = (a.y < b.y + b.h) && (a.y + a.h > b.y);
    return (x_overlaps && y_overlaps);
}

bool CollisionHandler::MapCollision(SDL_Rect a){

    m_CollisionLayer = (TileLayer*)Engine::GetInstance()->GetMap()->GetMapLayers().front();
    m_CollisionTilemap = m_CollisionLayer->GetTilemap();
    m_TileSize = m_CollisionLayer->GetTileSize();
    m_RowCount = m_CollisionLayer->GetRowCount();
    m_ColCount = m_CollisionLayer->GetColCount();

    int left_tile = a.x/m_TileSize;
    int right_tile = (a.x + a.w)/m_TileSize;

    int top_tile = a.y/m_TileSize;
    int bottom_tile = (a.y + a.h)/m_TileSize;
    if(left_tile < 0) {
        left_tile = 0;
    }

    if(right_tile > m_ColCount) {
        right_tile = m_ColCount;
    }

    if(top_tile < 0) {
        top_tile = 0;
    }

    if(bottom_tile > m_RowCount) {
        bottom_tile = m_RowCount;
    }

    for(int i = left_tile; i <= right_tile; ++i) {
        for(int j = top_tile; j <= bottom_tile; ++j) {
            if(m_CollisionTilemap[j][i] > 0) {
                return true;
            }
        }
    }
    return false;
}
