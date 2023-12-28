#pragma once

#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <iostream>
#include <memory>
#include <array>

#include "Instance.h"
#include "Window.h"
#include "Device.h"

typedef struct {
	Instance* instance;
	Window* window;
	Device* device;
}DisplayCreateInfo;

class Display
{
public:
	Display(DisplayCreateInfo* createInfo);
	Display(const Display& other);
	Display& operator=(const Display& other);

	~Display();
private:
	VkSurfaceKHR surface;
	VkSwapchainKHR swapchain;

	DisplayCreateInfo* createInfo;

	void CreateSurface();
	void CreateSwapchain();

	void CopyFrom(const Display& other);

	std::shared_ptr<char> useCount;

	const uint32_t imageCount = 3;

	VkSurfaceCapabilitiesKHR surfaceCapabilities;

};

