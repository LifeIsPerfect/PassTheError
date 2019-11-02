#pragma once
#ifndef _PASS_THE_ERROR_ERROR_HPP_
#define _PASS_THE_ERROR_ERROR_HPP_

#include <system_error>

namespace pass_the_error
{

enum class PassTheErrorError
{
     UnknownCategoryGotten = 1,
};

std::error_code make_error_code( PassTheErrorError );

} // namespace pass_the_error 

namespace std
{
template<>
     struct is_error_code_enum<pass_the_error::PassTheErrorError> : true_type {};
}

#endif // _PASS_THE_ERROR_ERROR_HPP_
