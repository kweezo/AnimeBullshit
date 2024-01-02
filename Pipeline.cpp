#include "Pipeline.h"


Pipeline::Pipeline(PipelineCreateInfo createInfo) {
	this->createInfo = createInfo;

	CreatePipeline();
	CreateFramebuffers();

	useCount.reset(new char);
}

Pipeline::Pipeline(const Pipeline& other) {
	CopyFrom(other);
}

Pipeline& Pipeline::operator=(const Pipeline& other) {
	if (this == &other) {
		return *this;
	}

	CopyFrom(other);

	return *this;
}

void Pipeline::CreatePipeline() {
	std::array<VkDynamicState, 2> dynamicStates = {
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_SCISSOR
	};

	VkPipelineDynamicStateCreateInfo dynamicState{};
	dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	dynamicState.dynamicStateCount = dynamicStates.size();
	dynamicState.pDynamicStates = dynamicStates.data();

	//TODO implement
	VkPipelineVertexInputStateCreateInfo vertexCreateInfo{};
	vertexCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertexCreateInfo.vertexAttributeDescriptionCount = 0;
	vertexCreateInfo.vertexBindingDescriptionCount = 0;


	VkPipelineInputAssemblyStateCreateInfo inputAssemblyCreateInfo{};
	inputAssemblyCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssemblyCreateInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	inputAssemblyCreateInfo.primitiveRestartEnable = VK_FALSE;

	VkViewport viewport{};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = createInfo.display->GetSwapchainExtent().width;
	viewport.height = createInfo.display->GetSwapchainExtent().height;
	viewport.minDepth = 0.0f;
	viewport.maxDepth =     viewport.maxDepth = 1.0f;

	VkRect2D scissor{};
	scissor.offset = { 0, 0 };
	scissor.extent = createInfo.display->GetSwapchainExtent();

	VkPipelineViewportStateCreateInfo viewportState{};
	viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportState.viewportCount = 1;
	viewportState.scissorCount = 1;
	viewportState.pScissors = &scissor;
	viewportState.pViewports = &viewport;


	VkPipelineRasterizationStateCreateInfo rasterizer{};
	rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizer.depthClampEnable = VK_FALSE;
	rasterizer.rasterizerDiscardEnable = VK_FALSE;
	rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
	rasterizer.lineWidth = 1.0f;
	rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
	rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
	rasterizer.depthBiasEnable = VK_FALSE;

	VkPipelineMultisampleStateCreateInfo multisampling{};//maybe?
	multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampling.sampleShadingEnable = VK_FALSE;
	multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;


	VkPipelineColorBlendAttachmentState colorBlendAttachment{};
	colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT
		| VK_COLOR_COMPONENT_A_BIT;
	colorBlendAttachment.blendEnable = VK_FALSE;

	VkPipelineColorBlendStateCreateInfo colorBlending{};
	colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlending.logicOpEnable = VK_FALSE;
	colorBlending.attachmentCount = 1;
	colorBlending.pAttachments = &colorBlendAttachment;

	VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;

	if (vkCreatePipelineLayout(createInfo.device->GetDevice(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
		std::cerr << "Failed to create a pipeline layout, sorry bro" << std::endl;
	}

	CreateRenderPass();

	std::array<VkPipelineShaderStageCreateInfo, 2> shaderStages = CreateShaderStage();

	VkGraphicsPipelineCreateInfo pipelineCreateInfo{};
	pipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineCreateInfo.stageCount = shaderStages.size();
	pipelineCreateInfo.pStages = shaderStages.data();
	pipelineCreateInfo.pVertexInputState = &vertexCreateInfo;
	pipelineCreateInfo.pViewportState = &viewportState;
	pipelineCreateInfo.pRasterizationState = &rasterizer;
	pipelineCreateInfo.pMultisampleState = &multisampling;
	pipelineCreateInfo.pColorBlendState = &colorBlending;
	pipelineCreateInfo.pDynamicState = &dynamicState;
	pipelineCreateInfo.layout = pipelineLayout;
	pipelineCreateInfo.renderPass = renderPass;
	pipelineCreateInfo.pInputAssemblyState = &inputAssemblyCreateInfo;
	pipelineCreateInfo.subpass = 0; //?????? CHECK THAT OUT

	if (vkCreateGraphicsPipelines(createInfo.device->GetDevice(), nullptr, 1, &pipelineCreateInfo, nullptr, &pipeline) !=
		VK_SUCCESS) {
		std::cerr << "Failed to create the graphics pipeline" << std::endl;
	}
}

void Pipeline::CreateRenderPass() {
	VkAttachmentDescription colorAttachment{};
	colorAttachment.format = createInfo.display->GetSwapchainImageFormat();
	colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	
	VkAttachmentReference colorAttachmentRef{};
	colorAttachmentRef.attachment = 0;
	colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkSubpassDescription subpass{};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &colorAttachmentRef;

	VkRenderPassCreateInfo renderPassInfo{};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.attachmentCount = 1;
	renderPassInfo.pAttachments = &colorAttachment;
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subpass;

	if (vkCreateRenderPass(createInfo.device->GetDevice(), &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS) {
		std::cerr << "Failed to create the render pass" << std::endl;
	}
}

std::array<VkPipelineShaderStageCreateInfo, 2> Pipeline::CreateShaderStage() {
	VkPipelineShaderStageCreateInfo vertStageCreateInfo{};
	vertStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	vertStageCreateInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
	vertStageCreateInfo.module = createInfo.shader->GetVertexModule();
	vertStageCreateInfo.pName = "main";

	VkPipelineShaderStageCreateInfo fragStageCreateInfo{};
	fragStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	fragStageCreateInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	fragStageCreateInfo.module = createInfo.shader->GetFragmentModule();
	fragStageCreateInfo.pName = "main";

	return { vertStageCreateInfo, fragStageCreateInfo };
}

void Pipeline::CreateFramebuffers() {
	std::vector<VkImageView> swapchainImageViews = createInfo.display->GetSwapchainImageViews();

	framebuffers.resize(swapchainImageViews.size());

	VkFramebufferCreateInfo framebufferCreateInfo{};
	framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	framebufferCreateInfo.renderPass = renderPass;
	framebufferCreateInfo.attachmentCount = 1;
	framebufferCreateInfo.width = createInfo.display->GetSwapchainExtent().width;
	framebufferCreateInfo.height = createInfo.display->GetSwapchainExtent().height;
	framebufferCreateInfo.layers = 1;
		
	uint32_t i = 0;
	for (VkFramebuffer& framebuffer : framebuffers) {
		framebufferCreateInfo.pAttachments = &swapchainImageViews[i];

		if (vkCreateFramebuffer(createInfo.device->GetDevice(), &framebufferCreateInfo, nullptr, &framebuffer) != VK_SUCCESS) {
			std::cerr << "Failed to create one of the framebuffers" << std::endl;
		}
		i++;
	}
}

void Pipeline::CopyFrom(const Pipeline& other) {
	pipeline = other.pipeline;
	pipelineLayout = other.pipelineLayout;
	renderPass = other.renderPass;
	createInfo = other.createInfo;
	useCount = other.useCount;
}

Pipeline::~Pipeline() {
	if (useCount.use_count() == 1) {
		for (VkFramebuffer framebuffer : framebuffers) {
			vkDestroyFramebuffer(createInfo.device->GetDevice(), framebuffer, nullptr);
		}
		vkDestroyRenderPass(createInfo.device->GetDevice(), renderPass, nullptr);
		vkDestroyPipelineLayout(createInfo.device->GetDevice(), pipelineLayout, nullptr);
		vkDestroyPipeline(createInfo.device->GetDevice(), pipeline, nullptr);
	}
}
