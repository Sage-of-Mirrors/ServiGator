cmake_minimum_required(VERSION 3.8)
project(servigator)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SERVIGATOR_SRC
    # servigator
    "inc/*.h"
    
    "src/ServiGator/*.cpp"
    "src/ServiGator/*.h"
    "src/ServiGator/*.hpp"
)

add_library(servigator SHARED ${SERVIGATOR_SRC})
set_target_properties(servigator PROPERTIES OUTPUT_NAME "ServiGator" SUFFIX ".asi")

target_include_directories(servigator PUBLIC inc)
target_link_libraries(servigator PUBLIC ${PROJECT_SOURCE_DIR}/lib/ScriptHookRDR2.lib)