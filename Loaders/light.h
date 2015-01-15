#pragma once

class LightLoader {
public:
	LightLoader(const char *light_info_file);
	void setLight() const;
	const float *lightPos(int id) const;

private:
	float ambient_rgb[4];
	struct LightSource {
		float position_xyz[4];
		float ambient_rgb[4];
		float diffuse_rgb[4];
		float specular_rgb[4];
	} lights[8];
	int lights_count;
};
