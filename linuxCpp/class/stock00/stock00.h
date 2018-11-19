#ifndef STOCK_H__
#define STOCK_H__

using namespace std;

#include <string>

class Stock
{
    private:
        string company;
        long shares;
        double share_val;
        double total_val;
        void set_tot(void) {total_val = shares*share_val;}
    public:
        void acquire(const string &co, long n, double pr);
        void buy(long num, double price);
        void sell(long name, double price);
        void update(double price);
        void show(void);        
};

#endif
