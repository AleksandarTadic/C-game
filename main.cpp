#include "Engine.h"
#include "Timer.h"
//using namespace std;

int main(int argc, char** argv){

    Engine::GetInstance()->Init();

    while(Engine::GetInstance()->isRunning()) {
        Engine::GetInstance()->Events();
        Engine::GetInstance()->Update();
        Engine::GetInstance()->Render();
        Timer::GetInstance()->Tick();
    }
    Engine::GetInstance()->Clean();
    return 0;
}
