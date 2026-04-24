cmake_minimum_required(VERSION 3.28)
project(BlackjackPA9 LANGUAGES CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
 
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)
 
add_executable(HaddixManono_PA9
    src/main.cpp
    src/GameObject.cpp
    src/Card.cpp
    src/Button.cpp
)
target_compile_features(HaddixManono_PA9 PRIVATE cxx_std_17)
target_link_libraries(HaddixManono_PA9 PRIVATE SFML::Graphics)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT HaddixManono_PA9)
 
# Copy the assets folder next to the exe so it can find fonts/images at runtime
if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/assets)
    file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()
