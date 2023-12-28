#pragma once

#include <iostream>
#include <memory>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

typedef struct {
	glm::ivec2 dimensions;
	std::string title;
	bool fullscreen;
}WindowCreateInfo;

class Window
{
public:
	Window(WindowCreateInfo* createInfo);
	Window(const Window& other);
	Window& operator=(const Window& other);

	~Window();

	bool UpdateWindow();

	GLFWwindow* GetWindow();
	glm::ivec2 GetDimensions();

private:
	void CopyFrom(const Window& other);

	glm::ivec2 dimensions{};
	bool fullscreen{};
	
	GLFWwindow* pWindow{};

	std::shared_ptr<char> useCount;
	
	static bool sExists;
};

