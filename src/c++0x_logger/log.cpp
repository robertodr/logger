#include "log.hpp"

#include "log_utils.hpp"

namespace logging 
{
   template <typename log_policy>
   std::string logger<log_policy>::get_time()
   {
          std::string time_str;                               
          time_t raw_time;                                    
                                                             
          time( & raw_time );                                 
          time_str = ctime( &raw_time );                      
                                                             
          //without the newline character                     
          return time_str.substr( 0 , time_str.size() - 1 );  
      }                                                       
   
   template <typename log_policy>
   std::string logger<log_policy>::get_logline_header() 
   {
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

   template <typename log_policy>
   void logger<log_policy>::print_impl()
   {
            policy->write( get_logline_header() + log_stream.str() );
            log_stream.str("");
   }
   
   /*! @name Explicit specializations
    */ 
   /// @{
   /*! Specialization for file_log_policy */
   template class logger<file_log_policy>;
   /// @}

} // close namespace logging
