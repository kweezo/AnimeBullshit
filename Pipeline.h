#pragma once

#include <array>
#include <iostream>
#include <vector>
#include <memory>

#include <vulkan/vulkan.h>

#include "Shader.h"
#include "Display.h"
#include "Device.h"


typedef struct {
	Shader* shader;
	Display* display;
	Device* device;
}PipelineCreateInfo;

class Pipeline
{
public:
	Pipeline(PipelineCreateInfo createInfo);
	Pipeline(const Pipeline& other);
	Pipeline& operator=(const Pipeline& other);

	~Pipeline();
private:

	void CreatePipeline();
	void CreateRenderPass();
	void CreateFramebuffers();

	std::array<VkPipelineShaderStageCreateInfo, 2> CreateShaderStage();

	std::vector<VkFramebuffer> framebuffers;

	VkPipeline pipeline;
	VkPipelineLayout pipelineLayout;
	VkRenderPass renderPass;

	PipelineCreateInfo createInfo;

	void CopyFrom(const Pipeline& other);
	std::shared_ptr<char> useCount;
};

