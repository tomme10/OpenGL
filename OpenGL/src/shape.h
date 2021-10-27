

class circle {
public:
	circle(float cx, float cy, float radius);
	void genBuffers();

	void populateBuffers();
	void draw();

	void move(float x, float y);

private:
	float x;
	float y;
	float r;
	unsigned int vbo;
	unsigned int ibo;
};