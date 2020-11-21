//
// Created by Rupanshu on 21-11-2017.
//

#include "Particles.h"
#include "Screen.h"
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>

namespace first {

    Particles::Particles() : m_x(0), m_y(0) {
        init();
    }

    void Particles::init() {
        m_x = 0;
        m_y = 0;
        m_direction = (2 * M_PI * rand()) / RAND_MAX;
        m_speed = (0.04 * rand()) / RAND_MAX;

        m_speed *= m_speed;
    }

    void Particles::update(int interval) {

        m_direction += interval * 0.0003;

        m_xspeed = m_speed * cos(m_direction);
        m_yspeed = m_speed * sin(m_direction);

        m_x += m_xspeed * interval;
        m_y += m_yspeed * interval;

        if (m_x < -1 || m_x > 1 || m_y < -1 || m_y > 1){
            init();
        }

        if (rand() < RAND_MAX/100){
            init();
        }
    }

}
