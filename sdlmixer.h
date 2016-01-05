#ifndef SDLMIXER_H
#define SDLMIXER_H

#include "wavfile.h"

#include <SDL2/SDL_mixer.h>

class GLWidget;

namespace SdlMixer
{
    void init(GLWidget *widget);
    void cleanup();

    WavFile &shoot();
    WavFile &pop();
};

#endif // SDLMIXER_H
