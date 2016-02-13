#version 150

in vec4 Position;  
in vec4 Color;
out vec4 vColor;  
uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model; 
void main() 
{ 
	vColor = Color;
	gl_Position = Projection * View * Model *  Position; 
};
