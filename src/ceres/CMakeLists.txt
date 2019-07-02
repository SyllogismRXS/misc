find_package(Ceres QUIET)
if (NOT Ceres_FOUND)
  return()
endif()

#find_package(Gflags REQUIRED)

include_directories(${CERES_INCLUDE_DIRS})

# helloworld example
add_executable(helloworld helloworld.cc)
target_link_libraries(helloworld ${CERES_LIBRARIES})

# powell example
add_executable(powell powell.cc)
target_link_libraries(powell ${CERES_LIBRARIES})

# robot pose mle example
add_executable(robot_pose_mle robot_pose_mle.cc)
target_link_libraries(robot_pose_mle ${CERES_LIBRARIES})
