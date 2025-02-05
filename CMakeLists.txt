cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 23)

project(MINISHOOTER VERSION 1.0.0)

add_executable(MINISHOOTER main.cpp ext/window/Window.cpp)

# Variables storing SDL framework locations
set(SDL2
  /Library/Frameworks/SDL2.framework)
set(SDL2_image
  /Library/Frameworks/SDL2_image.framework)
set(SDL2_ttf
  /Library/Frameworks/SDL2_ttf.framework)

target_link_libraries(
  MINISHOOTER PRIVATE
  ${SDL2}/Versions/A/SDL2
  ${SDL2_image}/Versions/A/SDL2_image
  ${SDL2_ttf}/Versions/A/SDL2_ttf
)

target_include_directories(
  MINISHOOTER PRIVATE
  ${SDL2}/Versions/A/Headers
  ${SDL2_image}/Versions/A/Headers
  ${SDL2_ttf}/Versions/A/Headers
)