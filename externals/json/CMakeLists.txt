project(json)
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS *.hpp)
add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})
set_target_properties(json PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(json  INTERFACE .)

