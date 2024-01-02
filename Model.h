#pragma once

#include <iostream>
#include <vector>

#include <vulkan/vulkan.h>

#define SHAPE_BOX 0
#define SHAPE_CONE 1 // will add more when i feel like it

typedef struct ModelCreateInfoShape {
	uint8_t shape;
};

class Model
{
public:

private:
	std::vector<float> vertices; // cleared after creating the buffer
};

