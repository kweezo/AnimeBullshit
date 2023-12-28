#include "Window.h"

bool Window::sExists = false;

Window::Window(WindowCreateInfo createInfo) {
	dimensions.x = createInfo.dimensions.x;
	dimensions.y = createInfo.dimensions.y;
	fullscreen = createInfo.fullscreen;
	
	if (sExists) {
		std::cerr << "Failed to create a window instance, as one already exists" << std::endl;
		return;
	}

	if (!glfwInit()) {
		std::cerr << "Failed to init GLFW" << std::endl;
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	pWindow = glfwCreateWindow(dimensions.x, dimensions.y,
		createInfo.title.c_str(),
		fullscreen ? glfwGetPrimaryMonitor() : nullptr,
		nullptr);

	if (!pWindow) {
		std::cerr << "Failed to create a GLFW window" << std::endl;
		return;
	}

	glfwMakeContextCurrent(pWindow);

	sExists = true;

	useCount.reset(new char);
}

bool Window::UpdateWindow() {
	glfwPollEvents();

	return glfwWindowShouldClose(pWindow);
}

Window::Window(const Window& other) {
	CopyFrom(other);
}

Window& Window::operator=(const Window& other) {
	if (this == &other) {
		return *this;
	}

	CopyFrom(other);

	return *this;
}

void Window::CopyFrom(const Window& other) {
	this->dimensions = dimensions;
	this->fullscreen = fullscreen;
	this->pWindow = pWindow;
	this->useCount = useCount;
}

Window::~Window(){
	if (useCount.use_count() == 1) {
		sExists = false;

		glfwDestroyWindow(pWindow);
		glfwTerminate();
	}
}

GLFWwindow* Window::GetWindow() {
	return pWindow;
}

glm::ivec2 Window::GetDimensions() {
	return dimensions;
}
