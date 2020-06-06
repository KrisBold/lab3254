cmake_minimum_required(VERSION 3.15)

project(Laboratory1 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDART 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#Чтобы найти пакеты Qt5
#set(CMAKE_PREFIX_PATH "C:\Qt\5.14.1\mingw73_64")

find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(project_headers 
	include/Configuration.h
	include/FileManager.h
	include/Magazine.h
	include/Subscriber.h
)

set(project_sources 
	src/main.cpp
	src/FileManager.cpp
	src/Magazine.cpp
	src/Subscriber.cpp
)

add_executable(${PROJECT_NAME}
	${project_headers}
	${project_sources}
)

target_link_libraries(${PROJECT_NAME} 
	PUBLIC 
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets
)