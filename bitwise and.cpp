//
// Created by Rupanshu on 12-12-2017.
//

#include <iostream>

using namespace std;

int main() {

    int color = 0x123456;

    unsigned char red = (color & 0xFF0000) >> 16;          // color >> 16 works also
    unsigned char green = (color & 0x00FF00) >> 8;
    unsigned char blue = (color & 0x0000FF);

    cout << hex << (int)red << " " << (int)green << " " << (int)blue << endl;
}

