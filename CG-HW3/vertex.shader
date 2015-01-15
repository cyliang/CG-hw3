R"shader(
uniform mat4 lightViewMatrix, lightProjMatrix, camViewMatrix;
varying vec3 normal, lightDir, eyeDir;
varying vec4 mappedCoor;

void main()
{	
	normal = gl_NormalMatrix * gl_Normal;

	vec3 vVertex = vec3(gl_ModelViewMatrix * gl_Vertex);

	lightDir = vec3(gl_LightSource[0].position.xyz - vVertex);
	eyeDir = -vVertex;

	gl_Position = ftransform();
	mappedCoor = lightProjMatrix * lightViewMatrix * inverse(camViewMatrix) * gl_ModelViewMatrix * gl_Vertex;
}
)shader"