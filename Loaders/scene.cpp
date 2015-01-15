#include "scene.h"
#include <GL/glut.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

SceneLoader::Model::Model(const char *file_name): obj(file_name) {
}

SceneLoader::SceneLoader(const char *info_file) {
	std::ifstream ifile(info_file, std::ios::in);
	if(!ifile) {
		std::cerr << "Cannot load scene file: " << info_file << std::endl;
		exit(1);
	}

	std::string model_str;
	while(ifile >> model_str) {
		if(model_str != "model") {
			std::cerr << "Error in parsing scene file: " << info_file << std::endl;
			exit(1);
		}

		std::string obj_name;
		ifile >> obj_name;
		Model m(obj_name.c_str());
		
		ifile >> m.scale_xyz[0] >> m.scale_xyz[1] >> m.scale_xyz[2]
			>> m.rotate_axyz[0] >> m.rotate_axyz[1] >> m.rotate_axyz[2] >> m.rotate_axyz[3]
			>> m.translate_xyz[0] >> m.translate_xyz[1] >> m.translate_xyz[2];

		if(!ifile) {
			std::cerr << "Error in parsing scene file: " << info_file << std::endl;
			exit(1);
		}

		models.push_back(m);
	}
}

void SceneLoader::displayScene() const {
	glMatrixMode(GL_MODELVIEW);

	for(int i=0; i<models.size(); i++) {
		const Model &m = models[i];

		glPushMatrix();
			glTranslatef(m.translate_xyz[0], m.translate_xyz[1], m.translate_xyz[2]);
			glRotatef(m.rotate_axyz[0], m.rotate_axyz[1], m.rotate_axyz[2], m.rotate_axyz[3]);
			glScalef(m.scale_xyz[0], m.scale_xyz[1], m.scale_xyz[2]);

			m.obj.setObj();
		glPopMatrix();
	}
}
