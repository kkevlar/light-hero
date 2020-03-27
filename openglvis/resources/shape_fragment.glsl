#version 330 core
out vec4 color;
in vec3 fragPos;
in vec3 fragNor;
uniform vec3 campos;
uniform float pow_spec;
uniform float w_spec;
uniform float w_diffuse;
uniform vec3 lp;
uniform vec3 color_diffuse;
uniform vec3 color_ambient;

uniform vec3 cubepos0;
uniform vec3 cubepos1;
uniform vec3 cubepos2;
uniform vec3 cubepos3;
uniform vec4 lit_amounts;
uniform int my_index;

uniform float w_ambient;
uniform float alpha;

void main()
{


vec3 n = 1 * normalize(fragNor);
vec3 ld = normalize(fragPos - lp);
float diffuse = dot(n,ld);
color.rgb = color_diffuse*diffuse*w_diffuse;
vec3 cd = normalize(fragPos - campos);

vec3 h;
float spec;
float interpow = 2.0f;
float ispecfactor = 0.15f;

if(my_index != 0)
{
ld = normalize(fragPos - cubepos0);
h = normalize(cd-ld);
spec = dot(n,h);
spec = clamp(spec,0,1);
spec = pow(spec,interpow);
diffuse = dot(n,ld);
diffuse = clamp(diffuse,0,1);
color.rgb += color_diffuse*diffuse*0.0*lit_amounts.r;
color.rgb += color_diffuse*spec*lit_amounts.r*ispecfactor;
}

if(my_index != 1)
{
ld =  normalize(fragPos - cubepos1);
h = normalize(cd-ld);
spec = dot(n,h);
spec = clamp(spec,0,1);
spec = pow(spec,interpow);
diffuse = dot(n,ld);
diffuse = clamp(diffuse,0,1);
color.rgb += color_diffuse*diffuse*0.0*lit_amounts.g;
color.rgb += color_diffuse*spec*lit_amounts.g*ispecfactor;
}

if(my_index != 2)
{
ld =  normalize(fragPos - cubepos2);
h = normalize(cd-ld);
spec = dot(n,h);
spec = clamp(spec,0,1);
spec = pow(spec,interpow);
diffuse = dot(n,ld);
diffuse = clamp(diffuse,0,1);
color.rgb += color_diffuse*diffuse*0.0*lit_amounts.b;
color.rgb += color_diffuse*spec*lit_amounts.b*ispecfactor;
}

if(my_index != 3)
{
ld =  normalize(fragPos - cubepos3);
h = normalize(cd-ld);
spec = dot(n,h);
spec = clamp(spec,0,1);
spec = pow(spec,interpow);
diffuse = dot(n,ld);
diffuse = clamp(diffuse,0,1);
color.rgb += color_diffuse*diffuse*0.0*lit_amounts.a;
color.rgb += color_diffuse*spec*lit_amounts.a*ispecfactor;
}


color.rgb += w_ambient * color_ambient;
color.a = alpha;


}
