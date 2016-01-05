#include "wavfile.h"

#include <QFile>

#include <iostream>

WavFile::WavFile(const QString &fileName)
{
    QFile file(":/sounds/" + fileName + ".wav");
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    SDL_RWops *rwops = SDL_RWFromConstMem(data.data(), data.size());
    sound = Mix_LoadWAV_RW(rwops, 1);
}

void WavFile::play()
{
    //int channel = Mix_PlayChannel(-1, sound, 0);
    Mix_PlayChannel(-1, sound, 0);

    //while(Mix_Playing(channel) != 0);
    //Mix_FreeChunk(sound);r
}
