#include "header.h"

void camCtrl(int key, int x, int y) {
	extern float rotate_angle;

	switch (key) {
	case GLUT_KEY_LEFT:
		rotate_angle += 5;
		break;
	case GLUT_KEY_RIGHT:
		rotate_angle -= 5;
		break;
	default:
		return;
	}

	glutPostRedisplay();
}

void lightCtrl(unsigned char key, int x, int y) {
	extern float light_angle[2];

	switch (key) {
	case 'w':
		light_angle[1] += 5;
		break;
	case 's':
		light_angle[1] -= 5;
		break;
	case 'a':
		light_angle[0] -= 5;
		break;
	case 'd':
		light_angle[0] += 5;
		break;
	default:
		return;
	}

	glutPostRedisplay();
}
