#version 330 core

out vec4 FragColor; // Returns a color

//Simple shader that colors the model 
void main()
{
	//				  R   G   B  a  Ranges from 0->1
	FragColor = vec4(153.0f/254.f, 255.f/254.f, 153.f/254.f, 1.0f); //Sets the color of the fragment
}

