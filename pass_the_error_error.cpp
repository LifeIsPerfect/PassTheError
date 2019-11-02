#include <include/pass_the_error_error.hpp>

#include <string>

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
               return "Error from unknown error category was gotten. Do you register all categories you can get from callee?"; 
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


