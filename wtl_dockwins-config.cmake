find_package (wtl REQUIRED NO_MODULE)

set (wtl_dockwins_DEFINITIONS)
set (wtl_dockwins_INCLUDE_DIRS ${Boost_INCLUDE_DIRS} ${wtl_INCLUDE_DIR}
  ${wtl_INCLUDE_DIRS})
set (wtl_dockwins_LIBRARIES ${wtl_LIBRARY} ${wtl_LIBRARIES})
set (wtl_dockwins_LIBRARY)

get_filename_component (_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
get_filename_component (wtl_dockwins_INCLUDE_DIR ${_DIR}/include ABSOLUTE)
