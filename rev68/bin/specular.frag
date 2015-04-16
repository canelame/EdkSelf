#version 330
in vec3 o_normal; 
in vec3 o_toLight; 
in vec3 o_toCamera; 
    
out vec4 resultingColor; 

float u_matShininess = 300;
vec3 u_matSpecularColor =  vec3(1,1,1);
vec3 u_matSpecularLight =  vec3(0,1,0);
vec3 u_light_color = vec3(1,1.5,1);
vec3 u_difusse_color= vec3(0,0,1);

vec3 specularLight(in vec3 N, in vec3 L, in vec3 V){
	float specularTerm =0;
	if(dot(N,L)>0){
		vec3 H = normalize(L+V);
		specularTerm = pow(dot(N,H),u_matShininess);
	}

	return u_matSpecularColor*u_matSpecularLight*specularTerm;

}

vec3 difusseLight(in vec3 N, in vec3 L){
		
	float difusseTerm = clamp(dot(N,L),0,1);
	return u_difusse_color  *u_light_color*difusseTerm;
	
}

void main(){
    vec3 L = normalize(o_toLight);
    vec3 V = normalize(o_toCamera);
    vec3 N = normalize(o_normal);

    resultingColor.xyz = difusseLight(N,L) + specularLight(N, L, V);
    resultingColor.a = 1;
}