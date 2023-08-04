cmake_minimum_required(VERSION 3.12)
project(CryproPupsik)

set(CMAKE_CXX_STANDARD 14)

include_directories(C:/Users/Max/Desktop/vcpkg/installed/x64-windows/include/tgbot)

link_directories(C:/Users/Max/Desktop/vcpkg/installed/x64-windows/lib)

add_executable(CryproPupsik Source.cpp)

target_link_libraries(CryproPupsik TgBot)
