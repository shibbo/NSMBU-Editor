cmake_minimum_required(VERSION 3.5)

project(nsmbu VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        common.h
        fmt/GTX.h
        fmt/GTX.cpp
        game/Game.h
        game/Game.cpp
        game/Level.h
        game/Level.cpp
        game/Tileset.h
        game/Tileset.cpp
        game/obj/Objects.h
        game/obj/Object.h
        game/obj/Object.cpp
        game/obj/Background.h
        game/obj/Background.cpp
        game/obj/Entrance.h
        game/obj/Entrance.cpp
        game/obj/Location.h
        game/obj/Location.cpp
        game/obj/Path.h
        game/obj/Path.cpp
        game/obj/PathPoint.h
        game/obj/PathPoint.cpp
        game/obj/Sprite.h
        game/obj/Sprite.cpp
        game/obj/Zone.h
        game/obj/Zone.cpp
        game/obj/ZoneBounds.h
        game/obj/ZoneBounds.cpp
        io/Filesystem.h
        io/FileBase.h
        io/FileBase.cpp
        io/FilesystemBase.h
        io/ExternalFilesystem.h
        io/ExternalFilesystem.cpp
        io/ExternalFile.h
        io/ExternalFile.cpp
        io/MemoryFile.h
        io/MemoryFile.cpp
        io/SARCFilesystem.h
        io/SARCFilesystem.cpp
        io/Yaz0File.h
        io/Yaz0File.cpp
        rend/renders.h
        rend/EntranceRenderer.h
        rend/EntranceRenderer.cpp
        rend/ObjectRenderer.h
        rend/ObjectRenderer.cpp
        rend/SpriteRenderer.h
        rend/SpriteRenderer.cpp
        ui/LevelView.h
        ui/LevelView.cpp
        ui/WindowBase.h
        util/ImageUtil.h
        util/ImageUtil.cpp
        util/MathUtil.h
        util/MathUtil.cpp
        util/units.h
        util/units.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(nsmbu
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET nsmbu APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(nsmbu SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(nsmbu
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(nsmbu PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(nsmbu PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS nsmbu
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(nsmbu)
endif()
