#ifndef PARTICLECOMPUTER_H
#define PARTICLECOMPUTER_H

#include "utilities.h"
#include "particles.h"
#include "emitter.h"
#include "force.h"
#include<QVector3D>

typedef std::vector<Particule> ParticleState;

class ParticleComputer
{
public:
    ParticleComputer();
    QVector3D acc_from_point_force(Force f, Particule p);
    QVector3D acc_from_directional_force(Force f);
};

class CPUParticleComputer : public ParticleComputer {
public:
    CPUParticleComputer();

    virtual ParticleState interpolate(const ParticleState &particle_state,
                             const std::vector<Force> &forces,
                             TimeTick delta_tick,
                             const TimeSec &tick_per_sec,
                             EmitterGroup &emitters);

    ParticleState step(const ParticleState &particle_state,
                       const std::vector<Force> &forces,
                       const TimeSec &delta_sec,
                       EmitterGroup &emitters);
};

#endif // PARTICLECOMPUTER_H
