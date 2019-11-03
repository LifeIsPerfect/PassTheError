#include <iostream>
#include <future>

#include <include/pass_the_error.hpp>
#include <include/pass_the_error_error.hpp>

namespace pass_the_error
{

category_list_t &get_category_list()
{
     static category_list_t category_list;
     return category_list;
}

category_list_t &register_category( const std::error_category &err_cat )
{
     static bool first_call = true;
     if( first_call )
     {
          first_call = false;

          // Register all standart category firstly.
          register_category( std::generic_category() );
          register_category( std::system_category() );
          register_category( std::iostream_category() );
          register_category( std::future_category() );

          // Register own pass_the_error error_category too.
          register_category( make_error_code( PassTheErrorError{} ).category() );
     }

     get_category_list().push_back( { err_cat.name(), &err_cat } );
     return get_category_list();
}

} // namespace pass_the_error
