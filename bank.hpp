#ifndef BANK_HPP
#define BANK_HPP

#include <list>
#include <random>
//#include <boost/serialization/access.hpp>

namespace bank
{
    enum TransactionType{Debit, Credit, Interest, Charge};

    class Transaction{
        public:
            double amount;
            TransactionType type;
            time_t date;

            Transaction(double amount, TransactionType type, double& bal);
            void view() const;
    };

    class Account{
        private:
            char fname[50], sname[50];
            time_t date;
            unsigned int acctNo;
        protected:
            std::list<const Transaction> transactions;
            double balance;
        public:
            friend double GetBalance(Account acct);

            Account(char *fname, char *sname, double balance);
            virtual void deposit(double amt);
            virtual void withdraw(double amt);
            std::string acctInfo() const ;
            void TransactionHistory();
    };

    class CurrentAccount : public Account{
        private:
            const double charge = 35.0;
        public:
            CurrentAccount(char *fname, char *sname, double balance) : Account(fname, sname, balance) {};
            void withdraw(double amt);
    };

    class SavingsAccount : public Account{
        private:
            const double charge = 2.0;
            const double rate = 0.012;
        public:
            int count = 0;
            SavingsAccount(char *fname, char *sname, double balance) : Account(fname, sname, balance){};
            void applyInterest();
            void withdraw(double amt);
    };

    class Customer{
        unsigned long userId;
        public:
            std::list<Account> accounts;
            void createAccount();
            void information();
    };

    double GetBalance(Account acct);

    int generateNo(int start, int lim, std::random_device& dre);

    void login();

    // void save(Customer *c);
}
#endif