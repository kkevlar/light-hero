#version 330 core
out vec3 color;
in vec3 fragPos;
in vec3 fragNor;
uniform vec3 campos;
uniform float pow_spec;
uniform float w_spec;
uniform float w_diffuse;
uniform vec3 lp;
uniform vec3 color_diffuse;
uniform vec3 color_ambient;
uniform float w_ambient;

void main()
{


vec3 n = 1* normalize(fragNor);
vec3 ld = normalize(fragPos - lp);
float diffuse = dot(n,ld);
color.rgb = color_diffuse*diffuse*w_diffuse;


vec3 cd = normalize(fragPos - campos);
vec3 h = normalize(cd+ld);
float spec = dot(n,h);
spec = clamp(spec,0,1);
spec = pow(spec,pow_spec);
color.rgb += vec3(1,1,1)*spec*w_spec;

color.rgb += w_ambient * color_ambient;


}
