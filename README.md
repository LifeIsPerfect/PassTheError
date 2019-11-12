PassTheError library
=============================================================

PassTheError is a small library that can help you to transmit std::error_code values through different processes.

The library can transmit either error codes from standart error categories (i.e. ones from `std::generic_category`, 
`std::system_category`, `std::iostream_category` and `std::future_category`) or error codes from your own error categories.

Suppose that you have a server side utility and that utility uses `std::error_code` to hanlde errors. The source of
such errors is uknown: you can catch an error code from one of standart categories or from custom error categories.
Suppose that you want to transmit gotten error code to client side utility via some IPC framework (such as Apache
Thrift or any other). The transmitting process of `std::error_code` is pretty confusing and can't be implemented in the 
naive manner regardless of choosen IPC framework. PassTheError library helps you to wrap your `std::error_code` on the server
side utility into special type that can be transmitted via IPC in the naive manner and reconstruct your original 
`std::error_code` from gotten on the client side wrapped object. To be able to do that, you need to register all custom
error categories you want to get errors from.
