#version 430

uniform mat4 mvp;
uniform mat4 transform;

uniform vec3 cameraRight;
uniform vec3 cameraUp;

in vec3 position;
in vec4 pos;
in vec4 color;
in float life;

out vec4 fColor;

void main()
{
    if (life > 0)
    {
        vec3 vertexPosition_worldspace = pos.xyz +
            (cameraRight * position.x)
            + (cameraUp * position.y);

        gl_Position = mvp * transform * vec4(vertexPosition_worldspace, 1.0);

        if (gl_VertexID == 0)
            fColor = color;
        else
            fColor = vec4(color.r, color.g, color.b, 0);
    }
}
