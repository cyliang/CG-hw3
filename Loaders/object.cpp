#include "object.h"
#include <GL/glut.h>

ObjLoader::ObjLoader(const char *object_info_file):
mesh(object_info_file) {
	displayListID = glGenLists(fTotal);

	for (int i = 0; i < fTotal; i++) {
		glNewList(displayListID + i, GL_COMPILE);
			glBegin(GL_TRIANGLES);
			for (int j = 0; j < 3; j++) {
				glNormal3fv(nList[faceList[i].v[j].n].ptr);
				glVertex3fv(vList[faceList[i].v[j].v].ptr);
			}
			glEnd();
		glEndList();
	}
}

void ObjLoader::setObj() const {
	int lastMaterial = -1;
	for(int i=0; i<fTotal; i++) {
		if(lastMaterial != faceList[i].m) {
			lastMaterial = (int) faceList[i].m;
			const material &mtl = mList[lastMaterial];

			glMaterialfv(GL_FRONT, GL_AMBIENT, mtl.Ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mtl.Kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mtl.Ks);
			glMaterialfv(GL_FRONT, GL_SHININESS, &mtl.Ns);
		}

		glCallList(displayListID + i);
	}
}

