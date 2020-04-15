#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 textureCoords;
layout(location = 3) in vec3 tangents; 
layout(location = 4) in vec3 bitangents; 

out VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} vs_out;

// We now have our camera system set up.
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    // We have our transformed position set properly now
    gl_Position = projectionMatrix*viewMatrix*modelMatrix*vec4(position, 1.0);

    // Calculate Tangent Space Matrix (TBN)
    vec3 t = normalize(vec3(modelMatrix * vec4(tangents, 0.0)));
    vec3 n= normalize(vec3(modelMatrix * vec4(normal, 0.0)));

    // re-orthogonalize T with respect to N
    t - normalize(t - dot(t, n) * n);

    // then retrieve perpendicular vector B with the cross product of T and N
    vec3 b = cross(n, t);
    mat3 TBN = transpose(mat3(t, b, n));

    vs_out.FragPos = vec3(modelMatrix * vec4(position, 1.0));;
    vs_out.TexCoords = textureCoords;
    vs_out.TangentLightPos = TBN * lightPos;
    vs_out.TangentViewPos  = TBN * viewPos;
    vs_out.TangentFragPos  = TBN * vec3(modelMatrix * vec4(position, 1.0));
}