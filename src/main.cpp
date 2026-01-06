#include "common.h"
#include <cstdio>

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "renderer.h"

using namespace ntt;

int main(void)
{
	ASSERT(glfwInit() == GLFW_TRUE);

#if USE_VULKAN
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
#endif

	GLFWwindow* pWindow = glfwCreateWindow(800, 600, "Vulkan Learning", NULLPTR, NULLPTR);
	ASSERT(pWindow != NULLPTR);

	glfwMakeContextCurrent(pWindow);

#if !USE_VULKAN
#if defined(PLATFORM_WINDOWS)
#pragma warning(push)
#pragma warning(disable : 4191)
#endif
	ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == GLFW_TRUE);
#if defined(PLATFORM_WINDOWS)
#pragma warning(pop)
#endif
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
#endif

	Renderer::Initialize();

	while (!glfwWindowShouldClose(pWindow))
	{
		glfwPollEvents();

		if (glfwGetKey(pWindow, GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(pWindow, true);
		}

#if !USE_VULKAN
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#endif
		glfwSwapBuffers(pWindow);
	}

	Renderer::Shutdown();

	glfwDestroyWindow(pWindow);
	glfwTerminate();

	return 0;
}