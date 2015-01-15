#include "header.h"
#include <iostream>
using namespace std;

extern ViewingLoader *view;
extern LightLoader *light;
extern SceneLoader *scene;
extern GLhandleARB shadowShader;
GLuint frameBufferObj;
GLuint shadowMapTexture;

void init() {
	/* Create Shader */
	const char *vertexShader =
#include "vertex.shader"
	;
	const char *fragShader =
#include "frag.shader"
	;

	shadowShader = glCreateProgram();
	ShaderLoad(shadowShader, vertexShader, GL_VERTEX_SHADER);
	ShaderLoad(shadowShader, fragShader, GL_FRAGMENT_SHADER);

	/* Generate texture for shadow map */
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &shadowMapTexture);
	glBindTexture(GL_TEXTURE_2D, shadowMapTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, view->getWidth(), view->getHeight(), 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	/* Generate Frame Buffer Object */
	glGenFramebuffers(1, &frameBufferObj);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObj);

	/* Attach the texture to the Frame Buffer Object */
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowMapTexture, 0);
}

void display() {
	void renderScene();
	extern float rotate_angle;

	GLfloat lightViewMatrix[16], lightProjectionMatrix[16];

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	
	{
		/* Pass 1 */
		glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObj);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		
		/* Set & get view matrix */
		const float *lightPos = light->lightPos(0);
		const float *atPos = view->getAtPos();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(
			lightPos[0], lightPos[1], lightPos[2],
			atPos[0], atPos[1], atPos[2],
			1, 0, 0
		);
		glGetFloatv(GL_MODELVIEW_MATRIX, lightViewMatrix);

		/* Set & get projection matrix */
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60, view->getWidth() / (float) view->getHeight(), 10, 60);
		glGetFloatv(GL_PROJECTION_MATRIX, lightProjectionMatrix);
		glViewport(0, 0, view->getWidth(), view->getHeight());

		glMatrixMode(GL_MODELVIEW);
		scene->displayScene();
	}

	{
		/* Pass 2 */
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		view->setViewing();

		/* Get view matrix */
		GLfloat camViewMatrix[16];
		glMatrixMode(GL_MODELVIEW);
		glGetFloatv(GL_MODELVIEW_MATRIX, camViewMatrix);

		glUseProgram(shadowShader);
		GLint locationLightViewMatrix = glGetUniformLocation(shadowShader, "lightViewMatrix");
		GLint locationLightProjMatrix = glGetUniformLocation(shadowShader, "lightProjMatrix");
		GLint locationCamViewMatrix = glGetUniformLocation(shadowShader, "camViewMatrix");
		GLint locationShadowMap = glGetUniformLocation(shadowShader, "shadowMap");
		if (locationLightProjMatrix == -1 || locationLightViewMatrix == -1 || locationCamViewMatrix == -1 || locationShadowMap == -1) {
			cerr << "Can't find location of variable." << endl;
		} else {
			glUniform1i(locationShadowMap, 0);
			glUniformMatrix4fv(locationLightViewMatrix, 1, GL_FALSE, lightViewMatrix);
			glUniformMatrix4fv(locationLightProjMatrix, 1, GL_FALSE, lightProjectionMatrix);
			glUniformMatrix4fv(locationCamViewMatrix, 1, GL_FALSE, camViewMatrix);
		}

		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, shadowMapTexture);

		glMatrixMode(GL_MODELVIEW);
		light->setLight();
		scene->displayScene();

		glDisable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	glutSwapBuffers();
}

void renderScene() {
	extern float light_angle[2];


	//glPushMatrix();
		//glRotatef(light_angle[0], 0, 1, 0);
		//glRotatef(light_angle[1], -1, 0, 0);
	//glPopMatrix();

	
	//	glRotatef(rotate_angle, 0, 1, 0);
}