#ifndef UTILS_HPP__
#define UTILS_HPP__

#include <sstream>

#define clscr printf("\e[1;1H\e[2J")

template<typename T>
constexpr auto SSTR(const T &x)
{
    return (std::ostringstream() << std::dec << x).str();
};

const char *errorMessage = "Something went wrong!\n";

const char *acctMenu = "\nChoose Account:\n"
                          "(c) Current\n"
                          "(s) Savings\n"
                          "(q) Quit\n> ";

const char *opMenu = "\nPerform Operation:\n"
                             "(d) Make a deposit\n"
                             "(w) Make a withdrawal\n"
                             "(b) Display account balance\n"
                             "(i) Check account info\n"
                             "(t) Transaction history\n"
                             "(q) Back\n>";

#endif
