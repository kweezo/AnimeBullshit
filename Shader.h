#pragma once

#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include <vulkan/vulkan.h>

#include "Device.h"

#define SHADER_MAIN_FUNCTION_STRING_NAME "main"

typedef struct {
	Device *device;
	std::string vertexPath;
	std::string fragmentPath;
}ShaderCreateInfo;

class Shader
{
public:
	Shader(ShaderCreateInfo createInfo);

	Shader(const Shader& other);
	Shader& operator=(const Shader& other);

	VkShaderModule GetVertexModule();
	VkShaderModule GetFragmentModule();

	~Shader();

private:

	void CreateShaderModules();
	std::shared_ptr<std::vector<char>> LoadShaderBinary(std::string path);

	VkShaderModule vertShaderModule;
	VkShaderModule fragShaderModule;

	ShaderCreateInfo createInfo;

	std::shared_ptr<char> useCount;
	void CopyFrom(const Shader& other);
};

