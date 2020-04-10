cmake_minimum_required(VERSION 3.12)
project(Kacassonne)

set(CMAKE_CXX_STANDARD 17)

IF (WIN32)
	add_definitions(-DWIN32_LEAN_AND_MEAN)

	set(wxWidgets_ROOT_DIR D:/Programmieren/wxWidgets-3.0.4/)
	set(wxWidgets_LIB_DIR D:/Programmieren/wxWidgets-3.0.4/lib/vc_lib)
	set(wxWidgets_CONFIGURATION mswu)

	include_directories(include forms D:/Programmieren/cppzmq-master D:/Programmieren/zmq)
ELSE()
	set(CMAKE_CXX_FLAGS "-g -rdynamic -no-pie")
	find_package(PkgConfig)
	pkg_check_modules(PC_ZeroMQ QUIET zmq)
	find_path(ZeroMQ_INCLUDE_DIR NAMES zmq.hpp PATHS ${PC_ZeroMQ_INCLUDE_DIRS})
	find_library(ZeroMQ_LIBRARY NAMES zmq PATHS ${PC_ZeroMQ_LIBRARY_DIRS})

	include_directories(include forms ${ZeroMQ_INCLUDE_DIR})
EndIF()

find_package(wxWidgets COMPONENTS core base REQUIRED)
include( "${wxWidgets_USE_FILE}")

add_executable(Kacassonne WIN32 src/main.cpp include/main.h forms/HostDialog_B.h forms/HostDialog_B.cpp forms/MainFrame_B.h
  forms/LobbyDialog_B.h forms/LobbyDialog_B.cpp src/GameDialog.cpp forms/GameDialog_B.cpp
  forms/MainFrame_B.cpp include/MainFrame.h src/MainFrame.cpp include/TablePanel.h src/TablePanel.cpp
  include/PointGroup.h src/PointGroup.cpp include/Card.h src/Card.cpp include/Stack.h src/Stack.cpp
  include/Game.h src/Game.cpp include/Stone.h src/Stone.cpp include/Player.h src/Player.cpp include/HostDialog.h
  src/HostDialog.cpp src/Message.cpp src/Connection.cpp forms/ConnectDialog_B.h forms/ConnectDialog_B.cpp src/LobbyDialog.cpp)

IF (WIN32)
	target_link_libraries(Kacassonne D:/Programmieren/zmq/libzmq-v141-mt-4_3_2.lib ${wxWidgets_LIBRARIES} )
ELSE()
	target_link_libraries(Kacassonne ${wxWidgets_LIBRARIES} ${ZeroMQ_LIBRARY})
ENDIF()