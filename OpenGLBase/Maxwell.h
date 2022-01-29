#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Shader.h"
#include "imgui.h"

#include <memory>


struct ImguiConfigurations {
};

struct Particle {
	glm::vec3 pos{0.0};
	glm::vec3 vel{0.0};
	glm::vec3 acc{0.00001, -0.0001, 0.0};
	float lifetime{255.0f};
	float remaining = lifetime;

	void update() {
		vel += acc;
		pos += vel;
		remaining-=0.5f;
	}
};

class Maxwell {
public:
	Maxwell();
	~Maxwell();
	void Run();
	
	ImguiConfigurations RenderVars;

	void ProcessKeyboardState();
	void ProcessScrollState();
	void ProcessMousePosition();
private:
	Particle ps[1500];
	Shader _qs;
	unsigned int _vao, _vbo;
	unsigned int tex;

	void _init_pipelines();
	void _init_imgui();

	GLdouble _deltaTime {0};
	GLdouble _currentFrame {0};
	GLdouble _lastFrame {0};

	glm::vec2 _lastOffset {0, 0};

	void _render_pass();
	void _imgui_pass() const;
};