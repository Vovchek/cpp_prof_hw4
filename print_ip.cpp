#include "print_ip.h"

int main()
{
    print_ip(int8_t{-1});                           // 255
    std::cout << '\n';
    print_ip(int16_t{0});                           // 0.0
    std::cout << '\n';
    print_ip(int32_t{2130706433});                  // 127.0.0.1
    std::cout << '\n';
    print_ip(int64_t{8875824491850138409});         // 123.45.67.89.101.112.131.41
    std::cout << '\n';
    print_ip(std::string{"Hello, World !"});        // Hello, World!
    std::cout << '\n';
    print_ip(std::vector<int>{100, 200, 300, 400}); // 100.200.300.400
    std::cout << '\n';
    print_ip(std::list<short>{400, 300, 200, 100});  // 400.300.200.100
    std::cout << '\n';
    print_ip(std::make_tuple(123, 456, 789, 0));    // 123.456.789.0
    std::cout << '\n';
    return 0;
}