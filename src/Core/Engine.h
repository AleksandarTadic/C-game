#ifndef ENGINE_H
#define ENGINE_H
#include <iostream>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"
#include "GameMap.h"
#include "GameObject.h"
#include "MapParser.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 640

using namespace std;

class Engine {

    public:
        static Engine* GetInstance(){
            return s_Instance = (s_Instance != nullptr)? s_Instance : new Engine();
        }
        bool Init();
        bool Clean();
        void Quit();

        void Update();
        void Render();
        void Events();

        inline GameMap* GetMap(){return m_levelMap;}
        inline bool isRunning(){return m_IsRunning;}
        inline SDL_Renderer* GetRenderer(){return m_Renderer;}
        inline GameMap* LoadMap(string newMap){return m_levelMap = MapParser::GetInstance()->GetMap(newMap);}
    private:
        Engine(){}
        bool m_IsRunning;

        GameMap* m_levelMap;
        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
        static Engine* s_Instance;
        vector<GameObject*> m_GameObjects;

        bool m_Paused = false;
};

#endif // ENGINE_H
