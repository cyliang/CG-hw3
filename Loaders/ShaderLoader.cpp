#include "ShaderLoader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>
#include <GL/glut.h>


bool ShaderLoad(GLhandleARB programId, const char* shader_string, GLenum shaderType)
{
	GLhandleARB h_shader;
	GLint str_length, maxLength;
	GLint isCompiled = GL_FALSE, isLinked = GL_FALSE;
	GLcharARB *pInfoLog;

	str_length = strlen(shader_string);

	// Create and load shader string.
	h_shader = glCreateShader(shaderType);
	if(h_shader == 0)
	{
		fprintf(stderr, "Error : Failed to create OpenGL shader object.\n");
		return false;
	}
	glShaderSource(h_shader, 1, (const GLcharARB**)&shader_string, &str_length);
	
	// Compile the vertex shader, print out the compiler log message.
	glCompileShader(h_shader);

	// get compile state information
	glGetObjectParameterivARB(h_shader, GL_OBJECT_COMPILE_STATUS_ARB, &isCompiled);

	if(!isCompiled)
	{
		fprintf(stderr, "Error : Failed to compile OpenGL shader source.\n");
		glGetObjectParameterivARB(h_shader, GL_OBJECT_INFO_LOG_LENGTH_ARB, &maxLength);
		pInfoLog = (GLcharARB *) malloc(maxLength * sizeof(GLcharARB));
		glGetInfoLogARB(h_shader, maxLength, &str_length, pInfoLog);
		fprintf(stderr, "%s\n", pInfoLog);
		free(pInfoLog);
		return false;
	}
	glAttachShader(programId, h_shader);

	// delete the shader object, since we have attached it with the program object.
	glDeleteShader(h_shader);

	// Link the program and print out the linker log message
	glLinkProgram(programId);
	glGetObjectParameterivARB(programId, GL_OBJECT_LINK_STATUS_ARB, &isLinked);

	if(!isLinked)
	{
		fprintf(stderr, "Error : Failed to link OpenGL shader.\n");
		glGetObjectParameterivARB(programId, GL_OBJECT_INFO_LOG_LENGTH_ARB, &maxLength);
		pInfoLog = (GLcharARB *) malloc(maxLength * sizeof(GLcharARB));
		glGetInfoLogARB(programId, maxLength, &str_length, pInfoLog);
		fprintf(stderr, "%s\n", pInfoLog);
		free(pInfoLog);
		return false;
	}

	return true;
}
