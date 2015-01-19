if(ENABLE_CXX11)
   add_executable(c++0x_logger_test.x c++0x_logger_test.cpp)
   target_link_libraries(c++0x_logger_test.x c++0x_logger)
endif()   

add_executable(logger_test.x logger_test.cpp)

add_executable(boost_logger_test.x boost_logger_test.cpp)
target_link_libraries(boost_logger_test.x boost_logger)
