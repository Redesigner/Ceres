cmake_minimum_required(VERSION 3.20.2)
project(ceres VERSION 0.0.1 LANGUAGES CXX)


# Look in build/cmake for modules
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# CMake modules
include(custom-utils)


# Main executable
add_executable(ceres src/Ceres/main.cpp)
target_sources(ceres PRIVATE

	src/Ceres/Game.cpp

	src/Ceres/Core/Program.cpp

	src/Ceres/Core/Common/Matrix.cpp
	src/Ceres/Core/Common/Matrix2D.cpp
	src/Ceres/Core/Common/Transform.cpp
	src/Ceres/Core/Common/Vector2.cpp
	src/Ceres/Core/Common/Vector3.cpp
	src/Ceres/Core/Common/VertexList.cpp

	
	# Components
	src/Ceres/Core/Components/Base/ComponentList.cpp
	src/Ceres/Core/Components/Base/ComponentParameters.cpp
	src/Ceres/Core/Components/Base/ComponentRef.cpp
	src/Ceres/Core/Components/Base/Message.cpp
	src/Ceres/Core/Components/Base/IComponent.cpp

	src/Ceres/Core/Components/RenderComponent.cpp
	src/Ceres/Core/Components/ControllerComponent.cpp
	src/Ceres/Core/Components/CameraComponent.cpp
	src/Ceres/Core/Components/PhysicsComponent.cpp
	src/Ceres/Core/Components/MovementComponent.cpp


	src/Ceres/Core/Entities/Base/IEntity.cpp

	src/Ceres/Core/Entities/Actor.cpp
	src/Ceres/Core/Entities/Block.cpp

	# Graphics
	src/Ceres/Core/Graphics/Context.cpp
	src/Ceres/Core/Graphics/CubeMap.cpp
	src/Ceres/Core/Graphics/Effect.cpp
	src/Ceres/Core/Graphics/GraphicsDevice.cpp
	src/Ceres/Core/Graphics/IndexBuffer.cpp
	src/Ceres/Core/Graphics/Mesh.cpp
	src/Ceres/Core/Graphics/Shadowmap.cpp
	src/Ceres/Core/Graphics/Skybox.cpp
	src/Ceres/Core/Graphics/Sprite.cpp
	src/Ceres/Core/Graphics/Texture.cpp
	src/Ceres/Core/Graphics/VertexStream.cpp
	src/Ceres/Core/Graphics/VertexArrayObject.cpp
	src/Ceres/Core/Graphics/VertexBufferObject.cpp
	src/Ceres/Core/Graphics/Window.cpp

	# Predefined Mesh Primitives
	src/Ceres/Core/Graphics/Primitives/MeshPrimitive.cpp
	src/Ceres/Core/Graphics/Primitives/Cube.cpp
	src/Ceres/Core/Graphics/Primitives/Sphere.cpp

	src/Ceres/Core/Graphics/VertexTypes/VertexPositionLayout.cpp
	src/Ceres/Core/Graphics/VertexTypes/VertexPositionNormalLayout.cpp
	src/Ceres/Core/Graphics/VertexTypes/VertexPositionNormalColorLayout.cpp
	src/Ceres/Core/Graphics/VertexTypes/VertexPositionNormalTextureLayout.cpp
	src/Ceres/Core/Graphics/VertexTypes/VertexPositionTextureLayout.cpp


	# I/O
	src/Ceres/Core/Input/Axis.cpp
	src/Ceres/Core/Input/Axis2D.cpp
	src/Ceres/Core/Input/Buttons.cpp
	src/Ceres/Core/Input/InputHandler.cpp
	src/Ceres/Core/Input/Joystick.cpp

	src/Ceres/Core/IO/ContentManager.cpp

	# Physics
	src/Ceres/Core/Physics/ConvexHull.cpp
	src/Ceres/Core/Physics/IPrimitive.cpp
	src/Ceres/Core/Physics/Primitives/CapsulePrimitive.cpp
	src/Ceres/Core/Physics/Primitives/CubePrimitive.cpp
	src/Ceres/Core/Physics/Primitives/SpherePrimitive.cpp
	src/Ceres/Core/Physics/PhysicsUtilities.cpp
	src/Ceres/Core/Physics/SweepResult.cpp

	src/Ceres/Core/Physics/GJK/GJK.cpp
	src/Ceres/Core/Physics/GJK/Simplex.cpp

	# Services
	src/Ceres/Core/Services/IService.cpp
	src/Ceres/Core/Services/ServiceContainer.cpp

	src/Ceres/Core/Services/ActorService.cpp
	src/Ceres/Core/Services/RenderService.cpp
	src/Ceres/Core/Services/PhysicsService.cpp
	src/Ceres/Core/Services/InputService.cpp

	src/Ceres/Core/World/World.cpp
)
target_include_directories(ceres PUBLIC src/Ceres/)

# Compiler options
target_compile_features(ceres PRIVATE cxx_std_17)
#target_enable_all_warnings(ceres)

# Set output directiories
set_target_properties(ceres PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin/release)
set_target_properties(ceres PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin/debug)
set_target_properties(ceres PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/bin/releasewdebug)

# Required packages
find_package(SDL2 REQUIRED)
find_package(SDL2-image REQUIRED)
find_package(fmt REQUIRED)
find_package(GLEW REQUIRED)

# Link packages
target_link_libraries(ceres PRIVATE SDL2::SDL2)
target_link_libraries(ceres PRIVATE SDL2::SDL2_image)
target_link_libraries(ceres PRIVATE fmt::fmt)
target_link_libraries(ceres PRIVATE GLEW::GLEW)


# Windows specific
if (WIN32)
	# Link SDL2main on windows to allow for a portable main()
	target_compile_definitions(ceres PRIVATE SDL_MAIN_HANDLED)
	target_link_libraries(ceres PRIVATE SDL2::SDL2main)
endif()
