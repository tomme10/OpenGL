#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <string>
#include "shape.h"
#include "shaders.cpp"


double offsetX = 0;
double offsetY = 0;
double zoom = 1;

bool d = false;
bool a = false;
bool s = false;
bool w = false;


bool shift = false;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_D && action == GLFW_PRESS) d = true;
    else if (key == GLFW_KEY_A && action == GLFW_PRESS) a = true;
    else if (key == GLFW_KEY_S && action == GLFW_PRESS) s = true;
    else if (key == GLFW_KEY_W && action == GLFW_PRESS) w = true;
    else if (key == GLFW_KEY_W && action == GLFW_RELEASE) w = false;
    else if (key == GLFW_KEY_S && action == GLFW_RELEASE) s = false;
    else if (key == GLFW_KEY_D && action == GLFW_RELEASE) d = false;
    else if (key == GLFW_KEY_A && action == GLFW_RELEASE) a = false;
    else if (key == GLFW_KEY_PERIOD && action == GLFW_PRESS) zoom = zoom * 3 / 2;
    else if (key == GLFW_KEY_COMMA && action == GLFW_PRESS) zoom = zoom * 1 / 2;
    else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS) shift = true;
    else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE) shift = false;
}

int main(void)
{

    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(1000, 1000, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSwapInterval(3);

    if (glewInit() != GLEW_OK) {
        std::cout << "error: did not return ok" << std::endl;
        return -1;
    }
    parsedShader shaderSource = parseShader("res/shaders/shader.shader");
    unsigned int shader = CreateShader(shaderSource.vertex, shaderSource.fragment);
    glUseProgram(shader);

    int zoomLocation = glGetUniformLocation(shader, "u_zoom");
    int offsetLocation = glGetUniformLocation(shader, "u_offset");

    circle c(0,0,2);
    c.genBuffers();
    c.populateBuffers();

    while (!glfwWindowShouldClose(window))
    {
        if (shift) {
            if (a && !d) offsetX -= zoom / 8;
            else if (d && !a) offsetX += zoom / 8;
            else if (!w && s) offsetY -= zoom / 4;
            else if (!s && w) offsetY += zoom / 4;
        }
        else if (!shift) {
            if (a && !d) offsetX -= zoom / 16;
            else if (d && !a) offsetX += zoom / 16;
            else if (!w && s) offsetY -= zoom / 8;
            else if (!s && w) offsetY += zoom / 8;
        }

        glUniform4f(zoomLocation, zoom, 1, 1, 1);
        glUniform4f(offsetLocation, offsetX, offsetY, 0, 0);

        glClear(GL_COLOR_BUFFER_BIT);

        c.draw();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}