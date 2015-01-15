#pragma once

#include <GL/glew.h>
#include <GL/glut.h>
#include "light.h"
#include "scene.h"
#include "viewing.h"
#include "ShaderLoader.h"

void init();
void display();
void reshape(GLsizei, GLsizei);
void camCtrl(int, int, int);
void lightCtrl(unsigned char, int, int);


