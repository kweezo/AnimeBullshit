#include "Window.h"
#include "Instance.h"
#include "Device.h"
#include "Display.h"
#include "Shader.h"
#include "Pipeline.h"
#include "Algebra.h"

int main(int argc, char** argv) {
	WindowCreateInfo windowCreateInfo{};
	windowCreateInfo.dimensions = { 800, 600 };
	windowCreateInfo.fullscreen = false;
	windowCreateInfo.title = "the higher forces have always acted cowardly";

	Window window = Window(windowCreateInfo);
	Instance instance = Instance();
	
	DeviceCreateInfo deviceCreateInfo;
	deviceCreateInfo.instance = instance.GetInstance();

	Device device = Device(deviceCreateInfo);

	DisplayCreateInfo displayCreateInfo;
	displayCreateInfo.instance = &instance;
	displayCreateInfo.window = &window;
	displayCreateInfo.device = &device;

	Display display = Display(displayCreateInfo);

	ShaderCreateInfo shaderCreateInfo{};

	shaderCreateInfo.vertexPath = "vert.spv";
	shaderCreateInfo.fragmentPath = "frag.spv";
	shaderCreateInfo.device = &device;

	Shader shader = Shader(shaderCreateInfo);

	PipelineCreateInfo pipelineCreateInfo{};
	pipelineCreateInfo.device = &device;
	pipelineCreateInfo.display = &display;
	pipelineCreateInfo.shader = &shader;

	Pipeline pipeline = Pipeline(pipelineCreateInfo);

	m4 m1 = { 1.0f };
	m4 m2= { 1.0f };

	m2 *= m1;

	for (int i = 0; i < 16; i++) {
		std::cout << m2.dat[i] << std::endl;
	}

	while (true) {
		if (window.UpdateWindow()) {
			break;
		}
	}

	return 0;
}