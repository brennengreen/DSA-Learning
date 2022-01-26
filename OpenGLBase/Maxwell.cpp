#include "Maxwell.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <filesystem>

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Input.h"
#include "Application.h"

#include "stb_image.h"

Maxwell::Maxwell()
{
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
	}

	glViewport(0, 0, Application::GetWindowExtent().x, Application::GetWindowExtent().y);

	_init_pipelines();
	_init_imgui();

	Input::Update();
}

Maxwell::~Maxwell() {
	ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Maxwell::ProcessKeyboardState()
{
}

void Maxwell::ProcessScrollState()
{
	glm::vec2 scroll_offset = Input::GetScrollOffset();
}

void Maxwell::ProcessMousePosition()
{
	_lastOffset = Input::GetMouseOffset();
}

void Maxwell::_init_pipelines()
{
	// 36 Verices, 6 Per face, 1 Color
	float vertices[] = {
		-0.5, 0.5, 0.0,
		0.5, 0.5, 0.0,
		0.5, -0.5, 0.0,
		0.5, -0.5, 0.0,
		-0.5, -0.5, 0.0,
		-0.5, 0.5, 0.0

		/*0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,

		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,

		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,

		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,

		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0*/
	};
	unsigned int vertex_count = 6;

	glCreateBuffers(1, &_vbo);
	glNamedBufferStorage(_vbo, sizeof(float)*3*vertex_count, vertices, 0);

	glCreateVertexArrays(1, &_vao);

	glVertexArrayVertexBuffer(_vao, 0, _vbo, 0, 3*sizeof(float));

	glEnableVertexArrayAttrib(_vao, 0);
	glVertexArrayAttribFormat(_vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(_vao, 0, 0);

	_qs = Shader("./Shaders/qs.vert", "./Shaders/qs.frag");
}

void Maxwell::_init_imgui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(Application::GetWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 460 core");
}

void Maxwell::_render_pass()
{
	glViewport(0, 0, Application::GetWindowExtent().x, Application::GetWindowExtent().y);
	glClear(GL_COLOR_BUFFER_BIT);

	glm::mat4 model = glm::mat4{1.0};
	
	_qs.use();
	_qs.setMat4("model", model);
	_qs.setVec3("view_pos", glm::vec3(0.0, 0.0, -1.0));

	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void Maxwell::_imgui_pass() const {
	ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

	{
        ImGui::Begin("Maxwell Configurations");

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Maxwell::Run()
{
    while (!Application::ShouldTerminate()) {
		ProcessKeyboardState();
		if (Input::GetMouseOffset() != _lastOffset) ProcessMousePosition();
		ProcessScrollState();

		_currentFrame = glfwGetTime();
		_deltaTime = _currentFrame - _lastFrame;

		// Render
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		_render_pass();
		_imgui_pass();

		Application::SwapBuffers();
		Application::PollEvents();
	}
}