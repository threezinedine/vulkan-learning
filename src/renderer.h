#pragma once
#include "common.h"
#include <vulkan/vulkan.h>

namespace ntt {

class Renderer
{
public:
	static void Initialize();
	static void Shutdown();

private:
	static bool s_isInitialize;

private:
	static void createInstance();
	static void getPhysicalDevices();

private:
	static VkInstance				s_instance;
	static vector<VkPhysicalDevice> s_physicalDevices;
};

} // namespace ntt
