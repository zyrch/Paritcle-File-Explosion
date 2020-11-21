//
// Created by Rupanshu on 16-11-2017.
//

#include <iostream>

#define SDL_MAIN_HANDLED

#include "include/SDL2/SDL.h"


using namespace std;

int main() {

    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;

    /*
     * SDL_Init : To begin using SDL in your program SDL_Init() must be called before most other SDL functions.
     *            The role of SDL_Init() is to properly initialize the SDL library and start each of the various
     *            subsystems requested as part of the call.
     * SDL_Quit : Closes all the subsystem and Quits
     * SDL_GetError : returns the error code for the situation
     */

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        //In this case the SDL_Init fails
        cout << "SDL init failed." << flush;
        cout << SDL_GetError() << endl;            // returns the error code
    }


    // Create an application window with the following settings
    SDL_Window *window = SDL_CreateWindow(
            "Particle Fire Explosion",                    // Window title
            SDL_WINDOWPOS_UNDEFINED,                      // Initial X position
            SDL_WINDOWPOS_UNDEFINED,                      // Initial Y position
            SCREEN_WIDTH,                                 // Width in pixels
            SCREEN_HEIGHT,                                // Height in pixeld
            SDL_WINDOW_SHOWN                              // A SDL_Window Flag
    );

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        cout << "Could not create a window ." << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(
            window,                                       // The window where rendering is to be done
            -1,                                           // The index of the rendering driver to initialize, or -1 to
            // initialize the first one supporting the requested flags
            SDL_RENDERER_PRESENTVSYNC                     // Present is synchronized with the refresh rate
    );

    if (renderer == NULL) {
        // In the case that the renderer could not be created...
        cout << "Could not create a renderer " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);                        // Destroy's the window
        SDL_Quit();
        return 2;
    }

    SDL_Texture *texture = SDL_CreateTexture(
            renderer,                                     // The rendering context
            SDL_PIXELFORMAT_RGBA8888,                     // Format, In this case we have on 4 byte for each pixel
            /*
             * SDL_PIXELFORMAT_RGBA8888 : Consist of three bytes for colour information
             * Each byte have a shade of the colour red green blue respectively (0 to 255)
             * The fourth byte is for transparency
             */
            SDL_TEXTUREACCESS_STATIC,                     // *The Way to write the pixels
            SCREEN_WIDTH,                                 // Screen Width
            SCREEN_HEIGHT                                 // Screen Height
    );

    if (texture == NULL) {
        // In the case that the textrue could not be created...
        cout << "Could not create a texture " << SDL_GetError() << endl;
        SDL_DestroyRenderer(renderer);                    // Destroy's the renderer
        SDL_DestroyWindow(window);                        // Destroy's the window
        SDL_Quit();
        return 3;
    }

    // A Block of memory we will use to update the texture
    Uint32 *buffer = new Uint32[SCREEN_WIDTH *
                                SCREEN_HEIGHT];           // An array for each pixel .. return NULL for error

    memset(
            buffer,                                       // buffer whose memory has to be set
            0,                                            // Set each memory to the passes argument
            SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32) // Total data (in bytes)
    );

    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; ++i) {
        buffer[i] = 0xFFFF00FF;
    }

    SDL_UpdateTexture(
            texture,                                       // The texture to update
            NULL,                                          // A pointer to the rectangle of pixels to update, NULL to update all
            buffer,                                        // The row of pixel data
            SCREEN_WIDTH * sizeof(Uint32)                  // No of bytes between the pixel data
    );

    SDL_RenderClear(renderer);                             // Clears the renderer

    // copy's the texture to the renderer
    SDL_RenderCopy(
            renderer,                                      // The Renderer Which should copy the texture
            texture,                                       // The texture which will be copied into the renderer
            NULL,                                          // Pointer to source rectangle of pixels, NULL for all
            NULL                                           // Pointer to destination rectangle of pixels, NULL for all
    );

    // Present the renderer to the window
    SDL_RenderPresent(renderer);

    bool quit = true;

    SDL_Event event;                            //Creates and event

    while (quit) {
        // Update particle
        // Draw particle
        // Checks for messages/Events

        while (SDL_PollEvent(
                &event)) {                     // SDL_PollEvent(&event) : Return 1 if events are pending otherwise return 0
            if (event.type == SDL_QUIT) {
                // In this case the event is of quiting the window then jump out the loop
                quit = false;
            }
        }
    }

    // Deallocate the resources assigned to *objects
    delete[] buffer;
    SDL_DestroyTexture(texture);               // Destroy's the texture
    SDL_DestroyRenderer(renderer);             // Destroy's the renderer
    SDL_DestroyWindow(window);                 // Destroy's the window
    SDL_Quit();                                // Closes all the subsystem and Quits

    return 0;

}