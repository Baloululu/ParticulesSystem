#version 330

uniform mat4 mvp;
uniform mat4 transform;

uniform vec3 cameraRight;
uniform vec3 cameraUp;

in vec3 position;
in vec4 color;
in vec3 loc;

out vec4 fColor;

void main()
{
    vec3 vertexPosition_worldspace = loc +
        (cameraRight * position.x)
        + (cameraUp * position.y);

    gl_Position = mvp * transform * vec4(vertexPosition_worldspace, 1.0);

    if (gl_VertexID == 0)
        fColor = color;
    else
        fColor = vec4(color.r, color.g, color.b, 0);
}
