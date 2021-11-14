using System;

namespace Bank
{
    class Program
    {
        public static void Clear() => Console.Clear();

        public static (string[], decimal, decimal) Setup()
        {
            Console.WriteLine("Welcome to the Best Bank\nLet's begin by setting up your accounts");
            Console.WriteLine();
            Console.WriteLine("Please Enter your name e.g Fname Sname");
            string[] name = Console.ReadLine().Split(' ');
            Console.WriteLine("\nEnter starting amount for current and savings accounts");
            Console.WriteLine("Current Account:");
            decimal c_amt = decimal.Parse(Console.ReadLine());
            Console.WriteLine("Savings Account:");
            decimal s_amt = decimal.Parse(Console.ReadLine());
            Clear();

            return (name, c_amt, s_amt);
        }

        public static void Actions(ConsoleKey prev, CurrentAcct c, SavingsAcct s)
        {
            switch (Console.ReadKey().Key)
            {
                case ConsoleKey.B:
                    Clear();
                    if (prev == ConsoleKey.C)
                        Console.WriteLine("Account Balance: {0:C}", c.Balance);
                    if (prev == ConsoleKey.S)
                        Console.WriteLine("Account Balance: {0:C}", s.Balance);
                    break;

                case ConsoleKey.D:
                    Clear();
                    Console.WriteLine("Enter Amount");
                    var dep = decimal.Parse(Console.ReadLine());
                    if (prev == ConsoleKey.C)
                        c.Deposit(dep);
                    if (prev == ConsoleKey.S)
                        s.Deposit(dep);
                    break;

                case ConsoleKey.I:
                    Clear();
                    if (prev == ConsoleKey.C)
                        Console.WriteLine("----Account Information----\n{0}", c.AccountInfo);
                    if (prev == ConsoleKey.S)
                        Console.WriteLine("----Account Information----\n{0}", s.AccountInfo);
                    break;

                case ConsoleKey.T:
                    Clear();
                    if (prev == ConsoleKey.C)
                        Console.WriteLine(c.AccountHistory());
                    if (prev == ConsoleKey.S)
                        Console.WriteLine(s.AccountHistory());
                    break;

                case ConsoleKey.R:
                    Clear();
                    if (prev == ConsoleKey.S) s.ApplyInterest();
                    break;

                case ConsoleKey.W:
                    Clear();
                    Console.WriteLine("Enter Amount");
                    var wth = decimal.Parse(Console.ReadLine());
                    if (prev == ConsoleKey.C)
                        c.WithDrawal(wth);
                    if (prev == ConsoleKey.S)
                        s.WithDrawal(wth);
                    break;

                case ConsoleKey.Q:
                    break;

                default:
                    Console.WriteLine("Unrecognized request. Try Again");
                    break;
            }
        }

        static void Main(string[] args)
        {
            var info = Setup();
            var current = new CurrentAcct(info.Item1[0], info.Item1[1], info.Item2);
            var saving = new SavingsAcct(info.Item1[0], info.Item1[1], 0.0012m, info.Item3);
            Clear();
            Console.WriteLine($"Current and Savings accounts created for {current.AccountHolder}\nPress Enter to continue");

            if (Console.ReadKey().Key == ConsoleKey.Enter)
            {
                string[] ops = { "Select (Key Press)","I To Retrieve Account Information", "B To check your balance", "D To make a deposit",
                             "W To make a Withdrawal", "R To apply interest(savings)", "T To view transactions","Any key to go back" };

                do
                {
                    Clear();
                    Console.WriteLine("Perform operation on account (Key Press)\nC Current\nS Savings\nESC To exit");

                    var key = Console.ReadKey().Key;
                    if (key == ConsoleKey.Escape) break;
                    switch (key)
                    {
                        case ConsoleKey.C:
                            Clear();
                            foreach (var op in ops)
                            {
                                if (op.StartsWith("R")) continue;
                                Console.WriteLine(op);
                            }
                            Actions(key, current, saving);
                            break;

                        case ConsoleKey.S:
                            Clear();
                            foreach (var op in ops) Console.WriteLine(op);
                            Actions(key, current, saving);
                            break;

                        default:
                            Console.WriteLine("Unrecognised request. Try again");
                            break;
                    }
                } while (Console.ReadKey().Key != ConsoleKey.Escape);
            }
        }
    }
}
