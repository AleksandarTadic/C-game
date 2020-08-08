#include "MapParser.h"

MapParser* MapParser::s_Instance = nullptr;

bool MapParser::Load() {
    if(!Parse("MAP", "assets/maps/mapa.tmx")){
        return false;
    }
    if(!Parse("MAP2", "assets/maps/mapa2.tmx")){
        return false;
    }
    if(!Parse("MAP3", "assets/maps/mapa3.tmx")){
        return false;
    }
    return true;
}

bool MapParser::Parse(string id, string source){
    TiXmlDocument xml;
    xml.LoadFile(source);

    if(xml.Error()) {
        cerr << "Failed to load: " << source << endl;
        return false;
    }

    TiXmlElement* root = xml.RootElement();
    int rowcount, colcount, tilesize = 0;
    root->Attribute("width", &colcount);
    root->Attribute("height", &rowcount);
    root->Attribute("tilewidth", &tilesize);

    TileSetList tilesets;
    for(TiXmlElement* e=root->FirstChildElement(); e!= nullptr; e=e->NextSiblingElement()){
        if(e->Value() == string("tileset")) {
            tilesets.push_back(ParseTileset(e));
        }
    }

    GameMap* gamemap = new GameMap();
    for(TiXmlElement* e=root->FirstChildElement(); e!= nullptr; e=e->NextSiblingElement()){
        if(e->Value() == string("layer")){
            TileLayer* tilelayer = ParseTileLayer(e, tilesets, tilesize, rowcount, colcount);
            gamemap->m_MapLayers.push_back(tilelayer);
        }
    }
    m_MapDict[id] = gamemap;
    return true;
}

TileSet MapParser::ParseTileset(TiXmlElement* xmlTileset) {
    TileSet tileset;
    tileset.Name = xmlTileset->Attribute("name");
    xmlTileset->Attribute("firstgid", &tileset.FirstID);
    xmlTileset->Attribute("tilecount", &tileset.TileCount);
    tileset.LastID = (tileset.FirstID + tileset.TileCount) - 1;

    xmlTileset->Attribute("columns", &tileset.ColCount);
    tileset.RowCount = tileset.TileCount/tileset.ColCount;
    xmlTileset->Attribute("tilewidth", &tileset.TileSize);

    TiXmlElement* image = xmlTileset->FirstChildElement();
    tileset.Source = image->Attribute("source");
    return tileset;
}

TileLayer* MapParser::ParseTileLayer(TiXmlElement* xmlLayer, TileSetList tilesets, int tilesize, int rowcount, int colcount){
    TiXmlElement* data;
    for(TiXmlElement* e = xmlLayer->FirstChildElement(); e != nullptr; e=e->NextSiblingElement()){
        if(e->Value() == string("data")){
            data = e;
            break;
        }
    }
    /// Parse Layer tile map
    string matrix(data->GetText());
    istringstream iss(matrix);
    string id;

    TileMap tilemap(rowcount, vector<int>(colcount, 0));

    for(int row = 0; row < rowcount; row++){
        for(int col = 0; col < colcount; col++){
            getline(iss, id, ',');
            stringstream convertor(id);
            convertor >> tilemap[row][col];

            if(!iss.good()){
                break;
            }
        }
    }
    return (new TileLayer(tilesize, colcount, rowcount, tilemap, tilesets));
}

void MapParser::Clean(){
    map<string, GameMap*>::iterator it;
    for(it = m_MapDict.begin(); it != m_MapDict.end(); it++){
        it->second = nullptr;
    }
    m_MapDict.clear();
}

string MapParser::GetNextMap(){
    vector <string> MapNames;
    map<string, GameMap*>::iterator it;
    for(it = m_MapDict.begin(); it != m_MapDict.end(); it++){
        MapNames.push_back(it->first);
    }
    if(m_MapCounter+1 != MapNames.size()) {
        m_MapCounter++;
    } else {
        m_MapCounter = 0;
    }
    return MapNames[m_MapCounter];
}




