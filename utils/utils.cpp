#include "utils.h"

#include <sstream>

namespace parsing
{

struct NumberAndDimension
{
    std::string_view number;
    std::string_view dimension;
};

NumberAndDimension parseDimensionFormat(std::string_view argument);
std::size_t getSizeDimension(std::string_view dim_part);
std::size_t getNumber(std::string_view number_part);

std::size_t getAsBytesSize(const std::string& size_str)
{
    auto [number_part, dim_part] = parseDimensionFormat(size_str);

    std::size_t numb = getNumber(number_part);
    std::size_t dim = getSizeDimension(dim_part);
    return numb * dim;
}

NumberAndDimension parseDimensionFormat(std::string_view argument)
{
    static constexpr std::string_view delimiter = "_";
    auto pos = argument.find_last_of(delimiter);
    if (pos == std::string::npos)
    {
        throw std::runtime_error("YamlConfig - invalid dimension format: " + std::string(argument));
    }
    std::string_view dim_part(argument.data() + (pos + delimiter.size()), argument.size() - (pos + delimiter.size()));
    std::string_view number_part(argument.data(), pos);

    return {.number = number_part, .dimension = dim_part};
}

std::size_t getSizeDimension(std::string_view dim_part)
{
    std::size_t res;

    if      (dim_part == "B")      res = 1;
    else if (dim_part == "KB")     res = 2 << 10;
    else if (dim_part == "MB")     res = 2 << 20;
    else if (dim_part == "GB")     res = 2 << 30;
    else
    {
        throw std::runtime_error("YamlConfig - invalid dimension format: " + std::string(dim_part));
    }

    return res;
}

std::size_t getNumber(std::string_view number_part)
{
    if (!std::all_of(number_part.begin(), number_part.end(), ::isdigit))
    {
        throw std::runtime_error("YamlConfig - invalid number format" + std::string(number_part));
    }

    std::size_t res;
    std::stringstream ss{};
    ss.write(number_part.data(), static_cast<std::streamsize>(number_part.size()));
    ss >> res;

    return res;
}

}