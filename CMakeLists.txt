cmake_minimum_required(VERSION 3.16)

project(Prototype VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(appPrototype
    main.cpp
)

qt_add_qml_module(appPrototype
    URI Prototype
    VERSION 1.0
    QML_FILES Main.qml
    QML_FILES CustomScrollBar.qml
    SOURCES buttoncontroller.h buttoncontroller.cpp
    QML_FILES CustomButton.qml

    RESOURCES
    assets/images/1.jpg
    assets/images/2.jpg
    assets/images/3.jpg
    assets/images/4.jpg
    assets/images/5.jpg
    assets/images/6.jpg
    assets/images/7.jpg
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appPrototype PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appPrototype
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appPrototype
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appPrototype
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
