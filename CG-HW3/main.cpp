#include "header.h"
#include <iostream>
#include <string>
using namespace std;

SceneLoader *scene;
LightLoader *light;
ViewingLoader *view;
GLhandleARB shadowShader;

float rotate_angle = 0;
float light_angle[2] = {0.0f, 0.0f}; // Horizontal, Vertical

int main(int argc, char *argv[]) {
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <scene_name>" << endl;
		return -1;
	}
	string view_file(argv[1]);
	string scene_file(argv[1]);
	string light_file(argv[1]);
	view_file += ".view";
	light_file += ".light";
	scene_file += ".scene";

	view = new ViewingLoader(view_file.c_str());
	light = new LightLoader(light_file.c_str());

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(view->getWidth(), view->getHeight());
	glutCreateWindow("GL-Assignment3 0116229");

	if (glewInit() != GLEW_OK)
		return -1;

	scene = new SceneLoader(scene_file.c_str());
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(camCtrl);
	glutKeyboardFunc(lightCtrl);
	glutMainLoop();

	return 0;
}

void reshape(GLsizei w, GLsizei h) {
	view->setWidthHeight(w, h);
}