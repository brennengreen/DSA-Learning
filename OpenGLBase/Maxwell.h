#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Shader.h"
#include "imgui.h"

#include <random>
#include <memory>
#include <vector>


struct ImguiConfigurations {
};

struct Particle {
	Particle() = default;
	~Particle() = default;
	Particle(
		glm::vec3 p,
		glm::vec3 v = glm::vec3{-0.005, 1.01, 0.0},
		glm::vec3 a = glm::vec3{0.00001, -0.0001, 0.0}
	) {
		pos = p;
		vel = v;
		acc = a;
	}
	glm::vec3 pos{0.0};
	glm::vec3 vel{0.0};
	glm::vec3 acc{0.0};
	float lifetime{50.0f};
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
	std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution;
	std::uniform_real_distribution<double> distribution_p;
	std::uniform_real_distribution<double> distribution_n;

	std::vector<Particle> ps;
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