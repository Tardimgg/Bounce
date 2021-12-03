cmake_minimum_required(VERSION 3.20)
project(Bounce)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(Bounce src/main.cpp src/World.cpp headers/World.h src/Ball.cpp headers/Ball.h src/surfaces/blockType/Block.cpp headers/surfaces/blockType/Block.h src/Environment.cpp headers/Environment.h src/surfaces/Spike.cpp headers/surfaces/Spike.h src/FlyingView.cpp headers/FlyingView.h src/Engine.cpp headers/Engine.h src/Level.cpp headers/Level.h lib/tinyxml2.cpp include/tinyxml2/tinyxml2.h src/surfaces/Surface.cpp headers/surfaces/Surface.h src/ActorListener.cpp headers/ActorListener.h src/surfaces/blockType/LeftHalfBlock.cpp headers/surfaces/blockType/LeftHalfBlock.h src/surfaces/ringType/Ring.cpp headers/surfaces/ringType/Ring.h src/surfaces/ringType/RotatedRing.cpp headers/surfaces/ringType/RotatedRing.h src/surfaces/EndLevel.cpp headers/surfaces/EndLevel.h src/surfaces/blockType/RightHalfBlock.cpp headers/surfaces/blockType/RightHalfBlock.h src/surfaces/Diminutive.cpp headers/surfaces/Diminutive.h src/surfaces/Magnifier.cpp headers/surfaces/Magnifier.h src/surfaces/ringType/BigRing.cpp headers/surfaces/ringType/BigRing.h src/surfaces/ringType/RotatedBigRing.cpp headers/surfaces/ringType/RotatedBigRing.h src/surfaces/ringType/RingType.cpp headers/surfaces/ringType/RingType.h src/surfaces/ringType/RotatedRingType.cpp headers/surfaces/ringType/RotatedRingType.h src/Spider.cpp headers/Spider.h src/surfaces/JumpBlock.cpp headers/surfaces/JumpBlock.h src/surfaces/blockType/BlockType.cpp headers/surfaces/blockType/BlockType.h src/surfaces/blockType/TopLeftHalfBlock.cpp headers/surfaces/blockType/TopLeftHalfBlock.h src/surfaces/blockType/TopRightHalfBlock.cpp headers/surfaces/blockType/TopRightHalfBlock.h)

add_subdirectory(lib/box2d-2.4.1)

target_link_libraries(Bounce box2d)

target_link_libraries(Bounce sfml-graphics sfml-audio)
