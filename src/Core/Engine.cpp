#include "Engine.h"
#include "TextureManager.h"
#include "Input.h"
#include "SDL.h"
#include "Timer.h"
#include "MapParser.h"


#include "Warrior.h"
#include "Enemy.h"
#include "Camera.h"


Engine* Engine::s_Instance = nullptr;

bool Engine::Init(){
    if(SDL_Init(SDL_INIT_VIDEO)!=0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)!=0) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    m_Window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);
    if(m_Window == nullptr) {
        SDL_Log("Failed to create Window: %s", SDL_GetError());
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(m_Renderer == nullptr) {
        SDL_Log("Failed to create Renderer: %s", SDL_GetError());
        return false;
    }

    if(!MapParser::GetInstance()->Load()) {
        cout << "Failed to load map" << endl;
    }

//    m_levelMap = MapParser::GetInstance()->GetMap("MAP");

    m_levelMap = MapParser::GetInstance()->GetMap("MAP2");


    TextureManager::GetInstance()->ParseTextures("assets/textures.tml");
    /// ili
//    TextureManager::getInstance()->Load("background", "assets/images/bg3.jpg");
//    TextureManager::getInstance()->Load("player", "assets/minotaur.png");

    Warrior* player = new Warrior(new Properties("player", 30, 380, 96, 96));
    Enemy* dwarf = new Enemy(new Properties("dwarf", 620, 300, 38, 30));
    m_GameObjects.push_back(player);
    m_GameObjects.push_back(dwarf);

    Camera::GetInstance()->SetTarget(player->GetOrigin());
    return m_IsRunning = true;
}

bool Engine::Clean(){
    for(unsigned int i = 0; i < m_GameObjects.size(); i++) {
        m_GameObjects[i]->Clean();
    }
    TextureManager::GetInstance()->Clean();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    SDL_Quit();
}

void Engine::Quit(){
    m_IsRunning = false;
}

void Engine::Update(){
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_P)) {
        m_Paused = !m_Paused;
        SDL_Delay(200);
    }

    if(m_Paused == false) {
        float dt = Timer::GetInstance()->GetDeltaTime();
        m_levelMap->Update();
        for(unsigned int i = 0; i < m_GameObjects.size(); i++) {
            m_GameObjects[i]->Update(dt);
        }
        Camera::GetInstance()->Update(dt);
    }
//
//    int w, h;
//    SDL_GetRendererOutputSize(m_Renderer, &w, &h);
//    cout << w << " = " << h << endl;

}

void Engine::Render(){
    SDL_SetRenderDrawColor(m_Renderer, 124, 218, 254, 255);
    SDL_RenderClear(m_Renderer);

    TextureManager::GetInstance()->Draw("background1", 0, 0, 3840, 1080, 1, 0.8, 0.6);
    m_levelMap->Render();
//    player->Draw();
    for(unsigned int i = 0; i < m_GameObjects.size(); i++) {
        m_GameObjects[i]->Draw();
    }
    SDL_RenderPresent(m_Renderer);

}

void Engine::Events(){
    Input::GetInstance()->Listen();
}
