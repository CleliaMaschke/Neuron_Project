cmake_minimum_required(VERSION 2.6)
project(neuron)
set(CMAKE_CXX_FLAGS "-O3 -W -Wall -pedantic -std=c++11")

enable_testing()
add_subdirectory(googletest)
include_directories(${googletest_SOURCE_DIR}/include ${googletest_SOURCE_DIR})

add_executable(neuron
			   Neuron.cpp
			   main.cpp
			   Cortex.cpp
			   )
			   
add_executable(neuron_test
				Neuron.cpp
				Cortex.cpp
				Neuron_Test.cpp
				)
target_link_libraries(neuron_test gtest gtest_main)
add_test(neuron_test neuron_test)

