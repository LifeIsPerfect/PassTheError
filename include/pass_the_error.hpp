#pragma once
#ifndef _PASS_THE_ERROR_HPP_
#define _PASS_THE_ERROR_HPP_

#include <system_error>
#include <utility>
#include <string>
#include <list>

using category_list_t = std::list<std::pair<std::string, const std::error_category *const>>;

/// @brief Получить список зарегистрированных error_category.
///
/// @return Список зарегистрированных error_category.
category_list_t &get_category_list();

/// @biref Зарегистрировать новую error_category.
///
/// @param[in] err_cat error_category, которую нужно добавить.
///
/// @return Список зарегистрированных error_category.
category_list_t &register_category( const std::error_category &err_cat );

#endif // _PASS_THE_ERROR_HPP_
