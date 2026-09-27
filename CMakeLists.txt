cmake_minimum_required(VERSION 3.15)
project(PixelWindow CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(USE_EXAMPLES OFF CACHE BOOL "" FORCE)


add_subdirectory(third_party/minifb)


add_executable(silly_things main.cpp)

# 4. Линкуем minifb и прокидываем заголовочные файлы
target_link_libraries(silly_things PRIVATE minifb)

