#include "Shader.h"


Shader::Shader(ShaderCreateInfo createInfo) {
	this->createInfo = createInfo;

	useCount.reset(new char);

	CreateShaderModules();
}

std::shared_ptr<std::vector<char>> Shader::LoadShaderBinary(std::string path) {
	std::ifstream file(path, std::ios::ate | std::ios::binary);

	if (!file.is_open()) {
		std::cerr << "Failed to load shader binary " << path << std::endl;
		return {};
	}

	size_t size = file.tellg();

	std::shared_ptr<std::vector<char>> binData(new std::vector<char>);
	binData->resize(size);

	file.seekg(0);
	file.read(binData->data(), size);

	return binData;
}

Shader::Shader(const Shader& other) {
	CopyFrom(other);
}


Shader& Shader::operator=(const Shader& other) {
	if (this == &other) {
		return *this;
	}
	
	CopyFrom(other);

	return *this;
}

void Shader::CreateShaderModules() {
	std::shared_ptr<std::vector<char>> vertexBin = LoadShaderBinary(createInfo.vertexPath);
	std::shared_ptr<std::vector<char>> fragBin = LoadShaderBinary(createInfo.fragmentPath);

	VkShaderModuleCreateInfo moduleCreateInfo{};

	moduleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	
	moduleCreateInfo.codeSize = vertexBin->size();
	moduleCreateInfo.pCode = (uint32_t*)vertexBin->data();

	if (vkCreateShaderModule(createInfo.device->GetDevice(), &moduleCreateInfo, nullptr, &vertShaderModule) != VK_SUCCESS) {
		std::cerr << "Failed to create the vertex shader module for " << createInfo.vertexPath << std::endl;;
	}

	
	moduleCreateInfo.codeSize = fragBin->size();
	moduleCreateInfo.pCode = (uint32_t*)fragBin->data();

	if (vkCreateShaderModule(createInfo.device->GetDevice(), &moduleCreateInfo, nullptr, &fragShaderModule) != VK_SUCCESS) {
		std::cerr << "Failed to create the fragment shader module for " << createInfo.fragmentPath << std::endl;;
	}
}

void Shader::CopyFrom(const Shader& other) {
	vertShaderModule = other.vertShaderModule;
	fragShaderModule = other.fragShaderModule;
	createInfo = other.createInfo;
	useCount = other.useCount;
}

Shader::~Shader() {
	if (useCount.use_count() == 1) {
		vkDestroyShaderModule(createInfo.device->GetDevice(), vertShaderModule, nullptr);
		vkDestroyShaderModule(createInfo.device->GetDevice(), fragShaderModule, nullptr);
	}
}



