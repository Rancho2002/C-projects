cmake_minimum_required( VERSION 2.8)
project( smart_traffic_control )
find_package( OpenCV REQUIRED )
add_executable( smart_traffic_control main )
target_link_libraries( smart_traffic_control ${OpenCV_LIBS} )

