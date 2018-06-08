#version 430

uniform mat4 mvp;
uniform mat4 transform;

uniform vec3 cameraRight;
uniform vec3 cameraUp;

layout (location = 0) in vec3 position;
//in vec3 position;

//in vec4 color;
//in vec3 loc;

//in int id;

//struct Particle
//{
//        vec3 _position;
//};

//layout (binding = 0) buffer pos {
//    vec3 AllPositions[];
//};

layout (location = 1) in vec4 pos;
//layout (location = 1) in vec3 color;
//in vec3 pos;

out vec4 fColor;

void main()
{
//    uint index = gl_DrawID;
//    vec3 p = AllPositions[32*3].xyz;

    vec3 vertexPosition_worldspace = pos.xyz +
        (cameraRight * position.x)
        + (cameraUp * position.y);

    gl_Position = mvp * transform * vec4(vertexPosition_worldspace, 1.0);

//    if (gl_VertexID == 0)
//        fColor = p._color;
//    else
//        fColor = vec4(p._color.r, p._color.g, p._color.b, 0);

    if (gl_VertexID == 0)
        fColor = vec4(1, 1, 1, 1);
    else
        fColor = vec4(1, 1, 1, 1);

//    vec3 vertexPosition_worldspace = loc +
//        (cameraRight * position.x)
//        + (cameraUp * position.y);

//    gl_Position = mvp * transform * vec4(vertexPosition_worldspace, 1.0);

//    if (gl_VertexID == 0)
//        fColor = color;
//    else
//        fColor = vec4(color.r, color.g, color.b, 0);
}
