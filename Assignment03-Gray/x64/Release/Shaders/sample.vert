#version 330 core

//Gets data at Attrib Index 0
layout(location=0) in vec3 aPos;

//projection matrix
uniform mat4 projection;

//view 
uniform mat4 view;

void main ()
{	
	//multiply the projection and view matrices to the vec4 version of aPos
	gl_Position = projection * view * vec4(aPos, 1.0);
}
