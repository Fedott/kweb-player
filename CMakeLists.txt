cmake_minimum_required(VERSION 3.0.0)

project(kweb-player)

set(QT_MIN_VERSION "5.5.0")
set(KF5_MIN_VERSION "5.4.0")

find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)
include(FeatureSummary)

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Find Qt modules
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
    Core
    Widgets
    Gui
    WebEngine
    WebEngineWidgets
    DBus
)

# Find KDE modules
find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
    CoreAddons      # KAboutData
    ConfigWidgets   # KStandardActions
    GlobalAccel
    Notifications
)

QT5_WRAP_UI(UIS_HDRS
    mainwindow.ui
)

# Add resources
set(RESOURCE ${CMAKE_SOURCE_DIR}/jsscripts.qrc)
qt5_add_resources(RESOURCE_ADDED ${RESOURCE})

set(SRC_SOURCES
    main.cpp
    googlemusicplayer.cpp
    mainwindow.cpp
    mprisplayerobject.cpp
    playerstatus.cpp
    trayicon.cpp
    amarok/DBusAbstractAdaptor.cpp
)

add_executable(kweb-player
    ${SRC_SOURCES}
    ${UIS_HDRS}
    ${RESOURCE_ADDED}
)

target_link_libraries(kweb-player
    Qt5::Widgets
    Qt5::WebEngineWidgets
    Qt5::Core
    Qt5::Gui
    Qt5::DBus
    KF5::GlobalAccel
    KF5::Notifications
)

# Install instructions
install(FILES kweb-player.notifyrc DESTINATION ${KNOTIFYRC_INSTALL_DIR})
