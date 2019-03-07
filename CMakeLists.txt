cmake_minimum_required(VERSION 3.5)
project(Mini_SLAM)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)


IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Release)
ENDIF()

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(Boost REQUIRED COMPONENTS system)

find_package(PCL 1.3 REQUIRED COMPONENTS common io)
find_package(Eigen3 REQUIRED)

find_package(cartographer REQUIRED)
include("${CARTOGRAPHER_CMAKE_DIR}/functions.cmake")
google_initialize_cartographer_project()
google_enable_testing()

find_package(LuaGoogle REQUIRED)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  nav_msgs
  cartographer_ros
  message_generation
)


# Override Catkin's GTest configuration to use GMock.
set(GTEST_FOUND TRUE)
set(GTEST_INCLUDE_DIRS ${GMOCK_INCLUDE_DIRS})
set(GTEST_LIBRARIES ${GMOCK_LIBRARIES})

## Generate services in the 'srv' folder
add_service_files(
  FILES
  write_to_file.srv
)

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES Mini_SLAM
  CATKIN_DEPENDS message_runtime roscpp rospy std_msgs nav_msgs 
  DEPENDS system_lib PCL Eigen cartographer
)

if (CATKIN_ENABLE_TESTING)
  catkin_add_gtest(configuration_files_test "config_files/config_files_test.cc")
  target_include_directories(configuration_files_test SYSTEM PUBLIC ${LUA_INCLUDE_DIR})
  target_link_libraries(configuration_files_test ${LUA_LIBRARIES})
  target_include_directories(configuration_files_test SYSTEM PUBLIC ${catkin_INCLUDE_DIRS})
  target_link_libraries(configuration_files_test ${catkin_LIBRARIES})
  add_dependencies(configuration_files_test ${catkin_EXPORTED_TARGETS})
  target_link_libraries(configuration_files_test cartographer)
  set(TARGET_COMPILE_FLAGS "${TARGET_COMPILE_FLAGS} ${GOOG_CXX_FLAGS}")
  set_target_properties(configuration_files_test PROPERTIES COMPILE_FLAGS ${TARGET_COMPILE_FLAGS})
endif()


include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
  ${PROJECT_SOURCE_DIR}/include/
  ${LUA_INCLUDE_DIR}
)

link_directories(
  ${PCL_LIBRARY_DIRS}
)

add_definitions(
  ${PCL_DEFINITIONS}  
)


add_executable(node1 src/node1.cpp)
target_link_libraries(node1
  ${catkin_LIBRARIES}
  ${PCL_LIBRARIES}
  ${LUA_LIBRARIES}
  cartographer
)
set_target_properties(node1 PROPERTIES COMPILE_FLAGS "${TARGET_COMPILE_FLAGS} ${GOOG_CXX_FLAGS}")


# Future work
# add_executable(node2 src/node2.cpp)
# target_link_libraries(node2
#   ${catkin_LIBRARIES}
#   ${PCL_LIBRARIES}
#   ${LUA_LIBRARIES}
#   cartographer
# )
# set_target_properties(node2 PROPERTIES COMPILE_FLAGS "${TARGET_COMPILE_FLAGS} ${GOOG_CXX_FLAGS}")


add_executable(write_to_file_server src/write_to_file_server.cpp)
target_link_libraries(write_to_file_server ${catkin_LIBRARIES})
add_dependencies(write_to_file_server Mini_SLAM_gencpp)

