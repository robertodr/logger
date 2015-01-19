# logger
Small logger library based on two Dr. Dobb's articles:

* [A Lightweight Logger for C++](http://www.drdobbs.com/cpp/a-lightweight-logger-for-c/240147505)
* [Logging In C++](http://www.drdobbs.com/cpp/logging-in-c/201804215?pgno=4)

The former makes use of `std::unique_ptr`, `std::mutex` and variadic templates and will only work 
when using a fairly recent compiler with decent C++11 support.
The latter uses only C++98/C++03 features.
