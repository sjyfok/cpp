#include <iostream>
#include "brass.h"
using std::ios_base;
using std::cout;
using std::endl;
using std::string;

AcctABC::AcctABC(const string &s, long an, double bal)
{
    fullName = s;
    acctNum = an;
    balance = bal;
}

AcctABC::Deposit(double amt)
{
    if (amt < 0)
        cout << "Negative deposit not allowed; "
            << "deposit is cancelled.\n";
    else
        balance += amt;
}

void AcctABC::Withdraw(double amt)
{
    balance -= amt;
}

AcctABC::Formatting AcctABC::SetFormat() const
{
    Formatting f;
    f.flag = cout.setf(ios_base::fixed, ios_base::floatfield);
    f.pr = cout.precision(2);
    return f;
}

void AcctABC::Restore(Formatting &f) const
{
    cout.setf(f.flag, ios_base::floatfield);
    cout.precision(f.pr);
}


void Brass::Withdraw(double amt)
{
    //format initialState = setFormat();
    //precis prec = cout.precision(2);

    if (amt < 0)
        cout << "Withrawal amount must be positive; "
            << "withdrawal canceled.\n";
    else if (amt <= Balance())
        AcctABC::Withdraw(amt);
    else
        cout << "Withdrawal amount of $" << amt
            << " exceeds your balance.\n"
            << "Withdrawal canceled.\n";
}

void Brass::ViewAcct() const
{
//    format initialState = setFormat();
    Formatting f = SetFormat();
//    precis prec = cout.precision(2);
    cout << "Brass Client: " << FullName() << endl;
    cout << "Account Number: " << AcctNum() << endl;
    cout << "Balance: $" << Balance() << endl;
    Restore(f);
}

BrassPlus::BrassPlus(const string &s, long an, double bal,
        double ml, double r):AcctABC(ba)
{
    maxLoan = ml;
    owesBank = 0.0;
    rate = r;
}

BrassPlus::BrassPlus(const Brass &ba, double ml, double r)
    : AcctABC(ba)
{
    maxLoan = ml;
    owesBank = 0.0;
    rate = r;
}

void BrassPlus::ViewAcct() const
{
    Formatting f = SetFormat();

    cout << "BrassPls Client: " << FullName() << endl;
    cout << "Account Number: " << AcctNum() << endl;
    cout << "Balance: $" << maxLoan << endl;
    cout << "Maximum loan: $" << owesBank << endl;
    cout.precision(3);
    cout << "Loan Rate: " << 100*rate << "%\n";
    Restore(f);
}

Brass::Brass(const string &s, long an, double bal)
{
    fullName = s;
    acctNum = an;
    balance = bal;
}

void Brass::Deposit(double amt)
{
    if (amt < 0)
        cout << "Negative deposit not allowed; "
            << "deposit is cancelled.\n";
    else
        balance += amt;
}


double Brass::Balance() const
{
    return balance;
}





void BrassPlus::Withdraw(double amt)
{
    format initialState = setFormat();
    precis prec = cout.precision(2);

    double bal = Balance();
    if (amt <= bal)
        Brass::Withdraw(amt);
    else if (amt <= bal + maxLoan - owesBank)
    {
        double advance = amt-bal;
        owesBank += advance*(1.0+rate);
        cout << "Bank advance: $" << advance*rate << endl;
        Deposit(advance);
        Brass::Withdraw(amt);
    }
    else
        cout << "Credit limit exceeded. Transaction cancelled.\n";
    restore(initialState, prec);
}

format setFormat()
{
    return cout.setf(std::ios_base::fixed,
            std::ios_base::floatfield);
}

void restore(format f, precis p)
{
    cout.setf(f, std::ios_base::floatfield);
    cout.precision(p);
}
