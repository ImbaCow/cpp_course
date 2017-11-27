add_executable(workshop3.4 main.cpp eventloop.cpp Ship.cpp)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype REQUIRED)
find_package(JPEG REQUIRED)
find_package(SFML 2 COMPONENTS window graphics system REQUIRED)

target_include_directories(workshop3.4 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(workshop3.4 PUBLIC cxx_std_17)
target_compile_definitions(workshop3.4 PRIVATE SFML_STATIC)

target_link_libraries(workshop3.4 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
