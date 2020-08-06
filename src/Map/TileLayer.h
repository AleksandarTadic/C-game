#ifndef TILELAYER_H
#define TILELAYER_H
#include <iostream>
#include "Layer.h"
#include <string>
#include <vector>

using namespace std;

struct TileSet{
    int FirstID, LastID;
    int RowCount, ColCount;
    int TileCount, TileSize;
    string Name, Source;
};

using TileSetList = vector<TileSet>;
using TileMap = vector<vector<int> >;

class TileLayer : public Layer {
    public:
        TileLayer(int tilesize, int colcount, int rowcount, TileMap tilemap, TileSetList tilesets);
        virtual void Render();
        virtual void Update();
        inline  TileMap GetTilemap(){return m_Tilemap;}
        int GetRowCount(){return m_RowCount;}
        int GetColCount(){return m_ColCount;}
        int GetTileSize(){return m_TileSize;}

    private:
        int m_TileSize;
        int m_RowCount, m_ColCount;
        TileMap m_Tilemap;
        TileSetList m_Tilesets;
};

#endif // TILELAYER_H
