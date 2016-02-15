#version 150                                  

in vec4 Position;  
in vec4 Color;
out vec4 vColor;  
uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model; 
uniform float Time;

void main() 
{ 
vColor = Color;
	vec4 P = Position;
	//P.y += sin(Time + Position.x);	
	//P.x += cos(Time + Position.y);
	//P.z += cos(Time + Position.z);
	gl_Position = Projection*View* Model*P; 
};
