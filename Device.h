#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <array>

#include <vulkan/vulkan.h>

#define GRAPHICS_QUEUE_FAMILY 0
#define TRANSFER_QUEUE_FAMILY 1

#define QUEUE_FAMILY_COUNT 2

typedef struct {
	VkInstance instance;
}DeviceCreateInfo;

class Device
{
public:
	Device(DeviceCreateInfo createInfo);
	Device(const Device& other);
	Device& operator=(const Device& other);

	~Device();

	VkDevice GetDevice();
	VkPhysicalDevice GetPhysicalDevice();

	std::array<uint32_t, QUEUE_FAMILY_COUNT> GetQueueFamilyIndices();
private:
	void CopyFrom(const Device& other);

	void PickPhysicalDevice();
	void CreateDevice();
	void MapQueueFamilyIndexes();
	std::vector<VkDeviceQueueCreateInfo> CreateQueueCreateInfos();

	std::shared_ptr<char> useCount;


	std::array<uint32_t, QUEUE_FAMILY_COUNT> queueFamilyIndexes;
	std::array<uint32_t, QUEUE_FAMILY_COUNT> queueCounts;
	std::array<std::vector<VkQueue>, QUEUE_FAMILY_COUNT> queues;

	VkDevice device;
	VkPhysicalDevice physicalDevice;

	VkInstance instance;
};

