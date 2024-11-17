cmake_minimum_required(VERSION 3.16)

project(ImageScaling VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick QuickControls2 Concurrent Gui Core)

qt_standard_project_setup()

qt_add_executable(appImageScaling
    main.cpp
)

qt_add_qml_module(appImageScaling
    URI ImageScaling
    VERSION 1.0
    QML_FILES Main.qml
    RESOURCES assets/crossRed.png
    SOURCES imagescaling.h imagescaling.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appImageScaling PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appImageScaling
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appImageScaling
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Core
    PRIVATE Qt6::QuickControls2
    PRIVATE Qt6::Gui
    PRIVATE Qt6::Concurrent
)

include(GNUInstallDirs)
install(TARGETS appImageScaling
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
