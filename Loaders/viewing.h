#pragma once

class ViewingLoader {
public:
	ViewingLoader(const char *ViewingFile);

	void setViewing() const;
	int getWidth() const;
	int getHeight() const;
	const float *getAtPos() const;
	void setWidthHeight(float width, float height);

	void zoom(bool inOut);
	void rotate(bool leftRight);

private:
	float eye_xyz[3];
	float vat_xyz[3];
	float vup_xyz[3];
	float fovy;
	float dnear;
	float dfar;
	float viewport_xywh[4];

	float rotate_angle;
};
