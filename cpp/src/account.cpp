#include <iostream>
#include <iomanip>
#include <exception>
#include<random>

#include "account.hpp"

account::Transaction::Transaction(double amount, TransactionType type, double &balance)
{
    this->amount = amount;
    this->type = type;
    balance += amount;
    date = time(nullptr);
}

void account::Transaction::view() const
{
    std::cout.precision(2);
    std::cout << std::put_time(localtime(&date), "%F %T %Z") << "\t" << std::fixed << amount << "\t" << type << std::endl;
}

account::Account::Account(std::string fname, std::string sname, double balance) : created(time(nullptr))
{
    firstname = fname;
    lastname = sname;
    this->balance = balance;
    if (balance > 0.0)
        transactions.push_front(Transaction(balance, Credit, balance));
    accountNo = generate_no(3300000111UL, 3399230329UL);
}

double account::Account::getBalance() const { return balance; }

void account::Account::deposit(double amount)
{
    if (amount <= 0.0)
        throw std::range_error("Can only deposit values greater than zero.");

    transactions.push_front(Transaction(amount, Credit, balance));
}

void account::Account::withdraw(double amount)
{
    transactions.push_front(Transaction(-amount, Debit, balance));
}

void account::Account::transactionHistory() const
{
    std::string sent = "Transaction History";
    std::cout << sent << "\n" << std::string(sent.length(), '-') << std::endl;
    for (const auto &i: transactions)
        i.view();
}

void account::Account::accountInformation() const
{
    std::string sent = "Account Information";
    std::cout << sent << "\n" << std::string(sent.length(), '-') << std::endl;
    std::cout << "Account Holder: " << firstname << ' ' << lastname << std::endl;
    std::cout << "Account No: " << accountNo << std::endl;
    std::cout << "No. of transactions: " << transactions.size() << std::endl;
    std::cout << "Active since: " << ctime(&created) << std::endl;
}

void account::CurrentAccount::withdraw(double amount)
{
    if (balance <= overdraftLimit)
        throw std::range_error(fundsN);

    if (amount > balance)
    {
        if ((balance - amount) < overdraftLimit)
            throw std::range_error(fundsN);

        Account::withdraw(amount);

        transactions.push_front(Transaction(-charge, Charge, balance));
        std::cout << "Account has gone into overdraft. Additional charge applies.";
    }
}

int account::SavingsAccount::count = 0;

void account::SavingsAccount::withdraw(double amount)
{
    if (amount > balance)
        throw std::range_error(fundsN);

    Account::withdraw(amount);
    count++;

    if (count > 3){
        std::cout << "Exceeded daily limit. Additional charge apply.";
        transactions.push_front(Transaction(-amount, Charge, balance));
    }
}

void account::SavingsAccount::applyInterest()
{
    if (balance > 0)
        transactions.push_front(Transaction(balance * rate, Interest, balance));
}

std::random_device rd;

size_t generate_no(size_t min, size_t max)
{
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<std::mt19937_64::result_type> uid(min, max);
    return uid(gen);
}