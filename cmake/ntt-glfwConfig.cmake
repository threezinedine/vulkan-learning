set(LIB_NAME ntt-glfw)

if (TARGET ${LIB_NAME})
    return()
endif()

include(FetchContent)

if (NOT TARGET glfw)
    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
    )

    FetchContent_MakeAvailable(glfw)

    if (UNIX)
        target_compile_options(
            glfw
            PRIVATE 
            -Wno-unused-parameter
            -Wno-missing-field-initializers
            -Wno-sign-compare
        )
    endif()
endif()

if (NOT TARGET GLAD)
    FetchContent_Declare(
        GLAD
        GIT_REPOSITORY https://github.com/threezinedine/glad.git
    )

    FetchContent_MakeAvailable(GLAD)

    if (MSVC)
        target_compile_options(
            glad
            PRIVATE 
            /wd4668
            /wd4191
            /wd5045
        )
    else()
        target_compile_options(
            glad
            PRIVATE 
            -Wno-unused-parameter
        )
    endif()
endif()

if (NOT TARGET OpenGL)
    find_package(OpenGL REQUIRED)
endif()

add_library(
    ${LIB_NAME}
    INTERFACE
)

target_link_libraries(
    ${LIB_NAME}
    INTERFACE
    glfw
    glad
    OpenGL::GL
)