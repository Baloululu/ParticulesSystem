#version 330

uniform mat4 mvp;
uniform mat4 transform;

in vec3 position;
in vec4 color;

out vec4 fColor;

void main()
{
    gl_Position = mvp * transform * vec4(position, 1.0);

    fColor = color;
}
