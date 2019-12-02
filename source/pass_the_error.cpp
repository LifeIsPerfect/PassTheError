/*
     Licensed to Alexander Skripko under one or more contributor license agreements. See the NOTICE file distributed 
with this work for additional information regarding copyright ownership. Alexander Skripko licenses this file to you
under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the
License. You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

     Unless required by applicable law or agreed to in writing, software distributed under the License is distributed
on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
*/

#include <iostream>
#include <algorithm>
#include <future>

#include <include/pass_the_error.hpp>
#include <include/pass_the_error_error.hpp>

#include <pass_the_error_types.h>

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

wrapped_error_code wrap_error_code( const std::error_code &ec )
{
     wrapped_error_code wec;
     wec.category_name = ec.category().name();
     wec.value = ec.value();
     return wec;
}

std::error_code unwrap_error_code( const wrapped_error_code &wec )
{
     auto it = std::find_if( get_category_list().begin(), get_category_list().end(),
          [wec]( const std::pair<std::string, const std::error_category *>& el )
          { 
               return el.first == wec.category_name; 
          } );
               
     if( it == get_category_list().end() )
     {
          return PassTheErrorError::UnknownCategoryGotten;
     }

     return { wec.value, *(it->second) };
}

} // namespace pass_the_error
