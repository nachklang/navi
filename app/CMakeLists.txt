project(naviApp)

file(GLOB_RECURSE PROJECT_SOURCES "*.h" "*.cpp")

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} navi_core cli11 json)
