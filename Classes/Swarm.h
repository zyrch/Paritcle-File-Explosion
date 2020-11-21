//
// Created by Rupanshu on 21-11-2017.
//

#ifndef PARTICLE_FIRE_EXPLOSION_SWARM_H
#define PARTICLE_FIRE_EXPLOSION_SWARM_H

#include "Particles.h"
#include <SDL2/SDL.h>

namespace first {
    class Swarm {

    public:
        const static int NPARTICLES = 5000;
        int last_time;

    private:
        Particles *m_pParticles;                            // Pointer to an array of particles

    public:
        Swarm();
        const Particles * const getParticles() {return m_pParticles;}
        void update(int elapsed);
        ~Swarm();

    };
}


#endif //PARTICLE_FIRE_EXPLOSION_SWARM_H
