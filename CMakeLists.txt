cmake_minimum_required(VERSION 3.5)

project(QTZork VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt5 or Qt6 components
find_package(QT NAMES Qt6 Qt5 REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(PROJECT_SOURCES
        main.cpp
        Character.cpp
        Character.h
        Command.cpp
        Command.h
        CommandWords.cpp
        CommandWords.h
        Item.cpp
        Item.h
        Parser.cpp
        Parser.h
        Room.cpp
        Room.h
        ZorkUL.cpp
        ZorkUL.h
        ProcessCommand.cpp
        ProcessCommand.h
        Player.h
        Player.cpp
        json.hpp
        Enemy.h
        Enemy.cpp
        mainwindow.cpp
        mainwindow.h
)

# If using Qt6, use qt_add_executable
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QTZork
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
    )
else()
    # For Qt5, add_executable
    add_executable(QTZork
            ${PROJECT_SOURCES}
    )
endif()

# Link Qt libraries
target_link_libraries(QTZork PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Set bundle properties
set_target_properties(QTZork PROPERTIES
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE FALSE
)

# Deployment configuration for Windows
if (WIN32)
    # Get the Qt install path
    set(QT_INSTALL_PATH "C:/QtDownloads/6.7.1/mingw_64")  # Adjust this path as per your Qt installation

    # Function to copy Qt DLLs
    function(copy_qt_dll DLL_NAME)
        if (EXISTS "${QT_INSTALL_PATH}/bin/Qt6${DLL_NAME}.dll")
            add_custom_command(TARGET QTZork POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "${QT_INSTALL_PATH}/bin/Qt6${DLL_NAME}.dll"
                    "$<TARGET_FILE_DIR:QTZork>"
            )
        else()
            message(FATAL_ERROR "Required Qt DLL ${QT_INSTALL_PATH}/bin/Qt6${DLL_NAME}.dll not found.")
        endif()
    endfunction()

    # Copy platform plugins (like qwindows.dll)
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows.dll")
        add_custom_command(TARGET QTZork POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:QTZork>/plugins/platforms/"
        )
        add_custom_command(TARGET QTZork POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows.dll"
                "$<TARGET_FILE_DIR:QTZork>/plugins/platforms/"
        )
    else()
        message(FATAL_ERROR "Required platform plugin ${QT_INSTALL_PATH}/plugins/platforms/qwindows.dll not found.")
    endif()

    # Copy Qt DLLs
    foreach(QT_LIB Widgets Gui Core)
        copy_qt_dll(${QT_LIB})
    endforeach(QT_LIB)
endif()

# Install target
include(GNUInstallDirs)
install(TARGETS QTZork
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
