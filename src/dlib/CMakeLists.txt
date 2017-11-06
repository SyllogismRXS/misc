find_package(DLIB QUIET)
if (NOT DLIB_FOUND)
  message("DLIB not found. Not building DLIB tutorials.")
  return()
endif()

include_directories(${DLIB_INCLUDE_DIR})

set(EX_1_NAME mpc_ex)
add_executable(${EX_1_NAME} ${EX_1_NAME}.cpp)
target_link_libraries(
  ${EX_1_NAME}
  ${DLIB_LIBRARIES}
  )

set(EX_2_NAME optimization_ex)
add_executable(${EX_2_NAME} ${EX_2_NAME}.cpp)
target_link_libraries(
  ${EX_2_NAME}
  ${DLIB_LIBRARIES}
  openblas
  )
