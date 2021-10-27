#include <GL/glew.h>
#include <cmath>
#include <iostream>
#include "shape.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const int points = 4;


inline double radians(double degrees) { return degrees / (180.0 / 3.141592653589793238463); }
inline double degrees(double radians) { return radians * (180.0 / 3.141592653589793238463); }


float max(float a, float b) {
	if (a > b) {
		return a;
	} else {
		return b;
	}
}

circle::circle(float cx, float cy,float radius) {
	x = cx;
	y = cy;
	r =  radius;
};

void circle::genBuffers() {
	glGenBuffers(1,&vbo);
	glGenBuffers(1, &ibo);
}

void circle::populateBuffers() {
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glBindBuffer(GL_INDEX_ARRAY, ibo);

	float positions[2 * points];
	//unsigned int indexes[(points-2)*3];

	float anglePerPopula = 360 / points;

	int point = 0;
	for (double i = 0; i < 360; i += anglePerPopula) {
		positions[point] = (std::cos(radians(i+45)) * r) + x;
		positions[point + 1] = (std::sin(radians(i+45)) * r) + y;
		point += 2;
	}

	/*for (int i = 0; i < (points - 2); i++) {
		indexes[i * 3] = positions[0];
		indexes[i * 3 + 1] = positions[1];
		indexes[i * 3 + 2] = positions[2];
	}*/

	glBufferData(GL_ARRAY_BUFFER ,sizeof(float)* points * 2, positions, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
}

void circle::move(float cx, float cy) {
	x = cx;
	y = cy;
}

void circle::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glDrawArrays(GL_TRIANGLE_FAN, 0, points);
}