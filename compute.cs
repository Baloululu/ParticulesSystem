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
uniform vec4 cameraPosition;

float lenghtSquare(vec4 vector)
{
	return (vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z);
}

void main()
{
	uint index = gl_GlobalInvocationID.x;

	life[index] = life[index] - deltaTimeSec;

	if (life[index] > 0)
	{
		vec4 accel = vec4(0, 0, -9.8, 0);
		vec4 spe = speed[index] + (accel * deltaTimeSec);
		vec4 pos = positions[index];

		vec4 temp = pos + (spe * deltaTimeSec);
		if (temp.z < 0)
		{
			spe.z = -spe.z;
			spe = spe/2;
			if (lenghtSquare(spe) < 0.1)
			{
				spe = vec4(0);
			}
		}

		pos = pos + (spe * deltaTimeSec);
		speed[index] = spe;
		positions[index] = pos;

		camera[index] = lenghtSquare(cameraPosition - pos);
	}
	else
		camera[index] = -1;
}
