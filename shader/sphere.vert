#version 450 core

layout(location=7) in vec3 Pos1; // the position variable has attribute position 0
layout(location=1) in vec3 Pos2;
layout(location=2) in vec3 Pos3;

layout(location=3) in uint isVisible;

out VS_OUT{  // interface-block
vec3 FragPos1;
vec3 FragPos2;
vec3 FragPos3;
//uvec3 tokens;
uint  isVisble;

} vs_out;

void main(){
vs_out.FragPos1=Pos1;
vs_out.FragPos2=Pos2;
vs_out.FragPos3=Pos3;
vs_out.isVisble=isVisible;
//vs_out.tokens=tokens;
}