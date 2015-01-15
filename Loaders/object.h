#pragma once
#include "mesh.h"

class ObjLoader: protected mesh {
public:
	ObjLoader(const char *object_info_file);
	
	void setObj() const;

private:
	unsigned int displayListID;

};
