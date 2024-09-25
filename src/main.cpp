#define DOCTEST_CONFIG_IMPLEMENT

#include "../external/glad/include/glad/glad.h"
#include "../external/glfw/include/GLFW/glfw3.h"
#include "../external/imgui/imgui.h"
#include "../external/imgui/backends/imgui_impl_glfw.h"
#include "../external/imgui/backends/imgui_impl_opengl3.h"

#include "../test/factorial_test.h"
#include "include/factorial.h"
#include "include/prime_factorial.h"
#include <doctest/doctest.h>
#include <iostream>
#include <libintl.h>
#include <stdio.h>
#include <string.h>

// Error callback function for GLFW
void glfwErrorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << description << std::endl;
}

int main(int _argc, char **_argv)
{
    glfwSetErrorCallback(glfwErrorCallback);
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Setup window
	GLFWwindow *window = glfwCreateWindow(1280, 720, "ImGui GLFW + OpenGL3 Example", NULL, NULL);
	if (window == NULL)
	{
		fprintf(stderr, "Failed to create GLFW window\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

    // Initialize GLAD (or GLEW)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize OpenGL loader" << std::endl;
        return -1;
    }
	
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Initialize ImGui for GLFW and OpenGL3 (IMPORTANT)
    ImGui_ImplGlfw_InitForOpenGL(window, true);   // Initialize for GLFW
    ImGui_ImplOpenGL3_Init("#version 130");       // Initialize for OpenGL3 with GLSL version

    // Main application loop
    while (!glfwWindowShouldClose(window))
    {
        // Poll and handle events
        glfwPollEvents();

        // Start a new ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // ImGui window code
        ImGui::Begin("Hello, world!");
        ImGui::Text("This is a sample text in ImGui.");
        ImGui::End();

        // Rendering
        ImGui::Render();
        glClear(GL_COLOR_BUFFER_BIT);  // Clear screen
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());  // Render ImGui

        // Swap buffers
        glfwSwapBuffers(window);
    }
	
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

	/*
	doctest::Context context;
	int res = context.run(); // run

	printf("Program code.\n");
	prime_factorial(31798230);

	std::cout << gettext("Hello World!") << std::endl;
	*/
	while (true)
	{
	}
	return 0;
}
