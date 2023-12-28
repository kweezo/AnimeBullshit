#include "Instance.h"

Instance::Instance() {
	pInstance.reset(new VkInstance);

	VkInstanceCreateInfo createInfo{};
	VkApplicationInfo appInfo{};

	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;

	appInfo.apiVersion = VK_VERSION_1_3;
	appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
	appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);

	appInfo.pApplicationName = "AnimeBS";
	appInfo.pEngineName = "our god is impotent";


	uint32_t extensionCount;
	const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&extensionCount);


	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	createInfo.enabledLayerCount = 0;
	createInfo.ppEnabledLayerNames = nullptr;
	createInfo.enabledExtensionCount = extensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;


	if (vkCreateInstance(&createInfo, nullptr, pInstance.get()) != VK_SUCCESS) {
		std::cerr << "Failed to create a Vulkan instance" << std::endl;
	}
}

VkInstance Instance::GetInstance() {
	return pInstance.get()[0];
}

Instance::Instance(const Instance& other) {
	pInstance = other.pInstance;
}

Instance& Instance::operator=(const Instance& other) {
	if (this == &other) {
		return *this;
	}

	pInstance = other.pInstance;

	return *this;
}

Instance::~Instance() {
	if (pInstance.use_count() == 1) {
		vkDestroyInstance(pInstance.get()[0], nullptr);
	}
}
