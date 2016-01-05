#include "sdlmixer.h"
#include "glwidget.h"

#include <iostream>

#include <SDL2/SDL.h>

using namespace std;

namespace SdlMixer
{
    WavFile *_shoot;
    WavFile *_pop;

    void initSdl(GLWidget *widget);
    void openAudio(GLWidget *widget);
    void loadFiles(GLWidget *widget);
}

void SdlMixer::init(GLWidget *widget)
{
    initSdl(widget);
    openAudio(widget);
    loadFiles(widget);
}

void SdlMixer::initSdl(GLWidget *widget)
{
    if(!SDL_Init(SDL_INIT_AUDIO)) return;
    cerr << "Unable to initialize SDL\n";
    widget->close();
}

void SdlMixer::openAudio(GLWidget *widget)
{
    int audio_rate = 44100;
    Uint16 audio_format = AUDIO_S16LSB;
    int audio_channels = 1;
    int audio_buffers = 4096;

    if(!Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)) return;
    cerr << "Unable to initialize audio\n";
    widget->close();
}

void SdlMixer::loadFiles(GLWidget *widget)
{
    _shoot = new WavFile("shoot");
    _pop = new WavFile("pop");

    if(_shoot->loaded() && _pop->loaded()) return;
    cerr << "Failed to load file\n";
    widget->close();
}

void SdlMixer::cleanup()
{
    Mix_CloseAudio();
    SDL_Quit();
}

WavFile &SdlMixer::shoot() { return *_shoot; }
WavFile &SdlMixer::pop() { return *_pop; }




















