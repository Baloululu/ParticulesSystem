#version 430 core

layout (local_size_x = 128, local_size_y = 1, local_size_z = 1) in;

layout (std140, binding = 0) buffer PositionBuffer{
	vec4 postions[];
};

layout (std140, binding = 1) buffer DirectionBuffer{
	vec4 directions[];
};

layout (std140, binding = 2) buffer ColorBuffer{
	vec4 colors[];
};

uniform float deltaTimeSec;

void main()
{
	uint index = gl_GlobalInvocationID.x;

	vec4 pos = postions[index];
	vec4 dir = directions[index];

	vec4 temp = pos + (dir * deltaTimeSec);

	if (temp.x > 10 || temp.x < -10)
		dir.x = -dir.x;
	if (temp.y > 10 || temp.y < -10)
		dir.y = -dir.y;
	if (temp.z > 10 || temp.z < -10)
		dir.z = -dir.z;

	pos = pos + (dir * deltaTimeSec);
	postions[index] = pos;
	directions[index] = dir;
}
