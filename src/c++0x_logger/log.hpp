#ifndef LOG_HPP
#define LOG_HPP

#include <mutex>
#include <sstream>

#include "log_utils.hpp"

namespace logging
{
    template<typename log_policy>
    class logger
    {
      private:
        size_t log_line_number;
        std::stringstream log_stream;
        log_policy * policy;
        std::mutex write_mutex;

        std::string get_time(); 
        std::string get_logline_header();

	/*! @name Core printing functionality
	 *  
	 *  A variadic template is used, we specify the version
	 *  with a variable number of parameters/types and the version
	 *  with no parameters/types.
	 *  The variadic template is called recursively.
	 *  The type for the first parameter is resolved and streamed
	 *  to log_stream. When all the parameters have been streamed
	 *  the version with no arguments is called.
	 */
	/// @{
	/*! */
        void print_impl();
        template<typename First, typename...Rest>
        void print_impl(First parm1, Rest...parm) {
            log_stream<<parm1;
            print_impl(parm...);
        }
	/// @}
    public:
        /*! Constructor
	 *  \param[in] name name for the log file
	 */ 
        logger(const std::string & name);
	/// Destructor
        ~logger(); 

	/// User interface for the logger class
        template<severity_type severity, typename...Args>
        void print(Args...args) {
            write_mutex.lock();
            switch(severity) {
            case severity_type::debug:
                log_stream << "<DEBUG> : ";
                break;
            case severity_type::warning:
                log_stream << "<WARNING> : ";
                break;
            case severity_type::error:
                log_stream << "<ERROR> : ";
                break;
            };
            print_impl(args...);
            write_mutex.unlock();
        }

    };
} // close namespace logging

#endif // LOG_HPP
