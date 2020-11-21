//
// Created by Rupanshu on 16-11-2017.
//

#ifndef PARTICLE_FIRE_EXPLOSION_SCREEN_H
#define PARTICLE_FIRE_EXPLOSION_SCREEN_H
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

namespace first {

    class Screen {

    public:
        const static int SCREEN_WIDTH = 800;
        const static int SCREEN_HEIGHT = 600;

    private:
        SDL_Window *m_window;
        SDL_Renderer *m_renderer;
        SDL_Texture *m_texture;
        Uint32 *m_buffer;
        Uint32 *m_buffer2;
        SDL_Event m_event;

    public:
        Screen();
        bool init();
        void update();
        void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
        void boxBlur();
        bool processEvent();
        void close();
    };
}


#endif //PARTICLE_FIRE_EXPLOSION_SCREEN_H
