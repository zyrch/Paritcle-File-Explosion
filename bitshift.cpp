//
// Created by Rupanshu on 19-11-2017.
//

#include <iostream>
#include "Classes/Screen.h"
#include <iomanip>
#define SDL_MAIN_HANDLED
#include "include/SDL2/SDL.h"


using namespace std;
using namespace refr;

int main() {

    unsigned char alpha = 0xFF;
    unsigned char red = 0x12;
    unsigned char green = 0x34;
    unsigned char blue = 0x56;

    unsigned int color = 0;
    color += alpha;
    color =  color << 8;                                          // shift the memory to the 8 bit towards the left
    color += red;
    color <<= 8;                                                  // same as color = color << 8;
    color += green;
    color <<= 8;
    color += blue;

    cout << setfill('0') << setw(8) << hex << color << endl;

    return 0;

}
