#include "Window.h"
#include "Instance.h"
#include "Device.h"
#include "Display.h"

int main(int argc, char** argv) {
	WindowCreateInfo windowCreateInfo{};
	windowCreateInfo.dimensions = { 800, 600 };
	windowCreateInfo.fullscreen = false;
	windowCreateInfo.title = "the higher forces have always acted cowardly";

	Window window = Window(&windowCreateInfo);
	Instance instance = Instance();
	
	DeviceCreateInfo deviceCreateInfo;
	deviceCreateInfo.instance = instance.GetInstance();

	Device device = Device(&deviceCreateInfo);

	DisplayCreateInfo displayCreateInfo;
	displayCreateInfo.instance = &instance;
	displayCreateInfo.window = &window;
	displayCreateInfo.device = &device;

	Display display = Display(&displayCreateInfo);

	while (true) {
		if (window.UpdateWindow()) {
			break;
		}
	}
}