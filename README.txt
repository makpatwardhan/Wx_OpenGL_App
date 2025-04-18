  find_package(wxWidgets CONFIG REQUIRED)
    target_link_libraries(main PRIVATE wx::core wx::base)

git clone https://github.com/microsoft/vcpkg
cd vcpkg
./bootstrap-vcpkg.sh


 ./vcpkg.exe install wxwidgets:x64-windows

find_package(PNG REQUIRED)
  target_link_libraries(main PRIVATE PNG::PNG)


find_package(OpenGL REQUIRED)
    target_link_libraries(main PRIVATE ${OPENGL_LIBRARIES})
    target_include_directories(main PRIVATE ${OPENGL_INCLUDE_DIR})
