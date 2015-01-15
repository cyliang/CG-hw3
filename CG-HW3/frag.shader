R"shader(
uniform sampler2D shadowMap;
varying vec3 normal, lightDir, eyeDir;
varying vec4 mappedCoor;

void PhongShading(bool inShadow);

void main (void)
{
	/* Decide whether in shadow */
	vec3 coor = mappedCoor.xyz / mappedCoor.w;
	coor *= 0.5;
	coor += 0.5;
	
	PhongShading(coor.z >= texture2D(shadowMap, coor.xy).x+0.01);
}

void PhongShading(bool inShadow) {
    vec4 final_color = 
	    (gl_FrontLightModelProduct.sceneColor * gl_FrontMaterial.ambient) + 
	    (gl_LightSource[0].ambient * gl_FrontMaterial.ambient);
							
	vec3 N = normalize(normal);
	vec3 L = normalize(lightDir);
	
	float lambertTerm = dot(N,L);
	
	if(!inShadow && lambertTerm > 0.0)
	{
		final_color += gl_LightSource[0].diffuse * 
		               gl_FrontMaterial.diffuse * 
					   lambertTerm;	
		
		vec3 E = normalize(eyeDir);
		vec3 R = reflect(-L, N);
		float specular = pow( max(dot(R, E), 0.0), 
		                 gl_FrontMaterial.shininess );
		final_color += gl_LightSource[0].specular * 
		               gl_FrontMaterial.specular * 
					   specular;	
	}

    gl_FragColor = final_color;
}
)shader"