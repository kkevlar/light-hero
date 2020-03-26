#version 330 core
out vec4 color;
void main()
{
	color.rgb = vec3(0.5,0.5,0.5);
	color.a=1;	//transparency: 1 .. 100% NOT transparent
}
