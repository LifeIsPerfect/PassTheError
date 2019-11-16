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

#include <string>

#include <include/pass_the_error_error.hpp>

namespace /*anonymous*/
{

struct PassTheErrorErrorCategory : std::error_category
{
     const char* name() const noexcept override;
     std::string message(int ev) const override;
};

const char* PassTheErrorErrorCategory::name() const noexcept 
{
     return "PassTheError";
}

std::string PassTheErrorErrorCategory::message(int ev) const 
{
     switch( static_cast<pass_the_error::PassTheErrorError>(ev) )
     {
          case pass_the_error::PassTheErrorError::UnknownCategoryGotten:
               return "Error from unknown error category was gotten."
                    "Do you register all categories you can get from callee?"; 
          default:
               return "(unrecognized error)";
     }
}

const PassTheErrorErrorCategory thePassTheErrorErrorCategory {};

} // anonymous namespace

namespace pass_the_error
{

std::error_code make_error_code( pass_the_error::PassTheErrorError ec )
{
     return { static_cast<int>( ec ), thePassTheErrorErrorCategory };
}

}


