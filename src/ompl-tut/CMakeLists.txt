find_package(OMPL QUIET)
if (NOT OMPL_FOUND)
  message("OMPL not found. Not building OMPL tutorials.")
  return()
endif()

include_directories("${OMPL_INCLUDE_DIRS}")

add_executable(ompl-tutorial-1 main.cpp)
target_link_libraries(
  ompl-tutorial-1
  ${OMPL_LIBRARIES}
  )

add_executable(ompl-car ompl-car.cpp)
target_link_libraries(
  ompl-car
  ${OMPL_LIBRARIES}
  )

add_executable(ompl-optimal ompl-optimal.cpp)
target_link_libraries(
  ompl-optimal
  ${OMPL_LIBRARIES}
  )

#set (APP_NAME_1 planOpenDE)
#file (GLOB SRCS planOpenDE.cpp)
#add_executable(${APP_NAME_1} ${SRCS})
## Link executable to other libraries
#target_link_libraries(
#  ${APP_NAME_1}
#  ${OMPL_LIBRARIES}
#  )

##--------------------------------------------------------
## Library Creation
##--------------------------------------------------------
#SET (LIBRARY_NAME BHV_Colregs)
#SET (LIB_MAJOR 0)
#SET (LIB_MINOR 0)
#SET (LIB_RELEASE 1)
#
#file( GLOB SRCS *.cpp)
#file( GLOB HDRS *.h)
#
#ADD_LIBRARY(${LIBRARY_NAME} SHARED
#  ${SRCS}
#  )
#
#TARGET_LINK_LIBRARIES(${LIBRARY_NAME}
#  OTHERLIBS
#  )
#
#SET (_soversion ${LIB_MAJOR}.${LIB_MINOR}.${LIB_RELEASE})
#
#set_target_properties(${LIBRARY_NAME} PROPERTIES SOVERSION ${LIB_MAJOR} VERSION ${_soversion})
#
#INSTALL(TARGETS ${LIBRARY_NAME}
#  LIBRARY DESTINATION lib
#  ARCHIVE DESTINATION lib
#)
