cmake_minimum_required(VERSION 3.20)
project(Bounce)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(Bounce src/main.cpp src/World.cpp headers/World.h src/Ball.cpp headers/Ball.h src/Player.cpp headers/Player.h src/Environment.cpp headers/Environment.h src/Spike.cpp headers/Spike.h src/View.cpp headers/View.h src/FlyingView.cpp headers/FlyingView.h src/Engine.cpp headers/Engine.h src/Level.cpp headers/Level.h lib/tinyxml2.cpp include/tinyxml2/tinyxml2.h src/Surface.cpp headers/Surface.h src/ActorListener.cpp headers/ActorListener.h)


target_link_libraries(Bounce sfml-graphics sfml-audio)
target_link_libraries(Bounce ${PROJECT_SOURCE_DIR}/lib/libbox2d.a)



