# logger
Small logger library based on a Dr. Dobb's article, [A Lightweight Logger for C++](http://www.drdobbs.com/cpp/a-lightweight-logger-for-c/240147505)

It makes use of `std::unique_ptr`, `std::mutex` and variadic templates and will only work 
when using a fairly recent compiler with decent C++11 support.
If your compiler doesn't have C++11 support, the library will not be compiled. You will still
be able to invoke the macros, but no log will be written.

The library is able to log basically everything that overloads `operator<<`
The small example in `tests` logs an `Eigen::Matrix3d`
