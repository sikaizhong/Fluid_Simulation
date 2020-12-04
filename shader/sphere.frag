#version 450 core
out vec4 FragColor;
uniform vec3 lightPos; // lightPos in world space, I have translated and normalized the input model.
uniform vec3 lightColor;
uniform bool turnOnLight;
uniform vec4 ClippingEqn;


in GS_OUT{
	vec4 world_pos;
	vec4 view_pos;
    vec4 color;
} gs_in;
bool isPositiveSide(vec4 ClippingEqn, vec4 pos)
{
    float clipDist=dot(ClippingEqn, pos);
    if(clipDist<0) return false;
    return true;
}
void main()
{   
    
    FragColor = gs_in.color;


}
