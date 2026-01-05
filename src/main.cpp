#include "common.h"
#include <cstdio>

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

int main(void)
{
	ASSERT(glfwInit() == GLFW_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan Learning", NULLPTR, NULLPTR);
	ASSERT(window != NULLPTR);

	glfwMakeContextCurrent(window);

#if defined(PLATFORM_WINDOWS)
#pragma warning(push)
#pragma warning(disable : 4191)
#endif
	ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == GLFW_TRUE);
#if defined(PLATFORM_WINDOWS)
#pragma warning(pop)
#endif
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}