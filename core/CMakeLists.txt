project(navi_core)

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS *.cpp *.h)
add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC _includes)
