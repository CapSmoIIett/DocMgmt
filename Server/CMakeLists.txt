cmake_minimum_required(VERSION 3.16)

project(DocMgmtServer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.4 COMPONENTS Sql Network REQUIRED)

###########################################################################

#set(PostgreSQL_ADDITIONAL_VERSIONS "15")

#set(PostgreSQL_INCLUDE_DIRS "D:/Programs/PostgreSQL/15/include")
#set(PostgreSQL_LIBRARY_DIRS "D:/Programs/PostgreSQL/15/bin")

#find_package(PostgreSQL REQUIRED)
#include_directories (${PostgreSQL_INCLUDE_DIRS})
#link_directories(${PostgreSQL_LIBRARY_DIRS})

###########################################################################

qt_add_executable(DocMgmtServer
    main.cpp
    server.cpp
    server.h
    messages.h
)

set_target_properties(DocMgmtServer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(DocMgmtServer
    PRIVATE Qt6::Sql Qt6::Network)

install(TARGETS DocMgmtServer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})