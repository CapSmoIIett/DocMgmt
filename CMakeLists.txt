cmake_minimum_required(VERSION 3.16)

project(DocMgmtQt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 COMPONENTS Quick Charts QuickControls2 REQUIRED)

qt_add_executable(appDocMgmtQt
    main.cpp
    imagines.qrc
    pages.qrc
)

qt_add_qml_module(appDocMgmtQt
    URI DocMgmtQt
    VERSION 1.0
    QML_FILES 
        main.qml 
        Pages/calendar.qml
        Pages/files.qml
        Pages/personal.qml
        Pages/CellBox.qml
        Pages/SideNavButton.qml
        Pages/LargeChartView.qml
)

#set(QT_CHARTS_INCLUDE_PATHS "${QT_ROOT}/include/QtCharts")

set_target_properties(appDocMgmtQt PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appDocMgmtQt
    PRIVATE Qt6::Quick)

install(TARGETS appDocMgmtQt
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
