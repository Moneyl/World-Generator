//#define GConstant = .0000000000667
//#define PI = 3.1415926535897932384626433832795

template <typename T>
std::string to_string(T value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}
