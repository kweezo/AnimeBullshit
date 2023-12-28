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
	Window(WindowCreateInfo createInfo);
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

/*
Window.h be my notes 
https://developer.nvidia.com/blog/vulkan-dos-donts/
 for 15-30 command buffers and 5-10 vkQueueSubmit() 
 calls per frame, batch VkSubmitInfo() to a single call as much as
 possible. Each vkQueueSubmit() has a performance cost on CPU,
 so lower is generally better. Note that VkSemaphore-based 
 synchronization can only be done across vkQueueSubmit() calls,
 so you may be forced to split work up into multiple submits.
Functions such as vkAllocateCommandBuffers(),
vkBeginCommandBuffer(), and vkEndCommandBuffer() should be called from the thread
that fills the command buffer. These calls take measurable time on CPU and
therefore should not be collected in a specific thread.
*/
