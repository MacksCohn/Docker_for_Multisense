cmake_minimum_required(VERSION 3.8)
project(ros-to-ros2-pipe)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(roscpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(PCL 1.3 REQUIRED) 
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
find_package(pcl_conversions REQUIRED) 

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

add_executable(ros-to-ros2-pipe src/ros-to-ros2-pipe.cpp)
target_link_libraries(ros-to-ros2-pipe ${PCL_LIBRARIES})
ament_target_dependencies(ros-to-ros2-pipe rclcpp roscpp sensor_msgs std_msgs pcl_conversions)

install(
  TARGETS
  ros-to-ros2-pipe
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
