#ifndef BOOST_LOG_UTILS_HPP
#define BOOST_LOG_UTILS_HPP

#include <fstream>
#include <memory>
#include <string>

#include <boost/shared_ptr.hpp>

namespace logging
{
    enum severity_type {
        debug = 1,
        error,
        warning
    };

    class log_policy_interface
    {
    public:
        virtual void open_ostream(const std::string& name) = 0;
        virtual void close_ostream() = 0;
        virtual void write(const std::string& msg) = 0;

    };

    /*
     * Implementation which allows to write into a file
     */

    class file_log_policy : public log_policy_interface
    {
        boost::shared_ptr< std::ofstream > out_stream;
    public:
        file_log_policy() : out_stream( new std::ofstream ) {}
        void open_ostream(const std::string& name);
        void close_ostream();
        void write(const std::string& msg);
        ~file_log_policy();
    };

} // close namespace logging

#endif // BOOST_LOG_UTILS_HPP
