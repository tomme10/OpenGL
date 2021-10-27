#shader vertex
#version 440 core

layout(location = 0) in vec4 position;
out vec4 pos;

uniform vec4 u_zoom;
uniform vec4 u_offset;

void main() {
	gl_Position = position;
	pos = vec4(position[0]*u_zoom[0]+u_offset[0], (position[1]*u_zoom[0]*2)+u_offset[1], position[2],position[3]);
}


#shader fragment
#version 440 core

out vec4 color;
in vec4 pos;

int MAXITERS = 255;

float mandelBrot(double r, double i) {
	double zn = 0;
	double zi = 0;
	float n = 0;
	while (n <= MAXITERS && sqrt(zn * zn + zi * zi) <= 2) {
		double newn = (zn * zn) - (zi * zi) + r;
		double newi = (zi * zn * 2) + i;
		zn = newn;
		zi = newi;
		n += 1;
	}
	if (n < MAXITERS) return n;
	else return n;
}

void main() {
	float mandel = (mandelBrot(pos[0]*2,pos[1]) / MAXITERS);
	color = vec4(mandel, mandel, mandel, 0.5);
}