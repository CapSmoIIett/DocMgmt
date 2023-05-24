include (FetchContent)

project(MTest VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.4 COMPONENTS Quick Charts QuickControls2 SQL REQUIRED)

###########################################################################

set(PostgreSQL_INCLUDE_DIRS "D:/Programs/PostgreSQL/15/include")
set(PostgreSQL_LIBRARY_DIRS "D:/Programs/PostgreSQL/15/bin")

#find_package(PostgreSQL REQUIRED)
include_directories (${PostgreSQL_INCLUDE_DIRS})
link_directories(${PostgreSQL_LIBRARY_DIRS})

###########################################################################

set(OPENSSL_INCLUDE_DIR "D:/Projects/DocMgmt/Client/openssl/DLL/x64/Debug/include/openssl")
set(OPENSSL_LIBRARY_DIR "D:/Projects/DocMgmt/Client/openssl/DLL/x64/Debug/bin")

#include_directories(${OPENSSL_INCLUDE_DIR})
#link_directories(${OPENSSL_LIBRARY_DIR})

find_package(OpenSSL REQUIRED)

###########################################################################


if(BUILD_TESTING)
        file(GLOB files "*.h" "*.cpp")
        file(GLOB server RELATIVE "Server" "*.h" "*.cpp")
        file(GLOB client RELATIVE "Client" "*.h" "*.cpp")

        qt_add_executable(mtest ${files}

            ../Client/main.cpp
            ../Client/header.h
            ../Client/client.cpp
            ../Client/client.h
            ../Client/qml.qrc
            ../Client/personalmodel.cpp
            ../Client/personalmodel.h
            ../Client/appengine.cpp
            ../Client/appengine.h
            ../Client/rightsmodel.cpp
            ../Client/rightsmodel.h
            ../Client/officemodel.cpp
            ../Client/officemodel.h
            ../Client/userpage.cpp
            ../Client/userpage.h
            ../Client/officepage.cpp
            ../Client/officepage.h
            ../Client/rightpage.cpp
            ../Client/rightpage.h
            ../Client/filesmodel.cpp
            ../Client/filesmodel.h
            ../Client/messenger.h
            ../Client/messenger.cpp
            ../Client/calendar.cpp
            ../Client/calendar.h
            ../Client/images.qrc


            ../Server/server.cpp
            ../Server/server.h
            ../Server/database.cpp
            ../Server/database.h
            ../Server/filebase.cpp
            ../Server/filebase.h

            ../encrypter.cpp
            ../encrypter.h

            ../logger.h
            ../logger.cpp

            ../messages.h
            ../datastructures.h
        )

        target_link_libraries(mtest PRIVATE GTest::gtest_main)

        include(GoogleTest)
        gtest_discover_tests(mtest)

        set_target_properties(mtest PROPERTIES
            MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
            MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
            MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
            MACOSX_BUNDLE TRUE
            WIN32_EXECUTABLE TRUE
        )

        target_link_libraries(mtest
            PRIVATE Qt6::Sql Qt6::Network Qt6::Widgets Qt6::Quick OpenSSL::SSL)

        install(TARGETS mtest
            BUNDLE DESTINATION .
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif()

#FetchContent_Declare (
#        googletest
#        GIT_REPOSITORY https://github.com/google/googletest.git
#        GIT_TAG release-1.11.0
##########)
#
#FetchContent_MakeAvailable(googletest)
#add_library(GTest::GTest INTERFACE IMPORTED)
#target_link_libraries(GTest::GTest INTERFACE gtest_main)
#
#add_executable(gtest main.cpp)
#
#target_link_libraries(gtest PRIVATE GTest::GTest)
#
