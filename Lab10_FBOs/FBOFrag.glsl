#version 330

// Take in our texture coordinate from our vertex shader
in vec2 texCoords;

// We always define a fragment color that we output.
out vec4 fragColor;

// Maintain our uniforms.
uniform sampler2D FBOTex;              // our primary texture
const float offset = 1.0 / 300.0;

void main() {
  
  vec2 offsets[9] = vec2[] (vec2(-offset, offset), vec2(0.0f, offset), vec2(offset, offset),
                            vec2(-offset, 0.0f), vec2(0.0f, 0.0f), vec2(offset, 0.0f), 
                            vec2(-offset, -offset), vec2(0.0f, -offset), vec2(offset, -offset));

  float kernel[9] = float[](
    2, 2, 2,
    2, -15, 2,
    2, 2, 2
  );

  vec3 sampleTex[9];
  for (int i = 0; i < 9; i++) {
    sampleTex[i] = vec3(texture(FBOTex, texCoords.st + offsets[i]));
  }

  vec3 col = vec3(0.0);
  for (int i = 0; i < 9; i++)
      col += sampleTex[i] * kernel[i];
  fragColor = vec4(col, 1.0);

}