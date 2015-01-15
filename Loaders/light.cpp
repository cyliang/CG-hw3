#include "light.h"
#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

LightLoader::LightLoader(const char *info_file): lights_count(0) {
	std::ifstream ifile(info_file, std::ios::in);
	if(!ifile) {
		std::cerr << "Cannot load the light file: " << info_file << std::endl;
		exit(1);
	}

	std::string type;
	while(ifile >> type) {
		if(type == "ambient") {
			ambient_rgb[3] = 1.0;
			ifile >> ambient_rgb[0] >> ambient_rgb[1] >> ambient_rgb[2];
		} else if(type == "light") {
			LightSource &source = lights[lights_count++];

			source.position_xyz[3] = 0.0f;
			source.ambient_rgb[3] = source.diffuse_rgb[3] = source.specular_rgb[3] = 1.0f;

			ifile >> source.position_xyz[0] >> source.position_xyz[1] >> source.position_xyz[2]
				>> source.ambient_rgb[0] >> source.ambient_rgb[1] >> source.ambient_rgb[2]
				>> source.diffuse_rgb[0] >> source.diffuse_rgb[1] >> source.diffuse_rgb[2]
				>> source.specular_rgb[0] >> source.specular_rgb[1] >> source.specular_rgb[2];
		} else {
			std::cerr << "Error in parsing the light file: " << info_file << std::endl;
			exit(1);
		}

		if(!info_file) {
			std::cerr << "Error in parsing the light file: " << info_file << std::endl;
			exit(1);
		}
	}
}

GLenum light_enum[8] = {
	GL_LIGHT0,
	GL_LIGHT1,
	GL_LIGHT2,
	GL_LIGHT3,
	GL_LIGHT4,
	GL_LIGHT5,
	GL_LIGHT6,
	GL_LIGHT7
};

void LightLoader::setLight() const {
	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_rgb);

	for(int i=0; i<lights_count; i++) {
		const LightSource &source = lights[i];
		GLenum light_enabled = light_enum[i];
		glEnable(light_enabled);
		
		glLightfv(light_enabled, GL_POSITION, source.position_xyz);
		glLightfv(light_enabled, GL_DIFFUSE, source.diffuse_rgb);
		glLightfv(light_enabled, GL_SPECULAR, source.specular_rgb);
		glLightfv(light_enabled, GL_AMBIENT, source.ambient_rgb);
	}
}

const float *LightLoader::lightPos(int id) const {
	return lights[id].position_xyz;
}