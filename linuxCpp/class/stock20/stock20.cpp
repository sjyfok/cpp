#include <iostream>
#include <cstring>
#include "stock20.h"

using namespace std;

Stock::Stock(void)
{
    company = "no name";
    shares = 0;
    share_val = 0.0;
    total_val = 0.0;
}

Stock::Stock(const string &co, long n, double pr)
{
    company = co;
    if (n < 0)
    {
        cout << "Number of shares can't be negative; "
            << company << " share set to 0.\n";
        shares = 0;
    }
    else
        shares = n;
    share_val = pr;
    set_tot();
}

Stock::~Stock(void)
{
}


void Stock::buy(long num, double price)
{
    if (num < 0)
    {
        cout << "Number of shares purchased can't be negative. "
            << "Transaction is aborted.\n";

    }
    else
    {
        shares += num;
        share_val = price;
        set_tot();
    }
}

void Stock::sell(int num, double price)
{
    if (num < 0)
    {
        cout << "Number of shares sold can't be negative. "
            << "Transaction is aborted.\n";
    }
    else if (num > shares)
    {
        cout << "You can't sell more than you have! "
            << "Transaction is aborted.\n";
    }
    else
    {
        shares -= num;
        share_val = price;
        set_tot();

    }
}

void Stock::update(double price)
{
    share_val = price;
    set_tot();
}

void Stock::show(void) const
{
    ios_base::fmtflags orig = 
        cout.setf(ios_base::fixed, ios_base::floatfield);
    streamsize prec = cout.precision(3);

    cout << "Company: " << company
        << " Shares: " << shares << '\n'
        << " Share price : $" << share_val
        << " Total Worth: $" << total_val << '\n';
}


const Stock & Stock::topval(const Stock &s)const
{
    if (s.total_val > total_val)
        return s;
    else
        return *this;
}
