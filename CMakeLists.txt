cmake_minimum_required(VERSION 3.20)
project(Bounce)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(Bounce src/main.cpp src/World.cpp headers/World.h src/Ball.cpp headers/Ball.h src/surfaces/Block.cpp headers/surfaces/Block.h src/Environment.cpp headers/Environment.h src/surfaces/Spike.cpp headers/surfaces/Spike.h src/FlyingView.cpp headers/FlyingView.h src/Engine.cpp headers/Engine.h src/Level.cpp headers/Level.h lib/tinyxml2.cpp include/tinyxml2/tinyxml2.h src/surfaces/Surface.cpp headers/surfaces/Surface.h src/ActorListener.cpp headers/ActorListener.h src/surfaces/HalfBlock.cpp headers/surfaces/HalfBlock.h src/surfaces/Ring.cpp headers/surfaces/Ring.h)


target_link_libraries(Bounce sfml-graphics sfml-audio)
target_link_libraries(Bounce ${PROJECT_SOURCE_DIR}/lib/libbox2d.a)



