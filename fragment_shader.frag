#version 410

uniform sampler2D noiseTexture;

in vec2 vTexCoord;

out vec4 FragColour;

void main() {
	// uses swizzling to display heightmap as greyscale
	FragColour = vec4( texture( noiseTexture, vTexCoord ).rrr, 1 );
}