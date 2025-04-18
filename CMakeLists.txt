cmake_minimum_required(VERSION 3.15)
project(wx_opengl_app)

set(CMAKE_CXX_STANDARD 17)
# Setup vcpkg toolchain (update the path as needed)
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain")

#find_package(wxWidgets CONFIG REQUIRED)
find_package(wxWidgets REQUIRED COMPONENTS core base gl)
find_package(PNG REQUIRED)
find_package(OpenGL REQUIRED)


#include(${wxWidgets_USE_FILE})

add_executable(wx_opengl_app
    main.cpp
    MyApp.cpp MyApp.h
    GLCanvas.cpp GLCanvas.h
)

target_include_directories(wx_opengl_app PRIVATE ${OPENGL_INCLUDE_DIR})
target_include_directories(wx_opengl_app PRIVATE ${wxWidgets_INCLUDE_DIRS})
target_link_libraries(wx_opengl_app PRIVATE ${wxWidgets_LIBRARIES})
#target_link_libraries(wx_opengl_app PRIVATE wx::core wx::base)
target_link_libraries(wx_opengl_app PRIVATE PNG::PNG)
target_link_libraries(wx_opengl_app PRIVATE ${OPENGL_LIBRARIES})


