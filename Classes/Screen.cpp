#include "Screen.h"
#include <iostream>
#include <cstring>
#include <SDL2/SDL.h>

using namespace std;

namespace first {

    Screen::Screen() :
            m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer(NULL), m_buffer2(NULL) {
    };

    bool Screen::init() {

     /*
     * SDL_Init : To begin using SDL in your program SDL_Init() must be called before most other SDL functions.
     * The role of SDL_Init() is to properly initialize the SDL library and start each of the various
     * subsystems requested as part of the call.
     * SDL_Quit : Closes all the subsystem and Quits
     * SDL_GetError : returns the error code for the situation
     */

        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            //In this case the SDL_Init fails
            return false;
        }

        // Create an application window with the following settings
        m_window = SDL_CreateWindow(
                "Particle Fire Explosion",              // Window title
                SDL_WINDOWPOS_UNDEFINED,                // Initial X position
                SDL_WINDOWPOS_UNDEFINED,                // Initial Y position
                SCREEN_WIDTH,                           // Width in pixels
                SCREEN_HEIGHT,                         // Height in pixeld
                SDL_WINDOW_SHOWN                       // A SDL_Window Flag
        );

        // Check that the window was successfully created
        if (m_window == NULL) {
            // In the case that the window could not be made...
            return false;

        }

        m_renderer = SDL_CreateRenderer(
                m_window,                 // The window where rendering is to be done
                -1,                       // The index of the rendering driver to initialize, or -1 to
                                          // initialize the first one supporting the requested flags
                SDL_RENDERER_PRESENTVSYNC // Present is synchronized with the refresh rate
        );

        if (m_renderer == NULL) {
         // In the case that the renderer could not be created...
            return false;
        }

        m_texture = SDL_CreateTexture(
                m_renderer,                                     // The rendering context
                SDL_PIXELFORMAT_RGBA8888,                       // Format, In this case we have on 4 byte for each pixel
         /*
          * SDL_PIXELFORMAT_RGBA8888 : Consist of three bytes for colour information
          * Each byte have a shade of the colour red green blue respectively (0 to 255)
          * The fourth byte is for transparency
          */

                SDL_TEXTUREACCESS_STATIC,                        // *The Way to write the pixels
                SCREEN_WIDTH,                                    // Screen Width
                SCREEN_HEIGHT                                    // Screen Height
        );

        if (m_texture == NULL) {
            return false;
        }

        // A Block of memory we will use to update the texture
        m_buffer = new Uint32[SCREEN_WIDTH *
                              SCREEN_HEIGHT]; // An array for each pixel .. return NULL for error

        m_buffer2 = new Uint32[SCREEN_WIDTH *
                               SCREEN_HEIGHT];

        memset(
                m_buffer,                                         // buffer whose memory has to be set
                0,                                                // Set each memory to the passes argument
                SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32)     // Total data (in bytes)
        );

        memset(
                m_buffer2,                                       // buffer whose memory has to be set
                90,                                              // Set each memory to the passes argument
                SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32)    // Total data (in bytes)
        );

        return true;

    };

    void Screen::update() {

        SDL_UpdateTexture(
                m_texture,                    // The texture to update
                NULL,                         // A pointer to the rectangle of pixels to update, NULL to update all
                m_buffer,                     // The row of pixel data
                SCREEN_WIDTH * sizeof(Uint32) // No of bytes between the pixel data
        );

        SDL_RenderClear(m_renderer); // Clears the renderer

        // copy's the texture to the renderer
        SDL_RenderCopy(
                m_renderer,                   // The Renderer Which should copy the texture
                m_texture,                    // The texture which will be copied into the renderer
                NULL,                         // Pointer to source rectangle of pixels, NULL for all
                NULL                          // Pointer to destination rectangle of pixels, NULL for all
        );

        // Present the renderer to the window
        SDL_RenderPresent(m_renderer);

    }

    void Screen::boxBlur() {
        // Swap the buffers, so pixel is in m_buffer2 and we are drawing to m_buffer.
        Uint32 *temp = m_buffer;
        m_buffer = m_buffer2;
        m_buffer2 = temp;

        for (int y = 0; y < SCREEN_HEIGHT; ++y) {
            for (int x = 0; x < SCREEN_WIDTH; ++x) {

                /*
                 * 0 0 0
                 * 0 1 0 plot the average colour value back into these pixels
                 * 0 0 0
                 */

                int redTotal = 0;
                int greenTotal = 0;
                int blueTotal = 0;

                for (int row = -1; row <= 1; ++row) {
                    for (int col = -1; col <= 1; ++col) {
                        int CURRENTy = y + row;
                        int CURRENTx = x + col;

                        if (CURRENTx >= 0 && CURRENTx < SCREEN_WIDTH && CURRENTy >= 0 && CURRENTy < SCREEN_HEIGHT) {

                            Uint32 color = m_buffer2[CURRENTy * SCREEN_WIDTH + CURRENTx];

                            Uint8 red = color >> 24;
                            Uint8 green = color >> 16;
                            Uint8 blue = color >> 8;

                            redTotal += red;
                            greenTotal += green;
                            blueTotal += blue;
                        }
                    }
                }

                Uint8 red = redTotal / 9;
                Uint8 green = greenTotal / 9;
                Uint8 blue = blueTotal / 9;

                setPixel(x, y, red, green, blue);

            }
        }

    }

    void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {

        if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
            return;
        }

        Uint32 color = 0;                               // An unsigned int of 32 bytes

        color += red;
        color <<= 8;                                    // shift 8 bits to the left
        color += green;
        color <<= 8;
        color += blue;
        color <<= 8;
        color += 0xFF;

        m_buffer[(y * SCREEN_WIDTH) +
                 x] = color;

    }

    bool Screen::processEvent() {

        while (SDL_PollEvent(
                &m_event)) {                              // SDL_PollEvent(&event) : Return 1 if events are pending otherwise return 0
            if (m_event.type == SDL_QUIT) {
                // In this case the event is of quiting the window then jump out the loop
                return false;
            }
        }
        return true;

    };

    void Screen::close() {

        // Deallocate the resources assigned to *objects
        delete[] m_buffer;
        delete[] m_buffer2;
        SDL_DestroyTexture(m_texture); // Destroy's the texture
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }
}