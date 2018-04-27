#version 330

uniform mat4 mvp;
uniform mat4 transform;

in vec3 position;
in vec3 color;

out vec3 fColor;

void main()
{
    gl_Position = mvp * transform * vec4(position, 1.0);

    fColor = color;
}
