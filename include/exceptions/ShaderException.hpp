#ifndef SHADER_EXCEPTION_HPP
#define SHADER_EXCEPTION_HPP

#include <exception>
#include <string>
#include <utility>

class ShaderException : public std::exception
{
public:
    explicit ShaderException(std::string message) : _message(std::move(message))
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return _message.c_str();
    }

private:
    std::string _message;
};

#endif //SHADER_EXCEPTION_HPP
