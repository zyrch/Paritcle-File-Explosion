//
// Created by Rupanshu on 21-11-2017.
//

#include "Swarm.h"
#include <SDL2/SDL.h>

namespace first {
    Swarm::Swarm() : last_time(0) {
        m_pParticles = new Particles[NPARTICLES];
    }


    Swarm::~Swarm() {
        delete[] m_pParticles;
    }

    void Swarm::update(int elapsed) {

        int interval = elapsed - last_time;

        for (int i = 0; i < Swarm::NPARTICLES; ++i) {
            m_pParticles[i].update(interval);
        }

        last_time = elapsed;
    }
}