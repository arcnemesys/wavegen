cmake_minimum_required(VERSION 3.10)
project(wavegen)

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

add_executable(wavegen 
	src/main.cpp 
	src/waveform.cpp
)
target_link_libraries(wavegen ${wxWidgets_LIBRARIES})
