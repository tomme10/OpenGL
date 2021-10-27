#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <string>
#include <stdlib.h>

void terminate(std::string error){
	std::printf("there was an error");
	std::printf(error.c_str());
	exit(-1);
}

int width = 800;
int height = 600;

const std::string title = "openGl learning experements";


float vertex[] = {
	0.5f,0.0f,0.0f,
	0.0f,1.0f,0.0f,
	1.0f,1.0f,0.0f
};

float colors[]{
	1.0f,0.0f,0.0f,
	0.0f,1.0f,0.0f,
	0.0f,0.0f,1.0f
};




int main() {
	GLFWwindow* window;

	if (!glfwInit()) terminate("failed GLFW initiation");

	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!window) { glfwTerminate(); terminate("failed GLFW window creation"); }

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) { terminate("failed GLEW initiation"); }





	std::cout << "hello World" << std::endl;
}