cmake_minimum_required(VERSION 3.16)
project(Lab2)

# Установим стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(SOURCES
src/aggressivestrategy.cpp
src/blackjack.cpp
src/card.cpp
src/console.cpp
src/deck.cpp
src/detailedsimulation.cpp
src/fastsimulation.cpp
src/loader.cpp
src/player.cpp
src/simulation.cpp
    src/dynamicstrategy.cpp
    src/simplestrategy.cpp
    src/smartstrategy.cpp
    src/tournamentsimulation.cpp

    main.cpp
)

set(HEADERS
    headers/aggressivestrategy.h
    headers/card.h
    headers/blackjack.h
    headers/deck.h
    headers/console.h
    headers/simulationfactory.h
    headers/simulationregistrar.h
    headers/strategyregistrar.h
    headers/factory.h
    headers/player.h
    headers/simulation.h
    headers/strategy.h
    headers/detailedsimulation.h
    headers/fastsimulation.h
    headers/tournamentsimulation.h
    headers/loader.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)


