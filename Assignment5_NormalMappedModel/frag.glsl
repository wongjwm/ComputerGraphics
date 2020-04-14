  
#version 330

// Take in our texture coordinate from our vertex shader
in vec2 texCoords;
in vec3 fragPos;
in vec3 normCoords;

// We always define a fragment color that we output.
out vec4 fragColor;

struct PointLight {
    vec3 color;
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float ambientIntensity;
    float specularIntensity;
    float constant;
    float linear;
    float quadratic;
};

uniform sampler2D diffuseTex;
uniform sampler2D normTex;
uniform mat4 viewMatrix;
uniform PointLight pointLights[1];

void main() {
  // Set our output fragment color to whatever we pull from our input texture (Note, change 'tex' to whatever the sampler is named)
  fragColor = texture(diffuseTex, texCoords);
  vec3 diffuseColor = fragColor.rgb;
  vec3 normal = texture(normTex, texCoords).xyz;
  vec3 ambient = vec3(0.0, 0.0, 0.0);
  vec3 diffuseLight = vec3(0.0, 0.0, 0.0);
  vec3 specular = vec3(0.0, 0.0, 0.0);

  for (int i = 0; i < 1; i++) {
    ambient += pointLights[i].ambientIntensity * pointLights[i].color;
    vec3 direction = normalize(pointLights[i].position - fragPos);
    float diffuseImpact = max(dot(normal, direction), 0.0);
    diffuseLight += diffuseImpact * pointLights[i].color;
    mat4 inverseView = inverse(viewMatrix);
    vec3 viewPosn = vec3(inverseView[0][3], inverseView[1][3], inverseView[2][3]);
    vec3 viewDirection = normalize(viewPosn - fragPos);
    vec3 reflectDirection = reflect(-direction, normal);
    float specularLight = pow(max(dot(viewDirection, reflectDirection), 0.0), 32);
    specular += pointLights[i].specularIntensity * specularLight * pointLights[i].color;  
  }
  vec3 light = ambient + specular + diffuseLight;
  fragColor = vec4(diffuseColor * light, 1.0);
}
