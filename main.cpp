//
// Created by Rupanshu on 16-11-2017.
//

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <bits/stdc++.h>
#include "Classes/Screen.h"
#include "Classes/Swarm.h"
#include <iostream>
#include <SDL2/SDL.h>

#define SDL_MAIN_HANDLED

#include "include/SDL2/SDL.h"


using namespace std;
using namespace first;

int main() {

    srand((unsigned int) time(NULL));

    Screen screen;

    if (!screen.init()) {
        //cout << "error while creating the screen" << endl;
    }

    screen.update();

    Swarm swarm;

    while (true) {                                                      // game loop

        int elasped = SDL_GetTicks();                                  // Get the number of mili seconds passed after the programme runs
        swarm.update(elasped);

        const Particles *const pParticles = swarm.getParticles();

        unsigned char green = (unsigned char)((1 + sin(elasped * 0.0001))* 128);
        unsigned char red = (unsigned char)((1 + cos(elasped * 0.0002))* 128);
        unsigned char blue = (unsigned char)((1 + sin(elasped * 0.001))* 128);


        for (int i = 0; i < Swarm::NPARTICLES; ++i) {
            Particles particle = pParticles[i];

            int x = (int) ((particle.m_x + 1) * Screen::SCREEN_WIDTH / 2);
            int y = (int) (particle.m_y * Screen::SCREEN_WIDTH / 2) + Screen::SCREEN_HEIGHT/2;

            screen.setPixel(x, y, red, green, blue);
        }

       screen.boxBlur();

        // Draw the screen
        screen.update();

        // Check event and messages
        if (!screen.processEvent()) {
            break;
        }

    }

    screen.close();

    return 0;

}