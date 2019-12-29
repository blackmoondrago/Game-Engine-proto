#version 450 core

in vec3 Normal;
in vec2 TexCoords;

out vec4 color;

uniform sampler2D inputTexture;

void main()
{

	color = texture(inputTexture, TexCoords);
	//color = vec4(0.0f,1.0f,1.0f,1.0f);
	
}