cmake_minimum_required(VERSION 3.16)

project(UnitTest)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Core Test Gui Widgets )

###########################################################################


qt_add_executable(UnitTest
    test.cpp
)

set_target_properties(UnitTest PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(UnitTest
    PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Test
    Qt6::Widgets)

install(TARGETS UnitTest
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
