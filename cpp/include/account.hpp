#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <ctime>
#include <list>
#include <string>

namespace account
{
    enum TransactionType { Debit, Credit, Interest, Charge };

    struct Transaction
    {
        private:
            TransactionType type;
            double amount;
            time_t date;

        public:
            /// @brief Register an account transaction
            /// @param amount the amount of the transaction
            /// @param type the type of transaction
            /// @param balance the current account balance
            Transaction(double amount, TransactionType type, double &balance);
            void view() const;
    };

    class IAccount
    {
        public:
            virtual double getBalance() const = 0;
            virtual void deposit(double amount) = 0;
            virtual void withdraw(double amount) = 0;
            virtual void transactionHistory() const = 0;
            virtual void accountInformation() const = 0;
    };

    class Account : public IAccount{
        private:
            std::string firstname, lastname;
            const time_t created;
            size_t accountNo;
        protected:
            double balance;
            std::list<Transaction> transactions;
            const char * fundsN = "Insufficient Funds. Transation Denied";
        public:
            Account(std::string fname, std::string sname, double balance = 0.0);
            double getBalance() const;
            virtual void deposit(double amount);
            virtual void withdraw(double amount);
            void transactionHistory() const;
            virtual void accountInformation() const;
    };

    class CurrentAccount : public Account{
        private:
            const double charge = 12.5;
            const double overdraftLimit = -250;
        public:
            CurrentAccount(std::string fname, std::string sname, double balance) : Account(fname, sname, balance){};
            void withdraw(double amount) override;
    };

    class SavingsAccount : public Account{
        private:
            const double charge = 2.0;
            const double rate = .015;
            static int count;
        public:
            SavingsAccount(std::string fname, std::string sname, double balance) : Account(fname, sname, balance){};
            void withdraw(double amount) override;
            void applyInterest();
    };
}

size_t generate_no(size_t min, size_t max);

#endif // ACCOUNT_HPP