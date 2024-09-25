#include "window.h"
#include <iostream>

// Error callback function for GLFW
void glfwErrorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << description << std::endl;
}

int window::init()
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
	m_window = glfwCreateWindow(1200, 700, "template", NULL, NULL);
	if (m_window == NULL)
	{
		fprintf(stderr, "Failed to create GLFW window\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(m_window);
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
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);   // Initialize for GLFW
    ImGui_ImplOpenGL3_Init("#version 130");       // Initialize for OpenGL3 with GLSL version
    return 0;
}

void window::render()
{
	m_should_exit = glfwWindowShouldClose(m_window);
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
	glClear(GL_COLOR_BUFFER_BIT);							// Clear screen
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); // Render ImGui
	// Swap buffers
	glfwSwapBuffers(m_window);
}

void window::terminate()
{
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(m_window);
	glfwTerminate();
}