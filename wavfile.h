#ifndef WAVSOUND_H
#define WAVSOUND_H

#include <SDL2/SDL_mixer.h>

class QString;

class WavFile
{
public:
    WavFile(const QString &fileName);

    bool loaded() { return sound != 0; }

    void play();

private:
    Mix_Chunk *sound;
};

#endif // WAVSOUND_H
