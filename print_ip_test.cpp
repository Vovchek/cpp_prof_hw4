#include <gtest/gtest.h>

#include <sstream>
#include "print_ip.h"

TEST(PrintIpTest, Test1)
{
  std::ostringstream ss;

  print_ip(int8_t{-1}, ss);
  EXPECT_STREQ(ss.str(), "255") << "int8_t{-1}";
  ss.rdbuf()->str("");
  print_ip(int16_t{0}, ss);
  EXPECT_STREQ(ss.str(), "0.0") << "int16_t";
  ss.rdbuf()->str("");
  print_ip(int32_t{2130706433});
  EXPECT_STREQ(ss.str(), "127.0.0.1") << "int32_t";
  ss.rdbuf()->str("");
  print_ip(int64_t{8875824491850138409});
  EXPECT_STREQ(ss.str(), "123.45.67.89.101.112.131.41") << "int64_t";
  ss.rdbuf()->str("");
  print_ip(std::string{"Hello, World !"});
  EXPECT_STREQ(ss.str(), "Hello, World!") << "std::string";
  ss.rdbuf()->str("");
  print_ip(std::vector<int>{100, 200, 300, 400});
  EXPECT_STREQ(ss.str(), "100.200.300.400") << "std::vector<int>";
  ss.rdbuf()->str("");
  print_ip(std::list<short>{400, 300, 200, 100});
  EXPECT_STREQ(ss.str(), "400.300.200.100") << "std::list<short>";
  ss.rdbuf()->str("");
  print_ip(std::make_tuple(123, 456, 789, 0));
  EXPECT_STREQ(ss.str(), "123.456.789.0")

}

