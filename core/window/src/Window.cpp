#include <iostream>
#include "Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void windowresize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

Window::Window(int width, int height, const char* title)
{
    // Initialize GLFW
    if(!glfwInit())
        std::cerr << "Failed to initialize GLFW!" << std::endl;
    else
        std::cout << "GLFW initialized! GLFW version: " << GLFW_VERSION_MAJOR << "." << GLFW_VERSION_MINOR << std::endl;
    
    // Initialize window
    this->window = glfwCreateWindow(width, height, title, NULL, NULL);
    if(!this->window)
        std::cerr << "Failed to initialize GLFW window!" << std::endl;
    else
        std::cout << "Initialized GLFW window!" << std::endl;

    // Configure window
    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, windowresize);

    // Initialize OpenGL
    if(!gladLoadGL())
        std::cerr << "Failed to initialize GLAD!" << std::endl;
    else
        std::cout << "GLAD initialized! OpenGL version: " << GLVersion.major << "." << GLVersion.minor << std::endl;
}

Window::~Window()
{
    glfwTerminate();
}

void Window::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::update() const
{
    // Check for OpenGL errors
    GLenum error = glGetError();
    if(error != GL_NO_ERROR)
        std::cout << "OpenGL error: " << error << std::endl;

    // Poll for input
    glfwPollEvents();

    // Swap front buffer(displayed) and back buffer
    glfwSwapBuffers(window);
}

bool Window::closed() const
{
    return glfwWindowShouldClose(window);
}