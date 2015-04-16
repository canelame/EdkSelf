#version 330
in vec3 o_normal;
in vec3 o_toLight;
in vec3 o_toCamera;

vec3 u_light_color = vec3(0.6,0.3,0);
vec3 u_difusse_color= vec3(0,0,1);

out vec4 resulting_color;


vec3 ambientLight(){
		
		return u_difusse_color  *u_light_color;
	
}



void main(){

vec3 L = normalize(o_toLight);
vec3 V = normalize(o_toCamera);
vec3 N = normalize(o_normal);



resulting_color.xyz=ambientLight();
resulting_color.a=1;

}