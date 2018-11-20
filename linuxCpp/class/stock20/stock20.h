#ifndef STOCK20_H__
#define STOCK20_H__

#include <string>

class Stock
{
    private:
        std::string company;
        int shares;
        double share_val;
        double total_val;
        void set_tot(void) {total_val = shares*share_val;}
    public:
        Stock();
        Stock(const std::string &co, long n = 0, double pr = 0.0);
        ~Stock();
        void buy(long num, double price);
        void sell(int num,  double price);
        void update(double price);
        void show(void) const;      
        const Stock &topval(const Stock &s) const;
};

#endif
