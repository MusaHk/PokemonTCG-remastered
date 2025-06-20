cmake_minimum_required(VERSION 3.29) # Will not work on any previous version
project(PokemonTCG-Remastered) # Define your project name

# 'set(var_name value' is used to create/assign value to variables
set(CMAKE_CXX_STANDARD 20) # Select the C++ Release to use
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Set the selected release as a hard req

include(FetchContent) # Library/Feature to download over http

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
) # Define the repo to download

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # Raylib specific settings, ignore
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
        raygui
        GIT_REPOSITORY https://github.com/raysan5/raygui.git
        GIT_TAG 4.0
) # Define the repo to download

FetchContent_MakeAvailable(raylib raygui) # Clone the above defined repos

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/ScreenSource/WelcomeScreen.cpp
        src/ScreenSource/ScreenManager.cpp
        src/ScreenSource/BattleScreen.cpp
        src/String.cpp
        src/Logger.cpp
        src/GameContext.cpp
        src/PokemonSource/UltraNecrozma.cpp
        src/ActionSource/AttackAction.cpp
        src/ActionSource/ScanAction.cpp
        src/ActionSource/AltarSacrificeAction.cpp
        src/Player.cpp
        src/Game.cpp
        src/PokemonSource/Dialga.cpp
        src/PokemonSource/MegaRayquaza.cpp
        src/PokemonSource/ZygardeComplete.cpp
        src/PokemonSource/Mewtwo.cpp
        src/PokemonSource/Darkrai.cpp
        src/PokemonSource/Reshiram.cpp
        src/PokemonSource/Zekrom.cpp
        src/PokemonSource/Palkia.cpp
        src/PokemonSource/Giratina.cpp) # Choose files to compile

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Needed for properly linking raygui
set(GENERATED_HEADERS_DIR "${CMAKE_BINARY_DIR}/generated")
file(MAKE_DIRECTORY ${GENERATED_HEADERS_DIR}) # Creates the specified dir

# Self explanatory, just copying the raygui headers
file(COPY "${raygui_SOURCE_DIR}/src/raygui.h" DESTINATION
        "${GENERATED_HEADERS_DIR}")

# Including the copied headers into your project
target_include_directories(${PROJECT_NAME} PRIVATE
        ${GENERATED_HEADERS_DIR}
)

# Similar here
target_link_libraries(${PROJECT_NAME} raylib)