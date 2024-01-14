# OpenGLLab1

## Overview

This project serves as a basic template for an OpenGL application. It utilizes GLEW (The OpenGL Extension Wrangler Library) and GLFW (a multi-platform library for OpenGL, OpenGL ES, and Vulkan development) to simplify OpenGL initialization and window management.

## Getting Started

To use this solution, follow these steps:

### 1. Add NuGet Packages

- [GLEW](https://www.nuget.org/packages/glew.v140): GLEW is a cross-platform open-source C/C++ extension loading library. It provides efficient run-time mechanisms for determining which OpenGL extensions are supported on the target platform.

- [GLFW](https://www.nuget.org/packages/glfw): GLFW is a lightweight and multi-platform library for handling windows, contexts, and input. It is particularly useful for creating and managing OpenGL contexts.

### 2. Link Dependencies

Follow these steps to link the necessary dependencies:

- Navigate to `Project -> Properties -> Linker -> Input -> Additional Dependencies`.
- Click `Edit` and add `opengl32.lib` to the list.

## Building and Running

After adding the required NuGet packages and linking dependencies, build and run the project. Ensure that the necessary OpenGL runtime files are available on your system.

## Contributing

Feel free to contribute to the project by opening issues or submitting pull requests. If you encounter any problems or have suggestions for improvements, please let us know.
