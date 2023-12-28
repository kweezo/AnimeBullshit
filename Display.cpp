#include "Display.h"

Display::Display(DisplayCreateInfo* createInfo) {
	this->createInfo = createInfo;
	useCount.reset(new char);
	
	CreateSurface();
	CreateSwapchain();
}

void Display::CreateSurface() {
	VkWin32SurfaceCreateInfoKHR surfaceCreateInfo{};

	surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	surfaceCreateInfo.hwnd = glfwGetWin32Window(createInfo->window->GetWindow());
	surfaceCreateInfo.hinstance = GetModuleHandle(nullptr);

	if (vkCreateWin32SurfaceKHR(createInfo->instance->GetInstance(), &surfaceCreateInfo, nullptr, &surface) != VK_SUCCESS) {
		std::cout << "Failed to create a win32 surface" << std::endl;
	}
}

void Display::CreateSwapchain() {
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(createInfo->device->GetPhysicalDevice(), surface, &surfaceCapabilities);

	uint32_t surfaceformatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(createInfo->device->GetPhysicalDevice(), surface, &surfaceformatCount, nullptr);

	std::vector<VkSurfaceFormatKHR> surfaceFormats(surfaceformatCount);
	vkGetPhysicalDeviceSurfaceFormatsKHR(createInfo->device->GetPhysicalDevice(), surface, &surfaceformatCount, surfaceFormats.data());

	VkSurfaceFormatKHR bestFormat = surfaceFormats[0];

	for (VkSurfaceFormatKHR surfaceFormat : surfaceFormats) {
		if (surfaceFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR && surfaceFormat.format == VK_FORMAT_B8G8R8A8_SRGB) {
			bestFormat = surfaceFormat;
		}
	}

	VkSwapchainCreateInfoKHR swapchainCreateInfo{};

	swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	swapchainCreateInfo.surface = surface;
	swapchainCreateInfo.minImageCount = imageCount;
	swapchainCreateInfo.imageFormat = bestFormat.format;
	swapchainCreateInfo.imageColorSpace = bestFormat.colorSpace;
	swapchainCreateInfo.imageExtent = surfaceCapabilities.currentExtent;
	swapchainCreateInfo.imageArrayLayers = 1;
	swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	
	std::array<uint32_t, QUEUE_FAMILY_COUNT> queueFamilyIndices = createInfo->device->GetQueueFamilyIndices();
	std::array<uint32_t, 2> neededQueueFamilyIndices = { queueFamilyIndices[GRAPHICS_QUEUE_FAMILY],
		queueFamilyIndices[TRANSFER_QUEUE_FAMILY] };

	if (queueFamilyIndices[GRAPHICS_QUEUE_FAMILY] == queueFamilyIndices[TRANSFER_QUEUE_FAMILY]) {
		swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	}
	else {

		swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		swapchainCreateInfo.queueFamilyIndexCount = 2;
		swapchainCreateInfo.pQueueFamilyIndices = neededQueueFamilyIndices.data();
	}

	swapchainCreateInfo.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
	swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	swapchainCreateInfo.presentMode = VK_PRESENT_MODE_FIFO_KHR;
	swapchainCreateInfo.clipped = VK_TRUE;

	if (vkCreateSwapchainKHR(createInfo->device->GetDevice(), &swapchainCreateInfo, nullptr, &swapchain) != VK_SUCCESS) {
		std::cerr << "Failed to create the swapchain" << std::endl;
	}
}

Display::Display(const Display& other) {
	CopyFrom(other);
}

Display& Display::operator=(const Display& other) {
	if (this == &other) {
		return *this;
	}

	CopyFrom(other);

	return *this;
}

void Display::CopyFrom(const Display& other) {
	createInfo = other.createInfo;
	surface = other.surface;
	useCount = other.useCount;
}

Display::~Display() {
	if (useCount.use_count() == 1) {
		vkDestroySwapchainKHR(createInfo->device->GetDevice(), swapchain, nullptr);
		vkDestroySurfaceKHR(createInfo->instance->GetInstance(), surface, nullptr);
	}
}
