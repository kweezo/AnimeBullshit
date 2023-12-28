#include "Device.h"

const std::array<const char*, 1> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

Device::Device(DeviceCreateInfo createInfo) {
	useCount.reset(new char);

	instance = createInfo.instance;

	PickPhysicalDevice();
	MapQueueFamilyIndexes();
	CreateDevice();
}

Device::Device(const Device& other) {
	CopyFrom(other);
}

Device& Device::operator=(const Device& other) {
	if (this == &other) {
		return *this;
	}

	CopyFrom(other);

	return *this;
}

void Device::PickPhysicalDevice() {
	uint32_t deviceCount;
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

	for (VkPhysicalDevice availableDevice : devices) {
		VkPhysicalDeviceProperties properties;
		vkGetPhysicalDeviceProperties(availableDevice, &properties);

		VkPhysicalDeviceFeatures features;
		vkGetPhysicalDeviceFeatures(availableDevice, &features);
		
		if (features.geometryShader) {//to avoid mining gpu
			physicalDevice = availableDevice;
			if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
				break;
			}
		}
	}
}

void Device::MapQueueFamilyIndexes() {
	uint32_t queueFamilyCount;
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);
	
	std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilyProperties.data());

	//if possible separate transfer and graphics queue families but if no thats is fine
	uint32_t i = 0;
	
	bool separateTransferFamilyExists = false;

	for (VkQueueFamilyProperties& properties : queueFamilyProperties) {
		if (properties.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			queueFamilyIndexes[GRAPHICS_QUEUE_FAMILY] = i;
			queueCounts[GRAPHICS_QUEUE_FAMILY] = properties.queueCount;
		}
		else if (properties.queueFlags & VK_QUEUE_TRANSFER_BIT) {
			queueFamilyIndexes[TRANSFER_QUEUE_FAMILY] = i;
			queueCounts[TRANSFER_QUEUE_FAMILY] = properties.queueCount;
			separateTransferFamilyExists = true;
		}
		i++;
	}
	if (!separateTransferFamilyExists) {
		queueFamilyIndexes[TRANSFER_QUEUE_FAMILY] = queueFamilyIndexes[GRAPHICS_QUEUE_FAMILY];
		queueCounts[TRANSFER_QUEUE_FAMILY] = queueCounts[GRAPHICS_QUEUE_FAMILY];
	}
}

std::vector<VkDeviceQueueCreateInfo> Device::CreateQueueCreateInfos() {
	float* graphicsQueuePriorities = (float*)calloc(queueCounts[GRAPHICS_QUEUE_FAMILY], sizeof(float));
	float* transferQueuePriorities = (float*)calloc(queueCounts[TRANSFER_QUEUE_FAMILY], sizeof(float));


	std::vector<VkDeviceQueueCreateInfo> createInfos;

	VkDeviceQueueCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;


	createInfo.queueFamilyIndex = queueFamilyIndexes[GRAPHICS_QUEUE_FAMILY];
	createInfo.queueCount = queueCounts[GRAPHICS_QUEUE_FAMILY];
	createInfo.pQueuePriorities = graphicsQueuePriorities;
	createInfos.push_back(createInfo);

	createInfo.queueFamilyIndex = queueFamilyIndexes[TRANSFER_QUEUE_FAMILY];
	createInfo.queueCount = queueCounts[TRANSFER_QUEUE_FAMILY];
	createInfo.pQueuePriorities = transferQueuePriorities;
	createInfos.push_back(createInfo);

	return createInfos;
}

void Device::CreateDevice() {
	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos = CreateQueueCreateInfos();

	VkPhysicalDeviceFeatures features{};

	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pEnabledFeatures = &features;
	createInfo.queueCreateInfoCount = queueCreateInfos.size();
	createInfo.pQueueCreateInfos = queueCreateInfos.data();
	createInfo.enabledLayerCount = 0;
	createInfo.enabledExtensionCount = deviceExtensions.size();
	createInfo.ppEnabledExtensionNames = deviceExtensions.data();
	createInfo.pNext = nullptr;
	

	if(vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
		std::cerr << "Failed to create a logical device" << std::endl;
	}

	for (uint32_t i = 0; i < queueCreateInfos.size(); i++) {
		free((void*)queueCreateInfos[i].pQueuePriorities);
		//dont give me shit its the best I could think of at 2 am
	}

	//retrieve queues
	for (uint32_t i = 0; i < queueCounts[GRAPHICS_QUEUE_FAMILY]; i++) {
		VkQueue queue;
		vkGetDeviceQueue(device, queueFamilyIndexes[GRAPHICS_QUEUE_FAMILY], i, &queue);
		queues[GRAPHICS_QUEUE_FAMILY].push_back(queue);
	}

	for (uint32_t i = 0; i < queueCounts[TRANSFER_QUEUE_FAMILY]; i++) {
		VkQueue queue;
		vkGetDeviceQueue(device, queueFamilyIndexes[TRANSFER_QUEUE_FAMILY], i, &queue);
		queues[TRANSFER_QUEUE_FAMILY].push_back(queue);
	}
}

VkDevice Device::GetDevice() {
	return device;
}

VkPhysicalDevice Device::GetPhysicalDevice() {
	return physicalDevice;
}

std::array<uint32_t, QUEUE_FAMILY_COUNT> Device::GetQueueFamilyIndices() {
	return queueFamilyIndexes;
}

void Device::CopyFrom(const Device& other) {
	useCount = other.useCount;
	device = other.device;
	physicalDevice = other.physicalDevice;
	instance = other.instance;
	queueFamilyIndexes = other.queueFamilyIndexes;
	queueCounts = other.queueCounts;
	queues = other.queues;
}

Device::~Device() {
	if (useCount.use_count() == 1) {
		vkDestroyDevice(device, nullptr);
	}
}

//11:16pm note section
/*
fixed pipelines can do whatever and can have anyting you want in them. 
*/
