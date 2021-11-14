using System;
using System.Collections.Generic;
using System.Text;

namespace Bank
{
    /// <summary>Parent class <c>BankAccount</c></summary>
    public class BankAccount
    {
        protected string _fname;
        protected string _sname;

        /// <value>Property <c> Account Number</c> Account number associated with the bank account </value>
        public string Account_number { get; }

        protected List<Transactions> transactions = new();
        private static readonly Random numberSeed = new();
        private readonly string created = DateTime.Now.ToShortDateString();

        /// <summary>Base constructor</summary>
        /// <param name="fname">Firstname of account holder</param>
        /// <param name="sname">Surname of account holder</param>
        /// <param name="bal">Initial amount in account</param>
        /// <return>No return value</return>
        public BankAccount(string fname, string sname, decimal bal)
        {
            _fname = fname;
            _sname = sname;
            Account_number = GetNumber();
            Deposit(bal, "Intitial Deposit");
        }

        /// <value>Property <c> Balance</c> Amount in account </value>
        public decimal Balance
        {
            get
            {
                decimal balance = 0;
                foreach (var item in transactions)
                {
                    balance += item.Amount;
                }
                return balance;
            }
        }

        /// <value>Name of account owner</value>
        public string AccountHolder => $"{_fname} {_sname}";
        /// <value>Description of account</value>
        public string AccountInfo => $"Holder: {AccountHolder}\nAccount no: {Account_number}\nDate created: {created}";

        /// <summary>Make a deposit into account</summary>
        /// <param name="amt"> Amount to deposit </param>
        /// <param name="note">Description of Transaction</param>
        /// <exception cref="ArgumentOutOfRangeException"></exception>
        public virtual void Deposit(decimal amt, string note = "CR")
        {
            if (amt <= 0)
            {
                throw new ArgumentOutOfRangeException(nameof(amt), "Can only deposit positive amounts");
            }
            transactions.Add(new Transactions(amt, DateTime.Now.ToLocalTime(), note));
        }

        /// <summary>Make a withdrawalfrom acccount</summary>
        /// <param name="amt"> Amount to withdraw </param>
        public virtual void WithDrawal(decimal amt, string note)
        {
            transactions.Add(new Transactions(-amt, DateTime.Now.ToLocalTime(), note));
        }

        /// <summary>Format list of transactions into a table like view</summary>
        /// <returns>string of all running transactions recorded</returns>
        public string AccountHistory()
        {
            var report = new StringBuilder();
            report.AppendLine("Date\t\t\t|\tAmount\t\t| Desc");
            report.AppendLine("---------------------------------------------------------------------");

            foreach (var item in transactions)
            {
                report.AppendLine($"{item.Date}\t|\t{item.Amount:C}\t\t| {item.Notes}");
            }
            //Console.WriteLine(report.ToString());

            return report.ToString();
        }

        private static string GetNumber()
        {
            lock (numberSeed)
            {
                return Convert.ToString(numberSeed.Next(32000000, 33000000));
            }
        }
    }

    /// <summary>Child class<c> CurrentAcct</c></summary>
    internal class CurrentAcct : BankAccount
    {
        private const decimal CHARGE = 35.0m;

        public CurrentAcct(string fname, string sname, decimal bal) : base(fname, sname, bal) { }

        public override void WithDrawal(decimal amt, string note = "DR")
        {
            if (amt > Balance)
            {
                amt += CHARGE;
            }

            base.WithDrawal(amt, note);
        }
    }

    /// <summary>Child class<c> SavingsAcct</c></summary>
    internal class SavingsAcct : BankAccount
    {
        public int count = 0;
        public decimal Rate { get; set; }
        private const decimal CHARGE = 2.0m;

        public SavingsAcct(string fname, string sname, decimal rate, decimal bal) : base(fname, sname, bal)
        {
            Rate = rate;
        }

        /// <summary>Apply Interst Rate</summary>
        public void ApplyInterest()
        {
            transactions.Add(new Transactions(Balance * Rate, DateTime.Now.ToLocalTime(), "IR"));
        }

        public override void WithDrawal(decimal amt, string note = "DR")
        {
            if (amt > Balance) Console.WriteLine("Insufficient funds. Try making a deposit.");
            else
            {
                base.WithDrawal(amt, note);
                count++;
                if (count > 3)
                {
                    Console.WriteLine($"Exceeded Limit - Additional charge of {CHARGE:C}");
                    base.WithDrawal(CHARGE, "CH");
                }
            }
        }
    }
}
