cmake_minimum_required(VERSION 3.16)
project(CampaignManager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# 1. Set a default build type (Release) if none is explicitly provided.
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "No build type specified. Defaulting to 'Release'.")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Points to your Qt binaries
set(CMAKE_PREFIX_PATH "C:/Qt/6.11.1/mingw_64") 

# Included Sql component for local SQLite database integration
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Sql)

# Source layout structured for Campaign Manager architecture
set(SOURCES
    src/main.cpp
    resources.qrc
    src/MainWindow.h
    src/MainWindow.cpp
    
    src/display/dashboard/DashboardWidget.h
    src/display/dashboard/DashboardWidget.cpp
    src/display/dashboard/DashboardWindow.h
    src/display/dashboard/DashboardWindow.cpp
    src/display/dashboard/HubCardWidget.h
    src/display/dashboard/HubCardWidget.cpp
    src/display/login/AuthDialog.h
    src/display/login/AuthDialog.cpp
    src/display/CustomMessageBox.h
    src/display/CustomMessageBox.cpp
    src/domain/AuthController.h
    src/domain/AuthController.cpp
    src/domain/DashboardController.h
    src/domain/DashboardController.cpp
    src/database/DatabaseManager.h
    src/database/DatabaseManager.cpp
    )

add_executable(CampaignManager ${SOURCES})

target_link_libraries(CampaignManager PRIVATE 
    Qt6::Core 
    Qt6::Gui 
    Qt6::Widgets 
    Qt6::Sql
)

target_include_directories(CampaignManager PRIVATE src)