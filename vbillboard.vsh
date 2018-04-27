#version 330

uniform mat4 mvp;
uniform mat4 transform;

uniform vec3 cameraRight;
uniform vec3 cameraUp;

in vec3 position;
in vec3 color;

out vec3 fColor;

void main()
{
    vec3 vertexPosition_worldspace =
        (cameraRight * position.x)
        + (cameraUp * position.y);

    gl_Position = mvp * transform * vec4(vertexPosition_worldspace, 1.0);

    fColor = color;
}
