cmake_minimum_required(VERSION 3.16)

project(MiniGCS VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Multimedia)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appMiniGCS
    main.cpp
)

qt_add_qml_module(appMiniGCS
    URI MiniGCS
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES src/controllers/dashboardcontroller.h src/controllers/dashboardcontroller.cpp
        SOURCES src/controllers/videocontroller.h src/controllers/videocontroller.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appMiniGCS PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appMiniGCS
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appMiniGCS
    PRIVATE Qt6::Quick
)
target_link_libraries(appMiniGCS PRIVATE Qt6::Core)
target_link_libraries(appMiniGCS PRIVATE Qt6::Multimedia)

include(GNUInstallDirs)
install(TARGETS appMiniGCS
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
