cmake_minimum_required(VERSION 3.6)
project(Particle_Fire_Explosion)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")



include_directories(${PROJECT_SOURCE_DIR}/include libSDL2-2.0.so.0)
link_directories(/usr/local/lib)

set(SOURCE_FILES main.cpp Classes/Screen.cpp Classes/Particles.cpp Classes/Swarm.cpp)

#target_link_libraries(Particle_Fire_Explosion SDL2)

add_executable(Particle_Fire_Explosion ${SOURCE_FILES})

target_link_libraries(Particle_Fire_Explosion SDL2main SDL2)