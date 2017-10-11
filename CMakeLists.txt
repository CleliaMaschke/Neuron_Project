cmake_minimum_required(VERSION 2.6)
project(neuron)

set(CMAKE_CXX_FLAGS "-O3 -W -Wall -pedantic -std=c++11")

add_executable(neuron
			   Neuron.cpp
			   main.cpp
			   )
			   
#testing
if(test)
	enable_testing()
	find_package(GTest)
	include_directories(${GTEST_INCLUDE_DIRS})

  add_definitions(-DTEST)

	add_executable(neuron_test NeuronTest.cpp Neuron.cpp)
	target_link_libraries(neuron_test ${GTEST_BOTH_LIBRARIES} pthread)
	add_test(neuron_test)
endif(Test)
