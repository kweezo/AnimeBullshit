#include "Display.h"

Display::Display(DisplayCreateInfo createInfo): swapchain(VK_NULL_HANDLE) {
	this->createInfo = createInfo;
	useCount.reset(new char);
	
	CreateSurface();
	CreateSwapchain();
	CreateSwapchainImageViews();
}

void Display::CreateSurface() {
	VkWin32SurfaceCreateInfoKHR surfaceCreateInfo{};

	surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	surfaceCreateInfo.hwnd = glfwGetWin32Window(createInfo.window->GetWindow());
	surfaceCreateInfo.hinstance = GetModuleHandle(nullptr);

	if (vkCreateWin32SurfaceKHR(createInfo.instance->GetInstance(), &surfaceCreateInfo, nullptr, &surface) != VK_SUCCESS) {
		std::cout << "Failed to create a win32 surface" << std::endl;
	}
}

void Display::CreateSwapchain() {
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(createInfo.device->GetPhysicalDevice(), surface, &surfaceCapabilities);

	uint32_t surfaceformatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(createInfo.device->GetPhysicalDevice(), surface, &surfaceformatCount, nullptr);

	std::vector<VkSurfaceFormatKHR> surfaceFormats(surfaceformatCount);
	vkGetPhysicalDeviceSurfaceFormatsKHR(createInfo.device->GetPhysicalDevice(), surface, &surfaceformatCount, surfaceFormats.data());

	for (VkSurfaceFormatKHR currFormat : surfaceFormats) {
		if (currFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR && currFormat.format == VK_FORMAT_B8G8R8A8_SRGB) {
			surfaceFormat = currFormat;
		}
	}

	VkSwapchainCreateInfoKHR swapchainCreateInfo{};

	swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	swapchainCreateInfo.surface = surface;
	swapchainCreateInfo.minImageCount = imageCount;
	swapchainCreateInfo.imageFormat = surfaceFormat.format;
	swapchainCreateInfo.imageColorSpace = surfaceFormat.colorSpace;
	swapchainCreateInfo.imageExtent = surfaceCapabilities.currentExtent;
	swapchainCreateInfo.imageArrayLayers = 1;
	swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	swapchainCreateInfo.oldSwapchain = swapchain;
	
	std::array<uint32_t, QUEUE_FAMILY_COUNT> queueFamilyIndices = createInfo.device->GetQueueFamilyIndices();
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

	if (vkCreateSwapchainKHR(createInfo.device->GetDevice(), &swapchainCreateInfo, nullptr, &swapchain) != VK_SUCCESS) {
		std::cerr << "Failed to create the swapchain" << std::endl;
	}

}

void Display::CreateSwapchainImageViews() {

	swapchainImageViews.clear();

	uint32_t swapchainImageCount;
	vkGetSwapchainImagesKHR(createInfo.device->GetDevice(), swapchain, &swapchainImageCount, nullptr);

	std::vector<VkImage> swapchainImages(swapchainImageCount);
	vkGetSwapchainImagesKHR(createInfo.device->GetDevice(), swapchain, &swapchainImageCount, swapchainImages.data());

	if (swapchainImageCount != imageCount) {
		std::cerr << "WARNING: insufficient amount of swapchain images created" << std::endl;
	}
	
	VkImageSubresourceRange subResRange{};
	subResRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	subResRange.baseMipLevel = 0;
	subResRange.levelCount = 1;
	subResRange.baseArrayLayer = 0;
	subResRange.layerCount = 1;

	VkImageViewCreateInfo imageViewCreateInfo{};

	imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	imageViewCreateInfo.format = surfaceFormat.format;
	imageViewCreateInfo.components = { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY,
		VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY };
	imageViewCreateInfo.subresourceRange = subResRange;

	swapchainImageViews.resize(swapchainImageCount);

	for (uint32_t i = 0; i < imageCount; i++) {
		imageViewCreateInfo.image = swapchainImages[i];
		
		if (vkCreateImageView(createInfo.device->GetDevice(), &imageViewCreateInfo, nullptr, &swapchainImageViews[i])
			!= VK_SUCCESS) {
			std::cerr << "Failed to create image view number " << i << std::endl;
		}
	}

}

VkExtent2D Display::GetSwapchainExtent() {
	return surfaceCapabilities.currentExtent;
}

VkFormat Display::GetSwapchainImageFormat() {
	return surfaceFormat.format;
}

std::vector<VkImageView> Display::GetSwapchainImageViews() {
	return swapchainImageViews;
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
		for (uint32_t i = 0; i < imageCount; i++) {
			vkDestroyImageView(createInfo.device->GetDevice(), swapchainImageViews[i], nullptr);
		}
		vkDestroySwapchainKHR(createInfo.device->GetDevice(), swapchain, nullptr);
		vkDestroySurfaceKHR(createInfo.instance->GetInstance(), surface, nullptr);
	}
}
