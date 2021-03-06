#version 430 core

layout (local_size_x = 128, local_size_y = 1, local_size_z = 1) in;

layout (std430, binding = 0) buffer PositionBuffer{
	vec4 positions[];
};

layout (std430, binding = 1) buffer SpeedBuffer{
	vec4 speed[];
};

layout (std430, binding = 2) buffer ColorBuffer{
	vec4 colors[];
};

layout (std430, binding = 3) buffer LifeBuffer{
	float life[];
};

layout (std430, binding = 4) buffer CameBuffer{
	float camera[];
};

uniform float deltaTimeSec;
uniform float maxLife;
uniform vec4 cameraPosition;

float lenghtSquare(vec4 vector)
{
	return (vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z);
}

vec4 interpolateColor(vec4 col1, vec4 col2, float actu, float max)
{
	float t = actu / max;
	return (1 - t) * col1 + t * col2;
}

void main()
{
	uint index = gl_GlobalInvocationID.x;

	life[index] = life[index] - deltaTimeSec;

	vec4 accel = vec4(0, 0, -9.81, 0);
	vec4 spe = speed[index] + (accel * deltaTimeSec);
	vec4 pos = positions[index];

	vec4 temp = pos + (spe * deltaTimeSec);
	if (temp.z < 0)
	{
		spe.z = -spe.z;
		spe = spe/2;
		if (lenghtSquare(spe) < 0.3)
		{
			spe = vec4(0);
		}
	}

	pos = pos + (spe * deltaTimeSec);
	speed[index] = spe;
	positions[index] = pos;

	colors[index] = interpolateColor(vec4(0, 0, 1, 0.5), vec4(0, 0, 1, 0.5), maxLife - life[index], maxLife);

	if (life[index] > 0)
		camera[index] = lenghtSquare(cameraPosition - pos);
	else
		camera[index] = -1;
}
