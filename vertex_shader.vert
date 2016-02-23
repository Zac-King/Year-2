#version 150

in vec4 Position;  
in vec4 Color;
out vec4 vColor;  
uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model; 
uniform float time;
uniform mat4 ProjectionView;

void main() 
{ 
	vColor = Color * cos(time);	
	gl_Position = ProjectionView * Position; 
};
