#ifndef STOCK1_H__
#define STOCK1_H__

#include <iostream>

using namespace std;


class Stock
{
    private:
        char company[30];
        long shares;
        double share_val;
        double total_val;
        void set_tot(void) {total_val = shares*share_val;}
    public:
        Stock();
        Stock(const char *co, int n = 0, double pr = 0.0);
        ~Stock();
        void buy(long num, double price);
        void sell(int num,  double price);
        void update(double price);
        void show(void);        
};

#endif
