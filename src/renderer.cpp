#include "renderer.h"

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

namespace ntt {

bool					 Renderer::s_isInitialize	 = false;
VkInstance				 Renderer::s_instance		 = VK_NULL_HANDLE;
vector<VkPhysicalDevice> Renderer::s_physicalDevices = {};

vector<const char*> requiredIntanceLayers	   = {};
vector<const char*> requiredInstanceExtensions = {};

void Renderer::Initialize()
{
	ASSERT(!s_isInitialize);

	createInstance();
	getPhysicalDevices();

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

void Renderer::getPhysicalDevices()
{
	u32 physicalDevicesCount;
	VK_ASSERT(vkEnumeratePhysicalDevices(s_instance, &physicalDevicesCount, nullptr));

	s_physicalDevices.resize(physicalDevicesCount);
	VK_ASSERT(vkEnumeratePhysicalDevices(s_instance, &physicalDevicesCount, s_physicalDevices.data()));

	for (u32 physicalDeviceIndex = 0; physicalDeviceIndex < physicalDevicesCount; ++physicalDeviceIndex)
	{
		VkPhysicalDevice&		   physicalDevice = s_physicalDevices[physicalDeviceIndex];
		VkPhysicalDeviceProperties deviceProperties;
		vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);

		printf("===================== Device %d =======================\n", physicalDeviceIndex);
		printf("\tDevice Name: %s\n", deviceProperties.deviceName);

		if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_OTHER)
		{
			printf("\tDevice Type: %s\n", "other");
		}
		else if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)
		{
			printf("\tDevice Type: %s\n", "integerated gpu");
		}
		else if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
		{
			printf("\tDevice Type: %s\n", "discrete gpu");
		}
		else if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU)
		{
			printf("\tDevice Type: %s\n", "virtual");
		}
		else if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_CPU)
		{
			printf("\tDevice Type: %s\n", "cpu");
		}
		else
		{
			UNREACHABLE();
		}

		VkPhysicalDeviceFeatures deviceFeatures;
		vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);

		printf("\n\tDevice Features:\n");
		printf("\t\tSupport Geometry Shader: %s\n", deviceFeatures.geometryShader ? "true" : "false");
		printf("\t\tSupport Multi Viewport: %s\n", deviceFeatures.multiViewport ? "true" : "false");

		u32 queueFamiliesCount;
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamiliesCount, nullptr);

		vector<VkQueueFamilyProperties> queueFamilies(queueFamiliesCount);
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamiliesCount, queueFamilies.data());

		printf("\n\tQueue families:\n");

		for (u32 queueFamilyIndex = 0u; queueFamilyIndex < queueFamiliesCount; ++queueFamilyIndex)
		{
			VkQueueFamilyProperties& queueFamilyProperties = queueFamilies[queueFamilyIndex];
			printf("\t\tQueue Family %d:\n", i32(queueFamilyIndex));
			printf("\t\t\tSupport graphics: %s\n",
				   queueFamilyProperties.queueFlags & VK_QUEUE_GRAPHICS_BIT ? "true" : "false");
			printf("\t\t\tSupport compute: %s\n",
				   queueFamilyProperties.queueFlags & VK_QUEUE_COMPUTE_BIT ? "true" : "false");
			printf("\t\t\tSupport transfer: %s\n",
				   queueFamilyProperties.queueFlags & VK_QUEUE_TRANSFER_BIT ? "true" : "false");
		}

		VkPhysicalDeviceMemoryProperties memoryProperties;
		vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memoryProperties);

		printf("\n\tMemory Heaps:\n");
		printf("\t\tMemory Types:\n");

		for (u32 memoryTypeIndex = 0u; memoryTypeIndex < memoryProperties.memoryTypeCount; ++memoryTypeIndex)
		{
			VkMemoryType& type = memoryProperties.memoryTypes[memoryTypeIndex];
			printf("\t\t\tMemory Type %d:\n", i32(memoryTypeIndex));
			printf("\t\t\t\tHeap Index: %d\n", type.heapIndex);
			printf("\t\t\t\tLocal: %s\n", type.propertyFlags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT ? "true" : "false");
			printf("\t\t\t\tHost visible: %s\n",
				   type.propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT ? "true" : "false");
			printf("\t\t\t\tHost coherent: %s\n",
				   type.propertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT ? "true" : "false");
		}

		printf("\n\t\tHeaps:\n");

		for (u32 heapIndex = 0u; heapIndex < memoryProperties.memoryHeapCount; ++heapIndex)
		{
			printf("\t\t\tHeap: %d\n", i32(heapIndex));
			VkMemoryHeap& heap = memoryProperties.memoryHeaps[heapIndex];
			printf("\t\t\t\tSize: %.1f GB\n", float(heap.size) / 1024 / 1024 / 1024);
			printf("\t\t\t\tDevice Local: %s\n", heap.flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT ? "true" : "false");
		}

		printf("\n\n");
	}
}

void Renderer::Shutdown()
{
	ASSERT(s_isInitialize);

	vkDestroyInstance(s_instance, nullptr);
}

} // namespace ntt
