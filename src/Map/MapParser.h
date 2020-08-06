#ifndef MAPPARSER_H
#define MAPPARSER_H

#include <map>
#include <string>
#include "GameMap.h"
#include "TileLayer.h"
#include "tinyxml.h"


using namespace std;

class MapParser {
    public:
        bool Load();
        void Clean();

        inline GameMap* GetMap(string id){return m_MapDict[id];}
        inline static MapParser* GetInstance(){return s_Instance = (s_Instance != nullptr)? s_Instance : new MapParser();}
    private:
        bool Parse(string id, string source);
        TileSet ParseTileset(TiXmlElement* xmlTileset);
        TileLayer* ParseTileLayer(TiXmlElement* xmlLayer, TileSetList tilesets, int tilesize, int rowcount, int colcount);

    private:
        MapParser(){};
        static MapParser* s_Instance;
        map<string, GameMap*> m_MapDict;
};

#endif // MAPPARSER_H
