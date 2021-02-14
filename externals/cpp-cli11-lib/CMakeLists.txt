project(cli11)
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS *.hpp)
add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})
set_target_properties(cli11 PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(cli11  INTERFACE .)

