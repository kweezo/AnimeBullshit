#pragma once

#include <iostream>
#include <memory>

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

class Instance
{
public:
	Instance();
	Instance(const Instance& other);
	Instance& operator=(const Instance& other);

	~Instance();

	VkInstance GetInstance();

private:
	std::shared_ptr<VkInstance> pInstance;
};

