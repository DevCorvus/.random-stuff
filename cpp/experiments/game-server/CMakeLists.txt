cmake_minimum_required(VERSION 3.10)

project(GameServerProject)

add_executable(server src/game.hpp src/udp.hpp src/udp.cpp src/server.cpp)
add_executable(client src/game.hpp src/udp.hpp src/udp.cpp src/client.cpp)
