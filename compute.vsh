#version 440

struct Particle
{
    vec2 _position;
    vec2 _velocity;
    int _isActive;
};

layout (local_size_x = 128, local_size_y = 1, local_size_z = 1) in;

layout (binding = 0) buffer ParticleBuffer {
    Particle AllParticles[];
};

uniform float uDeltaTimeSec;     // self-explanatory

void main()
{
    uint index = gl_GlobalInvocationID.x;
    Particle p = AllParticles[index];

    vec2 deltaPosition = p._velocity * uDeltaTimeSec;
    p._position = p._position + deltaPosition;

    AllParticles[index] = p;
}
