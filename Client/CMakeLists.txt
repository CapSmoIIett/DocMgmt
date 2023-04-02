cmake_minimum_required(VERSION 3.16)

project(DocMgmt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.4 COMPONENTS Quick Charts QuickControls2 SQL REQUIRED)

###########################################################################

set(PostgreSQL_ADDITIONAL_VERSIONS "15")

set(PostgreSQL_INCLUDE_DIRS "D:/Programs/PostgreSQL/15/include")
set(PostgreSQL_LIBRARY_DIRS "D:/Programs/PostgreSQL/15/bin")

#find_package(PostgreSQL REQUIRED)
include_directories (${PostgreSQL_INCLUDE_DIRS})
link_directories(${PostgreSQL_LIBRARY_DIRS})

###########################################################################

qt_add_executable(appDocMgmtQt
    main.cpp
    header.h
    client.cpp
    client.h
    imagines.qrc
    pages.qrc
    database.cpp
    database.h
    model.cpp
    model.h

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
        Pages/LargeChartView.qml
        Pages/DrawerItem.qml
        Pages/PageDrawer.qml
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
    PRIVATE Qt6::Quick Qt6::Sql)

install(TARGETS appDocMgmtQt
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
