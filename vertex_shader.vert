#version 150

in vec4 Position;  
in vec4 Color;
out vec4 vColor;  
uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model; 
uniform float time;
void main() 
{ 
	vec4 P = vec4(1.0, 1.0, 1.0, 1.0);
	vColor = Color * cos(time);	
	P.x = cos(time);
	P.y = sin(time);
	P.z = tan(time);
	gl_Position = Projection * View * Model * P * Position; 
};
