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

#set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/images/fox_icon.ico")

###########################################################################

qt_add_executable(appDocMgmtQt
    main.cpp
    header.h
    client.cpp
    client.h
    qml.qrc
    personalmodel.cpp
    personalmodel.h
    appengine.cpp
    appengine.h
    rightsmodel.cpp
    rightsmodel.h
    officemodel.cpp
    officemodel.h
    userpage.cpp
    userpage.h
    officepage.cpp
    officepage.h
    rightpage.cpp
    rightpage.h
    filesmodel.cpp
    filesmodel.h
    messenger.h
    messenger.cpp

    images.qrc

    ${app_icon_resource_windows}
    #/images/fox_icon.ico

    ../encrypter.cpp
    ../encrypter.h

    ../logger.h
    ../logger.cpp

    ../messages.h
    ../datastructures.h
)


qt_add_qml_module(appDocMgmtQt
    URI DocMgmtQt
    VERSION 1.0
    QML_FILES 
        qml/main.qml
        qml/authenticationWindow.qml
        qml/Pages/calendar.qml
        qml/Pages/files.qml
        qml/Pages/personal.qml
        qml/Pages/Test.qml
        qml/Pages/user.qml
        qml/Pages/right.qml
        qml/Pages/office.qml
        qml/Pages/rightstable.qml
        qml/Pages/officestable.qml
        qml/Components/CellBox.qml
        qml/Components/LargeChartView.qml
        qml/Components/DrawerItem.qml
        qml/Components/PageDrawer.qml
        qml/Components/ContextMenu.qml
        qml/Components/ContextItem.qml

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
