#include "bank.hpp"
#include "nlohmann/json.hpp"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <exception>
#include <algorithm>
//#include <boost/serialization/list.hpp>
//#include <boost/archive/text_oarchive.hpp>
//#include <boost/archive/text_iarchive.hpp>

using namespace std;
using json = nlohmann::json;

static random_device rd;

namespace bank
{
    Transaction::Transaction(double amount, TransactionType type, double &bal)
    {
        this->amount = amount;
        this->type = type;
        bal += amount;
        date = time(nullptr);
    }

    void Transaction::view() const
    {
        cout.precision(2);
        cout << put_time(localtime(&date), "%F %T %Z") << "\t " << fixed << amount << "\t " << type <<endl;
    }

    Account::Account(char *fname, char *sname, double balance = 0.0)
    {
        strcpy(this->fname, fname);
        strcpy(this->sname, sname);
        this->balance = balance;
        acctNo = generateNo(32000000, 33000000, rd);
        date = time(nullptr);
    }

    void Account::deposit(double amt)
    {
        if (amt <= 0) 
            throw range_error("Can only deposit values greater than zero.");
        transactions.push_front(Transaction(amt, Credit, balance));
    }

    void Account::withdraw(double amt)
    {
        transactions.push_front(Transaction(-amt, Debit, balance));
    }

    string Account::acctInfo() const
    {
        json info = {
            {"Account Holder", fname},
            {"Account No.", acctNo},
            {"No. of Transactions", transactions.size()},
            {"Account Balance", balance},
            {"Active Since", ctime(&date)}
        };

        return info.dump(5);
    }

    void Account::TransactionHistory()
    {
        cout << "Date\t" << setw(24) << "Amount\t" << setw(10) << "Remarks" <<endl;
        for_each(transactions.begin(), transactions.end(), [](const Transaction &i){i.view();});
    }

    void CurrentAccount::withdraw(double amt)
    {
        if (amt > balance) {
            amt += charge;
            cout << "Account has gone into overdraft. Additional charge applies." <<endl;
        }
        Account::withdraw(amt);
    }

    void SavingsAccount::applyInterest()
    {
        transactions.push_front(Transaction(balance * rate, Interest, balance));
    }

    void SavingsAccount::withdraw(double amt)
    {
        if (amt > balance)
            cout << "Insufficient funds. Transaction denied" <<endl;
        else{
            Account::withdraw(amt);
            count ++;

            if (count > 3){
                cout << "Exceeded Limit. Additinal charge applies";
                transactions.push_front(Transaction(-charge, Charge, balance));
            }
        }
    }

    void Customer::createAccount()
    {
        char fn[50], sn[50];
        cout << "Let's begin setting up your account" <<endl;
        cout << "***********************************" <<endl;
        cout << "Enter your first name:" <<endl;
        cin >> fn;
        cout << "Enter your surname:" <<endl;
        cin >> sn;
        cout << "\rPlease wait as we setup your accounts" <<endl;
        accounts.push_back(CurrentAccount(fn, sn, 0.0));
        accounts.push_back(SavingsAccount(fn, sn, 0.0));
        userId = rd();

        unsigned short pin = generateNo(1000, 9999, rd);
        cout << "Your PIN for login: " << pin <<endl;
    }

    void Customer::information() 
    {
        json info;
        info["Id"] = userId;
        info["Accounts"] = {
            {"Current", json::parse(accounts.front().acctInfo())},
            {"Savings", json::parse(accounts.back().acctInfo())}
        };
        
        cout << info.dump(2);
    }

    double GetBalance(Account acct) { return  acct.balance; }

    int generateNo(int start, int lim, random_device& dre)
    {
        uniform_int_distribution <int> uid(start, lim);
        return uid(dre);
    }

    void login()
    {
        unsigned short pin, count = 0;
        cout << "Enter your login pin: ";
        cin >> pin;

        ifstream user("db/C" + to_string(pin));

        do{
            count++;
            cout << "Seems you may have forgotten your pin\nPlease Try again." <<endl;
            cout << "Enter your login pin: ";
            cin >> pin;
            ifstream user("db/C" + to_string(pin));

            if (count == 3){
                cout << "Please create an account or try again later!." <<endl;
                exit(1);
            }
        }while (!user.is_open());
    }

    // void save(Customer *c)
    // {
    //     ofstream file("db/C");

    //     {
    //         boost::archive::text_oarchive oa(file);
    //         oa << *c;
    //     }
    // }

}