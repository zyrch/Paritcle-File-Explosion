//
// Created by Rupanshu on 21-11-2017.
//

#ifndef PARTICLE_FIRE_EXPLOSION_PARTICLES_H
#define PARTICLE_FIRE_EXPLOSION_PARTICLES_H

#include <stdlib.h>
#include <SDL2/SDL.h>

namespace first {
    struct Particles {
        double m_x;                         // To change the postion slowly I declare it double
        double m_y;

    private:
        double m_direction;
        double m_speed;
        double m_xspeed;
        double m_yspeed;

    private:
        void init();
    public:
        Particles();

        void update(int interval);

        //~Particles();
    };
}


#endif //PARTICLE_FIRE_EXPLOSION_PARTICLES_H
