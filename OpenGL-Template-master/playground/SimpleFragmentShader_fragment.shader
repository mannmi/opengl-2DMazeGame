#version 330 core

// Ouput data
out vec3 color;
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec3 aColor; // the color variable has attribute position 1
out vec3 ourColor; // output a color to the fragment shader

void main()
{

	// Output color = red 
	color = vec3(1,0,0);
	gl_Position = vec4(aPos, 1.0);
    eeourColor = aColor; // set ourColor to the input color we got from the vertex data

}