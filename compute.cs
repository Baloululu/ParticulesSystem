#version 430 core

layout (local_size_x = 128, local_size_y = 1, local_size_z = 1) in;

layout (std140, binding = 1) buffer PositionBuffer{
	vec4 postions[];
};

uniform float deltaTimeSec;

void main()
{
	uint index = gl_GlobalInvocationID.x;
//    Particle p = AllParticles[index];

	vec4 pos = postions[index];

	pos = pos + vec4(0.5 * deltaTimeSec, 0, 0, 0);
	postions[index] = pos;

//	p._position = p._position + vec3(0.01,0,0);
//	p._color = vec4(p._color);

//    vec2 deltaPosition = p._velocity * uDeltaTimeSec;
//    p._position = p._position + deltaPosition;

//    AllParticles[index] = p;
}
