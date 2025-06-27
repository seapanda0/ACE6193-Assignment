cmake_minimum_required(VERSION 3.30)

project(
  ACE6193-Assignment
  VERSION 1.0
  LANGUAGES CXX)

include_directories(include)

add_library(cardManager source/cardManager.cpp)
add_library(Card source/Card.cpp)
add_library(Context source/Context.cpp)
add_library(State source/State.cpp)

add_executable(flashCard main.cpp)

target_link_libraries(flashCard PRIVATE cardManager)
target_link_libraries(flashCard PRIVATE Card)
target_link_libraries(flashCard PRIVATE Context)
target_link_libraries(flashCard PRIVATE State)
