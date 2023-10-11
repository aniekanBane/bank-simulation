#define BOOST_TEST_MODULE AccountTests testcases
#include <boost/test/included/unit_test.hpp>
#include "account.hpp"
#include <exception>

using namespace account;

BOOST_AUTO_TEST_SUITE(AccountTests)

BOOST_AUTO_TEST_CASE(AccountConstructorTest)
{
    Account acct1("John", "Doe", 1000.0), acct2("My", "Dart");
    BOOST_CHECK_CLOSE(acct1.getBalance(), 1000.0, 0.01);
    BOOST_CHECK_CLOSE(acct2.getBalance(), 0.0, 0.01);
}

BOOST_AUTO_TEST_CASE(AccountDepositTest)
{
    Account acct("John", "Doe", 1000.0);
    acct.deposit(500.0);
    BOOST_CHECK_CLOSE(acct.getBalance(), 1500.0, 0.01);
    BOOST_CHECK_THROW(acct.deposit(0.0), std::range_error);
    BOOST_CHECK_THROW(acct.deposit(-1), std::range_error);
}

BOOST_AUTO_TEST_CASE(AccountWithdrawTest)
{
    Account acct("John", "Doe", 1000.0);
    acct.withdraw(500.0);
    BOOST_CHECK_CLOSE(acct.getBalance(), 500.0, 0.01);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CurrentAccountTests)

BOOST_AUTO_TEST_CASE(CurrentAccountWithdrawTest)
{
    CurrentAccount acct("John", "Doe", 1000.0);
    BOOST_CHECK_THROW(acct.withdraw(1500.0), std::range_error);
    BOOST_CHECK_NO_THROW(acct.withdraw(1150.0));
    BOOST_CHECK_THROW(acct.withdraw(300.0), std::range_error);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(SavingsAccountTests)

BOOST_AUTO_TEST_CASE(SavingsAccountWithdrawTest)
{
    SavingsAccount acct("John", "Doe", 500.0);
    BOOST_CHECK_THROW(acct.withdraw(501.0), std::range_error);
    BOOST_CHECK_NO_THROW(acct.withdraw(200.0));
    BOOST_CHECK_CLOSE(acct.getBalance(), 300.0, 0.01);
}

BOOST_AUTO_TEST_CASE(SavingAccountInterestTest)
{
    SavingsAccount acct("Lacky", "Kolh", 0);
    BOOST_NOEXCEPT(acct.applyInterest());
    acct.deposit(100);
    acct.applyInterest();
    BOOST_CHECK_CLOSE(acct.getBalance(), 100+(100 * .015), 0.01);
}

BOOST_AUTO_TEST_SUITE_END()