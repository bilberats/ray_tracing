cmake_minimum_required(VERSION 3.21)
project(ray_tracing)

set(CMAKE_CXX_STANDARD 14)

add_executable(ray_tracing main.cpp Vector3.cpp Vector3.h Image.h Image.cpp Image.h Shape.cpp Shape.h Sphere.cpp Sphere.h Camera.cpp Camera.h Quaternion.cpp Quaternion.h Scene.cpp Scene.h Render.cpp Render.h Inputs.cpp Inputs.h Color.cpp Color.h Triangle.cpp Triangle.h multithreadingFunc.cpp multithreadingFunc.h JSON.cpp JSON.h JSON.cpp JSON.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR G:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network main REQUIRED)

include_directories(G:/SFML/include)
target_link_libraries(ray_tracing sfml-system sfml-window sfml-graphics sfml-audio sfml-main)