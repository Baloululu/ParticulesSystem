#include "particlecomputer.h"

ParticleComputer::ParticleComputer()
{

}

QVector3D acc_from_point_force(Force f, Particule p)
{
    QVector3D v = f.getVect() - p.getPos();
    float norme = v.length();
    return f.getValue() * v / (norme * norme);
}

QVector3D acc_from_directional_force(Force f)
{
    return f.getVect() *f.getValue();
}

inline float dist2_max1(QVector3D a, QVector3D b)
{
    return fminf( (a - b).length(), 1.f);
}

CPUParticleComputer::CPUParticleComputer()
{}

ParticleState CPUParticleComputer::interpolate(const ParticleState &particle_state,
                         const std::vector<Force> &forces,
                         TimeTick delta_tick,
                         const TimeSec &tick_per_sec,
                         EmitterGroup &emitters)
{
//    ParticleState current_state = particle_state;

//    while (delta_tick != 0)
//    {
//        if (delta_tick > 0) {
//            current_state = step(particle_state, forces, 1 / (float)tick_per_sec, emitters);
//            delta_tick--;
//        } else {
//            current_state = step(particle_state, forces, -1 / (float)tick_per_sec, emitters);
//            delta_tick++;
//        }
//    }

//    return current_state;
}

// TODO
// add lifetime mechanism for particles + rendering for shaders (intensity)
ParticleState CPUParticleComputer::step(const ParticleState &particle_state,
                                        const std::vector<Force> &forces,
                                        const TimeSec &delta_sec,
                                        EmitterGroup &emitters)
{
//    float ds = (float) delta_sec;
//    ParticleState new_state;
//    int ps_size = particle_state.size();
//    new_state.reserve(ps_size);

//    //emit particles
//    for (std::unique_ptr<Emitter>& emitter : emitters) {
//        emitter->emitParticles([&new_state](Particle p){
//            new_state.push_back(p);
//        });
//    }

//    //calculate positions
//    for (int i = 0; i < ps_size; i++)
//    {
//        Particle new_particle = particle_state[i];

//        //update particle life
//        new_particle.age += delta_sec;
//        if (new_particle.age < 0 || new_particle.age > new_particle.life) {
//            continue;
//        }

//        //calculate new velocity
//        for (int j = 0; j < forces.size(); j++) {
//            const Force &force = forces[j];
//            switch (force.type) {
//            case ForcePoint:
//                new_particle.velocity += ds * acc_from_point_force(force.xyz(), new_particle.position, force.mag1);
//                break;
//            case ForceDirectional:
//                new_particle.velocity += ds * acc_from_directional_force(force.xyz(), force.mag1);
//                break;
//            case ForceNoise_1:
//                new_particle.velocity += ds * acc_from_noise(new_particle.position, force.seed1, force.mag1);
//                break;
//            case ForceNoise_2:
//                new_particle.velocity += ds * acc_from_noise_smooth(new_particle.position, force.seed1, force.mag1, force.x);
//                break;
//            default:
//                break;
//            }
//        }
//        //calculate new position
//        new_particle.position += new_particle.velocity;
//        new_state.push_back(new_particle);
//    }
//    return new_state;
}
