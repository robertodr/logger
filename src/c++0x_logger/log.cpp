#include "log.hpp"

#include <stdexcept>

#include "log_utils.hpp"

namespace logging 
{
   template <typename logPolicy>
   logger<logPolicy>::logger(const std::string & name) 
       : logLineNumber_(0), policy_(new logPolicy) 
   {
       if(!policy_) {
           throw std::runtime_error("LOGGER: Unable to create the logger instance");
       }
       policy_->open_ostream(name);
   }

   template <typename logPolicy>
   logger<logPolicy>::~logger()
   {
            if(policy_) {
                policy_->close_ostream();
                delete policy_;
            }
   }

   template <typename logPolicy>
   std::string logger<logPolicy>::get_time()
   {
          std::string time_str;                               
          time_t raw_time;                                    
                                                             
          time(&raw_time);                                 
          time_str = ctime(&raw_time);                      
                                                             
          //without the newline character                     
          return time_str.substr(0, time_str.size() - 1);  
      }                                                       
   
   template <typename logPolicy>
   std::string logger<logPolicy>::get_logline_header() 
   {
            std::stringstream header;

            header.str("");
            header.fill('0');
            header.width(7);
            header << logLineNumber_++ << " < " <<get_time() << " - ";

            header.fill('0');
            header.width(7);
            header << clock() << " > ~ ";

            return header.str();
        }

   template <typename logPolicy>
   void logger<logPolicy>::print_impl()
   {
            policy_->write(get_logline_header() + logStream_.str());
            logStream_.str("");
   }
   
   /*! @name Explicit specializations
    */ 
   /// @{
   /*! Specialization for file_log_policy */
   template class logger<file_log_policy>;
   /// @}

} // close namespace logging
