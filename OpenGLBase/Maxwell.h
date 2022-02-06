#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
	float lifetime{1500.0f};
	float remaining = lifetime;

	void update(float dt) {
		//vel += acc;
		pos += vel * dt;
		remaining-=dt;
	}
};

struct Emitter {
	std::vector<Particle> ps;
	std::vector<int> dead_particles;
	std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution;
	std::uniform_real_distribution<double> distribution_double_01;
	std::uniform_real_distribution<double> distribution_n;
	int spawn_particles = 10;

	void Initialize() {
		distribution = std::uniform_real_distribution<double>(-0.5, 0.5);
		distribution_double_01 = std::uniform_real_distribution<double>(0, 1);
		distribution_n = std::uniform_real_distribution<double>(-10, 0.0001);

		for (int i = 0; i < 100000; i++) {
			ps.push_back(
				Particle()
			);
			ps[i].remaining = 0;
		}
	}

	void Fire() {
		if (dead_particles.size() >= spawn_particles) 
			for (int i = 0; i < spawn_particles; i++) {
				ps[dead_particles.back()] = Particle(
						{0.0, -1.0, 0.0},
						{distribution(generator)*0.00025,  std::uniform_real_distribution<double>(0.95, 1.025)(generator)*0.0005, 0.0},
						{distribution(generator)*0.0001, std::uniform_real_distribution<double>(0.95, 1.025)(generator)*0.00000001, 0.0}
					);
				dead_particles.pop_back();
			}
	}

	void Render(Shader shader, unsigned int vao, unsigned int tex, float dt) {
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		for (int i = 0; i < ps.size(); i++) {
			if (ps[i].remaining <= 0) {
				dead_particles.push_back(i);
				continue;
			}
	
			ps[i].update(dt);

			float scale = 0.05;

			glm::mat4 model = glm::mat4{1.0};
			model = glm::translate(model, ps[i].pos);
			model = glm::scale(model, glm::vec3(scale, scale, scale));

			shader.use();
			shader.setFloat("scale", scale);
			shader.setVec3("color", glm::vec3(distribution_double_01(generator), distribution_double_01(generator), distribution_double_01(generator)));
			shader.setMat4("model", model);
			shader.setVec3("center", ps[i].pos);
			shader.setFloat("lifetime", ps[i].lifetime);
			shader.setFloat("remaining", ps[i].remaining);

			glBindVertexArray(vao);
			glBindTextureUnit(0, tex);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);	
		}
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
	Emitter em {};

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