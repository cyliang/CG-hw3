#pragma once
#include "object.h"
#include <vector>

class SceneLoader {
public:
	SceneLoader(const char *SceneInfoFile);
	void displayScene() const;

private:
	struct Model {
		Model(const char *objFileName);

		ObjLoader obj;
		float scale_xyz[3];
		float rotate_axyz[4];
		float translate_xyz[3];
	};

	std::vector<Model> models;
};
