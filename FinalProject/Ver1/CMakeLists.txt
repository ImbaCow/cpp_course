add_executable(Ver1 main.cpp GameRun.cpp HeroTank.cpp
Bullets.cpp Enemies.cpp Game.cpp 
GameMenu.cpp GameEnd.cpp GameLevel.cpp GamePause.cpp Math.cpp Boss.cpp)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype REQUIRED)
find_package(JPEG REQUIRED)
find_package(SFML 2 COMPONENTS window graphics system REQUIRED)

target_include_directories(Ver1 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(Ver1 PUBLIC cxx_std_17)
target_compile_definitions(Ver1 PRIVATE SFML_STATIC)

target_link_libraries(Ver1 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
