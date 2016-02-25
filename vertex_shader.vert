#version 410

layout( location = 0 ) in vec4 Position;
layout( location = 1 ) in vec2 TexCoord;

out vec2 vTexCoord;

uniform mat4 ProjectionViewModel;

uniform sampler2D noiseTexture;

// heightScale has a default but can be overridden
uniform float heightScale = 10;

void main() {
	vTexCoord = TexCoord;

	// samples height
	float height = texture( noiseTexture, TexCoord ).r;

	// and offsets the Y by the height and heightScale
	gl_Position = ProjectionViewModel * (Position + vec4(0,height * heightScale,0,0));
}