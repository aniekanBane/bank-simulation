using System;

namespace Bank
{
    public class Transactions
    {
        public decimal Amount { get; }
        public DateTime Date { get; }
        public string Notes { get; }

        public Transactions(decimal amt, DateTime date, string note)
        {
            Amount = amt;
            Date = date;
            Notes = note;
        }
    }
}
