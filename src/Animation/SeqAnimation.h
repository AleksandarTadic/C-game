#ifndef SEQANIMATION_H
#define SEQANIMATION_H

#include "map"
#include <string>
#include <vector>
#include "SDL.h"
#include "Animation.h"

using namespace std;

struct Sequence {
    int Speed;
    int FrameCount;
    int Width, Height;
    vector<string> TextureIDs;
};

class SeqAnimation: public Animation {
    public:
        SeqAnimation(bool repeat = true);

        virtual void Update(float dt);
        void Parse(string source);
        void SetCurrentSeq(string seqID);
        void SetRepeat(bool repeat){m_Repeat = repeat;}
        void Draw(float x, float y, float scaleX=1, float scaleY=1, SDL_RendererFlip flip = SDL_FLIP_NONE);

    private:
        Sequence m_CurrentSeq;
        map<string, Sequence> m_SeqMap;

};

#endif // SEQANIMATION_H
