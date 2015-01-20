#define LOGGING_LEVEL_1
#include <iostream>

#include <Eigen/Dense>

#include "LoggerInterface.hpp"

int main()
{
    LOG("Starting the application..");
    for( short i = 0 ; i < 3 ; i++ ) {
        LOG("The value of 'i' is ", i , ". " , 3 - i - 1 , " more iterations left ");
    }
    Eigen::Matrix3d mat = Eigen::Matrix3d::Ones();
    LOG("Log an Eigen matrix: \n", mat);
    LOG_WARN("Loop over");
    LOG_ERR("All good things come to an end.. :(");
    return 0;
}
