#include "Animation.h"

Animable::Animable()
{

}
Animable::~Animable()
{

}

void Animable::addAnimation(shared_ptr<Animation> anim) {
    animFrames.push_back(anim);
}

//AQUEST NO S'UTILITZA
void Animable::update(int nframe) {

    bool trobat = false;
    int i;
    for (i = 0; i<animFrames[animFrames.size()-1]->frameFinal && !trobat; i++)
        trobat = animFrames[i]->frameFinal>=nframe;

    aplicaTG(animFrames[i-1]->transf);
}

//ANIMACIONS VIRTUALWORLD
void Animable::applyAnimations(int nframe){
    for(unsigned long i = 0; i<animations.size(); i++){
        applyAnimation(animations[i], nframe);
    }
}
