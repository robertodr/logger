#ifndef LOG_HPP
#define LOG_HPP

#include <mutex>
#include <sstream>

#include "log_utils.hpp"

namespace logging
{
    template<typename logPolicy>
    class logger
    {
      private:
        size_t logLineNumber_;
        std::stringstream logStream_;
        logPolicy * policy_;
        std::mutex writeMutex_;

        std::string get_time(); 
        std::string get_logline_header();

	/*! @name Core printing functionality
	 *  
	 *  A variadic template is used, we specify the version
	 *  with a variable number of parameters/types and the version
	 *  with no parameters/types.
	 *  The variadic template is called recursively.
	 *  The type for the first parameter is resolved and streamed
	 *  to logStream_. When all the parameters have been streamed
	 *  the version with no arguments is called.
	 */
	/// @{
	/*! */
        void printImpl();
        template<typename First, typename...Rest>
        void printImpl(First parm1, Rest...parm) {
            logStream_<<parm1;
            printImpl(parm...);
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
            writeMutex_.lock();
            switch(severity) {
            case severity_type::debug:
                logStream_ << "<DEBUG> : ";
                break;
            case severity_type::warning:
                logStream_ << "<WARNING> : ";
                break;
            case severity_type::error:
                logStream_ << "<ERROR> : ";
                break;
            };
            printImpl(args...);
            writeMutex_.unlock();
        }

    };
} // close namespace logging

#endif // LOG_HPP
