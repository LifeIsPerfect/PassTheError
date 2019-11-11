#pragma once
#ifndef _PASS_THE_ERROR_HPP_
#define _PASS_THE_ERROR_HPP_

#include <system_error>
#include <utility>
#include <string>
#include <list>

namespace pass_the_error
{

class wrapped_error_code;

using category_list_t = std::list<std::pair<std::string, const std::error_category *>>;

/// @brief Get list of registered error categories.
///
/// @return The list.
category_list_t &get_category_list();

/// @biref Register new error category.
///
/// @param[in] err_cat   Error category to register.
///
/// @return List of registered error categories.
category_list_t &register_category( const std::error_category &err_cat );

/// @brief Wrap error code.
///
/// The function turns its standart error_code parameter into an object of interprocess-transmittable type.
/// Use the function on the server side to transmit your std::error_code to client side.
///
/// @param[in] ec   Error code.
///
/// @return Wrapper error code.
wrapped_error_code wrap_error_code( const std::error_code &ec );

/// @brief Unwrap wrapped error code. 
///
/// The function turns its interprocess-transmittable parameter into an object of standart error_code type.
/// Use the function on the client side to reconstruct original std::error_code transmitted from the server.
///
/// @param[in] wec  Wrapped error code.
///
/// @return Error code.
std::error_code unwrap_error_code( const wrapped_error_code &wec );

} // namespace pass_the_error

#endif // _PASS_THE_ERROR_HPP_
