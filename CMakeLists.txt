cmake_minimum_required (VERSION 3.12)

project ("NAM_to_NeuralPi" VERSION 1.0.0
                     DESCRIPTION "A simple Tool to convert NAM files to NeuralPi/Proteus"
                     HOMEPAGE_URL "https://github.com/Thomas-Sparber/NAM_to_NeuralPi")

file(GLOB_RECURSE NAM_SOURCES Source/*.cpp Source*.h)

include_directories(${PROJECT_NAME} Dependencies/AudioFile)
include_directories(${PROJECT_NAME} Dependencies/NeuralAmpModelerCore/Dependencies/eigen)
include_directories(${PROJECT_NAME} Dependencies/NeuralAmpModelerCore/Dependencies/nlohmann)
include_directories(${PROJECT_NAME} Dependencies/NeuralAmpModelerCore)
add_subdirectory(Dependencies/NeuralAmpModelerCore)

add_executable (${PROJECT_NAME} ${NAM_SOURCES})
target_compile_features (${PROJECT_NAME} INTERFACE cxx_std_17)
target_compile_options(${PROJECT_NAME} PUBLIC -O3)
target_link_libraries(${PROJECT_NAME} PRIVATE NAM)