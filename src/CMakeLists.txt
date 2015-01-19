set(sources log_utils.cpp)
add_library(logger STATIC ${sources})

add_executable(test.x test.cpp)
target_link_libraries(test.x logger)
