cmake_minimum_required(VERSION 3.0.0)

project(kweb-player)

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SRC_SOURCES
main.cpp
googlemusicplayer.cpp
mainwindow.cpp
mprisplayerobject.cpp
playerstatus.cpp
trayicon.cpp
amarok/DBusAbstractAdaptor.cpp
)

add_executable(kweb-player ${SRC_SOURCES})

#find_package(Qt5Widgets REQUIRED)
find_package(Qt5 REQUIRED Core Gui WebEngine)

target_link_libraries(kweb-player Qt5::Widgets)


