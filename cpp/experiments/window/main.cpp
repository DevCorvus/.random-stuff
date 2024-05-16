#include <GL/gl.h>
#include <GLFW/glfw3.h>

int main() {
    GLFWwindow *window;

    if (!glfwInit()) {
        return -1;
    }

    window = glfwCreateWindow(640, 480, "My App", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.5f, 0.0f, 1.0f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
