﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BankSys
{
    class Program
    {
        static void Main(string[] args)
        {
            Bank bank = new Bank();
            bank.OpenAccount("2222", "2222", 20);
            bank.OpenAccount("3333", "3333", 50);
            bank.OpenCredit(10000, "6666", "6666", 0);
            ATM atm = new ATM(bank);
            for (int i = 0; i < 5; i++)
                atm.Transaction();
        }
    }
}
