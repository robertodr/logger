#ifndef LOG_HPP
#define LOG_HPP

#include <mutex>
#include <sstream>

#include "log_utils.hpp"

namespace logging
{
    template< typename log_policy >
    class logger
    {
        unsigned log_line_number;
        std::string get_time() {
            std::string time_str;
            time_t raw_time;

            time( & raw_time );
            time_str = ctime( &raw_time );

            //without the newline character
            return time_str.substr( 0 , time_str.size() - 1 );
        }
        std::string get_logline_header() {
            std::stringstream header;

            header.str("");
            header.fill('0');
            header.width(7);
            header << log_line_number++ <<" < "<<get_time()<<" - ";

            header.fill('0');
            header.width(7);
            header <<clock()<<" > ~ ";

            return header.str();
        }
        std::stringstream log_stream;
        log_policy* policy;
        std::mutex write_mutex;

        //Core printing functionality
        void print_impl() {
            policy->write( get_logline_header() + log_stream.str() );
            log_stream.str("");
        }
        template<typename First, typename...Rest>
        void print_impl(First parm1, Rest...parm) {
            log_stream<<parm1;
            print_impl(parm...);
        }
    public:
        logger( const std::string& name ) {
            log_line_number = 0;
            policy = new log_policy;
            if( !policy ) {
                throw std::runtime_error("LOGGER: Unable to create the logger instance");
            }
            policy->open_ostream( name );
        }

        template< severity_type severity, typename...Args >
        void print( Args...args ) {
            write_mutex.lock();
            switch( severity ) {
            case severity_type::debug:
                log_stream<<"<DEBUG> :";
                break;
            case severity_type::warning:
                log_stream<<"<WARNING> :";
                break;
            case severity_type::error:
                log_stream<<"<ERROR> :";
                break;
            };
            print_impl( args... );
            write_mutex.unlock();
        }

        ~logger() {
            if( policy ) {
                policy->close_ostream();
                delete policy;
            }
        }
    };
} // close namespace logging

#endif // LOG_HPP
