cmake_minimum_required(VERSION 3.30)

project(
  ACE6193-Assignment
  VERSION 1.0
  LANGUAGES CXX)

include_directories(include)

add_library(cardManager source/cardManager.cpp)

add_executable(flashCard main.cpp)

target_link_libraries(flashCard PRIVATE cardManager)
