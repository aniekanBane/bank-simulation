#include <memory>
#include <iostream>
#include "account.hpp"
#include "utils.hpp"

void accountFunctions(account::Account*);

int main()
{
    clscr;
    std::cout << "Welcome to the Best Bank!\n";

    std::string first_name, last_name;

    do{
        std::cout << "Please enter your firstname > ";
        std::cin >> first_name;
    } while (first_name.empty());
    
    do{
        std::cout << "Please enter your lastname > ";
        std::cin >> last_name;
    }while(last_name.empty());

    double initial_deposit = 0.0;
    do{
        std::cout << "Enter amount for initial deposit > ";
        std::cin >> initial_deposit;
    }while (std::cin.fail());
    
    auto current = std::make_unique<account::CurrentAccount>(first_name, last_name, initial_deposit);
    auto savings = std::make_unique<account::SavingsAccount>(first_name, last_name, initial_deposit);

    char account;
    while(true)
    {
        std::cout << acctMenu;
        std::cin >> account;
        
        switch (account)
        {
            case 'c':
                accountFunctions(current.get());
                break;

            case 's':
                accountFunctions(savings.get());
                break;

            case 'q':
                return 0;
            
            default:
                break;
        }
    }

    return 0;
}

void accountFunctions(account::Account* df)
{
    char choice;
    do{
        std::cout << opMenu;
        double amount;
        std::cin >> choice;
        switch (choice)
        {
        case 'd':
            try{
                clscr;
                std::cout << "Enter amount: ";
                std::cin >> amount;
                df->deposit(amount);
            }catch(std::range_error e){
                std::cout << e.what() << std::endl;
            }catch(std::exception e){
                std::cout << errorMessage;
            }
            break;

        case 'b':
            clscr;
            std::cout << "Account Balance: " << df->getBalance() << std::endl;
            break;

        case 'w': 
            try{
                clscr;
                std::cout << "Enter amount: ";
                std::cin >> amount;
                df->withdraw(amount);
            }catch(std::range_error e){
                std::cout << e.what() << std::endl;
            }catch(std::exception e){
                std::cout << errorMessage;
            }
            break;

        case 'i': 
            clscr;
            df->accountInformation();
            break;

        case 't': 
            clscr;
            df->transactionHistory();
            break;
        
        default:
            choice = 'q';
            break;
        }
    }while(choice != 'q');
}