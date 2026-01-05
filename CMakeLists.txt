cmake_minimum_required(VERSION 3.20)
project(VulkanLearning)

file(
    GLOB 
    SOURCE_FILES
    "src/*.cpp"
)

file(
    GLOB
    HEADER_FILES
    "src/*.h"
)

set(DEFINITIONS "")

if(MSVC)
    add_compile_options(-Wall /WX /wd4820)
    list(APPEND DEFINITIONS "PLATFORM_WINDOWS")
else()
    add_compile_options(-Wall -Wextra -Werror)
    list(APPEND DEFINITIONS "PLATFORM_LINUX")
endif()

add_executable(
    ${PROJECT_NAME} 
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

set(ntt-glfw_DIR "${CMAKE_SOURCE_DIR}/cmake")
find_package(ntt-glfw REQUIRED) 

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    ntt-glfw
)

target_compile_definitions(
    ${PROJECT_NAME}
    PRIVATE
    ${DEFINITIONS}
)