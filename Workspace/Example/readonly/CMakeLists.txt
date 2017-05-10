cmake_minimum_required(VERSION 2.8)
project(cg_generator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(CG_GENERATOR
    ../readonly/common_readonly.h
    ../readonly/Game_readonly.h
    ../readonly/Game_readonly.cpp
    ../readonly/Entity_readonly.h
    ../readonly/Entity_readonly.cpp
    ../readonly/entities/Ship_readonly.h
    ../readonly/entities/Ship_readonly.cpp
    ../readonly/entities/Barrel_readonly.h
    ../readonly/entities/Barrel_readonly.cpp
    ../readonly/entities/Ball_readonly.h
    ../readonly/entities/Ball_readonly.cpp
    ../readonly/entities/Mine_readonly.h
    ../readonly/entities/Mine_readonly.cpp
    ../custom/common.h
    ../custom/Game.h
    ../custom/Game.cpp
    ../custom/Entity.h
    ../custom/Entity.cpp
    ../custom/entities/Ship.h
    ../custom/entities/Ship.cpp
    ../custom/entities/Barrel.h
    ../custom/entities/Barrel.cpp
    ../custom/entities/Ball.h
    ../custom/entities/Ball.cpp
    ../custom/entities/Mine.h
    ../custom/entities/Mine.cpp
)

add_executable(cg ../readonly/main_readonly.cpp)
target_link_libraries(cg CG_GENERATOR)

add_executable(cgcode ../readonly/mainMono_readonly.cpp)
set_target_properties(cgcode PROPERTIES COMPILE_FLAGS "-E -P -DEXPLICITE_EXCLUDE")