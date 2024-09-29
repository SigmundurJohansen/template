#include "window.h"
#include "../utils/console.h"
#include "gui.h"
#include "themes.h"
#include <iostream>


static bool b_wireframe = false;
static bool b_wireframeToggle = false;
static bool b_show_console = true;
static bool b_show_demo_window = false;
static bool b_show_demo_windowToggle = false;

bool show_save_menu = false;
bool show_load_menu = false;

// Error callback function for GLFW
void glfwErrorCallback(int error, const char *description)
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
	ImGuiIO &io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;	  // Enable Docking
	// io.ConfigFlags |= ImGuiViewportFlags_TopMost;         //
	io.ConfigViewportsNoAutoMerge = true;
	io.ConfigViewportsNoTaskBarIcon = true;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	embrace_the_darkness();
	set_to_mouse_style();

	ImGuiStyle &style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_ChildBg].w = 0.0f;
	}
	// Initialize ImGui for GLFW and OpenGL3 (IMPORTANT)
	ImGui_ImplGlfw_InitForOpenGL(m_window, true); // Initialize for GLFW
	ImGui_ImplOpenGL3_Init("#version 130");		  // Initialize for OpenGL3 with GLSL version

	return 0;
}

void SetDemoMode()
{
	if (b_show_demo_window != b_show_demo_windowToggle)
	{
		if (b_show_demo_window)
			b_show_demo_windowToggle = true;
		else
			b_show_demo_windowToggle = false;
	}
}

void SetWireframeMode()
{
	if (b_wireframe != b_wireframeToggle)
	{
		if (b_wireframe)
		{
			b_wireframeToggle = true;
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
		{
			b_wireframeToggle = false;
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
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

	set_docking_mode(); // needs one ImGui::End();

	if (b_show_demo_window)
		ImGui::ShowDemoWindow(&b_show_demo_window);

	ImGuiWindowFlags sidebar_window_flags = ImGuiWindowFlags_NoTitleBar;
	ImGui::SetNextWindowBgAlpha(0.0f);					 // disable dockspace overlay over the game window
	ImGui::Begin("Sidebar", NULL, sidebar_window_flags); // needs one ImGui::End();
	ImGui::Separator();

	// OPTIONS

	if (!ImGui::CollapsingHeader("Options"))
	{
		if (ImGui::BeginTable("split", 3))
		{
			ImGui::TableNextColumn();
			ImGui::Checkbox("Wireframe", &b_wireframe);
			ImGui::TableNextColumn();
			ImGui::Checkbox("Console", &b_show_console);
			ImGui::TableNextColumn();
			ImGui::Checkbox("Demo", &b_show_demo_window);
			ImGui::EndTable();
		}
	}

	SetWireframeMode();
	SetDemoMode();

	if (b_show_console)
		show_console(&b_show_console);

	ImGui::Separator();

	// Render stats
	set_render_stats();
	ImGui::Separator();

	if (ImGui::Button("Save Map"))
	{
		show_save_menu = true;
	}

	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	window_flags |= ImGuiWindowFlags_NoNav;
	window_flags |= ImGuiWindowFlags_NoDocking;

	if (show_save_menu)
	{
		const ImGuiViewport *main_viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 650, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
		ImGui::Begin("Save Window", &show_save_menu, window_flags);
		static char saveName[64] = "saveName1";
		ImGui::InputText("name", saveName, sizeof(saveName));
		if (ImGui::Button("save entities"))
		{
			show_save_menu = false;
		}

		ImGui::End();
	}
	ImGui::SameLine();
	if (ImGui::Button("Load Map"))
	{
		show_load_menu = true;
	}
	if (show_load_menu)
	{
		const ImGuiViewport *main_viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 650, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
		ImGui::Begin("Load Window", &show_load_menu, window_flags);
		list_saved_states(show_load_menu);
		ImGui::End();
	}

	ImGui::End();
	ImGui::End();
	ImGui::Render();

	glClear(GL_COLOR_BUFFER_BIT); // Clear screen
	// Rendering
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