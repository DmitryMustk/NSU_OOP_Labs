#include <iostream>
#include <tuple>
#include <vector>

template <std::size_t Index = 0, typename... Types>
typename std::enable_if<Index == sizeof...(Types)>::type
print_tuple(std::ostream&, const std::tuple<Types...>&) {}

template <std::size_t Index = 0, typename... Types>
typename std::enable_if<Index < sizeof...(Types)>::type
print_tuple(std::ostream& os, const std::tuple<Types...>& t) {
    if (Index > 0) {
        os << ", ";
    }
    os << std::get<Index>(t);
    print_tuple<Index + 1>(os, t);
}

template <typename... Types>
std::ostream& operator<<(std::ostream& os, const std::tuple<Types...>& t) {
    os << "(";
    print_tuple(os, t);
    os << ")";
    return os;
}

int main() {
    std::vector<int> vec = {4, 3, 2, 1};
    std::tuple<int, std::string, double> t = {5, "abcd", 3.14};
    std::cout << t << std::endl;
    
    return 0;
}
