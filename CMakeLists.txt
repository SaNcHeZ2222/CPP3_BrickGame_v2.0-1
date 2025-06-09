cmake_minimum_required(VERSION 3.14)
project(MyQtProject)

set(CMAKE_CXX_STANDARD 17)

# Укажите путь к Qt6
set(Qt6_DIR "/Users/sanchez02/.brew/opt/qt/lib/cmake/Qt6")
set(CMAKE_PREFIX_PATH "/Users/sanchez02/.brew/opt/qt/lib/cmake")

find_package(Qt6 COMPONENTS Widgets REQUIRED)

# Убедитесь, что CMake обрабатывает MOC файлы
set(CMAKE_AUTOMOC ON)

# set_property(SOURCE tetriswindow.cpp PROPERTY SKIP_AUTOMOC ON)

# Добавьте файлы main.cpp, mainwindow.cpp, tetriswindow.cpp и startwindow.cpp в проект
add_executable(MyQtProject gui/desktop/main.cpp brick_game/snake/snakegame_back.c gui/desktop/snakegame.cpp gui/desktop/tetriswindow.cpp gui/desktop/startwindow.cpp brick_game/tetris/tetris_back_desktop.c)

# Ссылки на Qt6 Widgets
target_link_libraries(MyQtProject Qt6::Widgets)
