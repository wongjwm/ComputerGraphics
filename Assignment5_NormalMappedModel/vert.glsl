#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normalCoords;
layout(location = 2) in vec2 textureCoords;

// We now have our camera system set up.
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

// We define a new output vec2 for our texture coorinates.
out vec3 fragPos;
out vec3 normCoords;
out vec2 texCoords;

void main()
{
    // We have our transformed position set properly now
    gl_Position = projectionMatrix*viewMatrix*modelMatrix*vec4(position, 1.0);
    // And we map our texture coordinates as appropriate
    fragPos = position;
    normCoords = normalCoords;
    texCoords = textureCoords;
}