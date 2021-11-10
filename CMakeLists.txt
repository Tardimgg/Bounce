cmake_minimum_required(VERSION 3.20)
project(Bounce)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(Bounce src/main.cpp src/World.cpp headers/World.h src/Ball.cpp headers/Ball.h src/Player.cpp headers/Player.h src/Environment.cpp headers/Environment.h src/Spike.cpp headers/Spike.h src/View.cpp headers/View.h src/FlyingView.cpp headers/FlyingView.h src/Engine.cpp headers/Engine.h)

target_link_libraries(Bounce sfml-graphics sfml-audio)
