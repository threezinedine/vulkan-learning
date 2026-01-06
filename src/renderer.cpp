#include "renderer.h"
#include <vector>
using namespace std;

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

namespace ntt {

bool	   Renderer::s_isInitialize = false;
VkInstance Renderer::s_instance		= VK_NULL_HANDLE;

vector<const char*> requiredIntanceLayers	   = {};
vector<const char*> requiredInstanceExtensions = {};

void Renderer::Initialize()
{
	ASSERT(!s_isInitialize);

	createInstance();

	s_isInitialize = true;
}

void Renderer::createInstance()
{
	VkApplicationInfo appInfo  = {};
	appInfo.sType			   = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName   = "Application";
	appInfo.applicationVersion = VK_API_VERSION_1_1;
	appInfo.pEngineName		   = "No Engine";
	appInfo.engineVersion	   = VK_API_VERSION_1_1;

	u32					glfwExtensionsCount;
	const char**		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionsCount);
	vector<const char*> finalRequiredExtension(glfwExtensionsCount + requiredInstanceExtensions.size());

	for (u32 glfwExtensionIndex = 0; glfwExtensionIndex < glfwExtensionsCount; ++glfwExtensionIndex)
	{
		finalRequiredExtension[glfwExtensionIndex] = glfwExtensions[glfwExtensionIndex];
	}

	u32 requiredInstanceExtensionsCount = requiredInstanceExtensions.size();
	for (u32 insRequiredExtensionIndex = 0; insRequiredExtensionIndex < requiredInstanceExtensionsCount;
		 ++insRequiredExtensionIndex)
	{
		finalRequiredExtension[glfwExtensionsCount + insRequiredExtensionIndex] =
			requiredInstanceExtensions[insRequiredExtensionIndex];
	}

	VkInstanceCreateInfo insInfo	= {};
	insInfo.sType					= VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	insInfo.pApplicationInfo		= &appInfo;
	insInfo.enabledLayerCount		= u32(requiredIntanceLayers.size());
	insInfo.ppEnabledLayerNames		= requiredInstanceExtensions.data();
	insInfo.enabledExtensionCount	= u32(finalRequiredExtension.size());
	insInfo.ppEnabledExtensionNames = finalRequiredExtension.data();

	VK_ASSERT(vkCreateInstance(&insInfo, nullptr, &s_instance));
}

void Renderer::Shutdown()
{
	ASSERT(s_isInitialize);

	vkDestroyInstance(s_instance, nullptr);
}

} // namespace ntt
