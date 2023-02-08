/*
1. Адрес может быть представлен в виде произвольного целочисленного типа.
Выводить побайтово в беззнаковом виде, начиная со старшего байта, с символом `.`
(символ точки) в качестве разделителя. Выводятся все байты числа.
2. Адрес может быть представлен в виде строки. Выводится как есть, вне зависимости от содержимого.
3. Адрес может быть представлен в виде контейнеров `std::list`, `std::vector`.
Выводится полное содержимое контейнера поэлементно и разделяется `.` (символом точка). Элементы выводятся как есть.
4. Опционально адрес может быть представлен в виде `std::tuple` при условии, что все типы одинаковы.
Выводится полное содержимое поэлементно и разделяется `.` (одним символом точка). Элементы выводятся как есть.
В случае, если типы кортежа не одинаковы, должна быть выдана ошибка при компиляции кода.

*функция печати должна быть одной шаблонной функцией,
разные варианты входов должны быть реализованы через механизм SFINAE
*вариант для целочисленного представления должен представлять собой одну функцию
*вариант для контейнеров std::list и std::vector должен представлять собой одну функцию
*не должно быть реализации типа "если не совпало с иными - значит это контейнер"
*найдите самый простой способ для печати `std::string` (но функция всё ещё должна быть шаблонной)
*опциональная реализация для `std::tuple` должна приводить к ошибке в случае отличающихся типов
*не должно быть ограничений на размер целочисленных типов (в байтах), на размер контейнеров и кортежа (количество элементов)
*/

#include <vector>
#include <list>
#include <string>
#include <tuple>
#include <iostream>
#include <utility>
#include <type_traits>

template <typename T>
union int_type {
	T x;
	unsigned char s[sizeof(T)];
};

template <typename T>
std::enable_if_t<std::is_integral<T>::value> 
print_ip(T &&ip, std::ostream &os = std::cout)
{
	int_type<T> t {ip};	//t.x = ip;
	for (int i = sizeof(ip) - 1; i >= 0; --i)
	{
		os << unsigned(t.s[i]);
		// also works (whitch one does fit 'production rules'?):
		// os << +(t.s[i]);
		// os << static_cast<unsigned>(t.s[i]);
		// os << static_cast<unsigned>(((unsigned char *)(&ip))[i]);
		// os << +(((uint8_t *)(&ip))[i]);
		// etc...
		if (i)
			os << ".";
	}
	// os << '\n';
}

template <typename T>
std::enable_if_t<std::is_same<T, std::string>::value> 
print_ip(T &&s, std::ostream &os = std::cout)
{
	os << s; // << std::endl;
}

template <
	template <typename, typename> typename Container,
	typename Type, typename Allocator = std::allocator<Type>
	>
std::enable_if_t<std::is_same<Container<Type, Allocator>, std::vector<Type, Allocator>>::value ||
				 std::is_same<Container<Type, Allocator>, std::list<Type, Allocator>>::value>
 print_ip(const Container<Type, Allocator> &container, std::ostream &os = std::cout)
{

	for (auto iter = std::begin(container); iter != std::end(container); ++iter)
	{
		if (iter != std::begin(container))
			os << ".";
		os << *iter;
	}
	// os << '\n';
	return;
}

template <typename TT, int I = std::tuple_size<TT>::value>
void print_ip(const TT &t, std::ostream &os = std::cout)
{
	if constexpr (I > 1)
	{
		static_assert(std::is_same<decltype(std::get<0>(t)), decltype(std::get<I-1>(t))>::value );
		print_ip<TT, I - 1>(t, os);
	}
	os << (std::get<I - 1>(t));
	if constexpr (I < std::tuple_size<TT>::value)
		os << '.';
}


/* also works:

template<std::size_t I = 0, typename... Tp>
std::enable_if_t<I == sizeof...(Tp)>
  print_ip(const std::tuple<Tp...>& t, std::ostream &os = std::cout)
  { }
template<std::size_t I = 0, typename... Tp>
std::enable_if_t<I < sizeof...(Tp)>
  print_ip(const std::tuple<Tp...>& t, std::ostream &os = std::cout)
  {
    os << std::get<I>(t);
	if constexpr (I+1 < sizeof...(Tp))
		os << '.';
    print_ip<I + 1, Tp...>(t, os);
  }

*/