#include <iostream>
using std::cout;
#include "stonewt1.h"

void display(const Stonewt &st, int n);
int main(void)
{
    Stonewt poppint(9, 2.8);
    double p_wt = poppint;
    cout << "Convert to double => ";
    cout << "Popints: " << p_wt << " pounds.\n";
    cout << "Convert to int => ";
    cout << "Popints: " << int(poppint) << " pounds.\n";
    return 0;

}


void display(const Stonewt &st, int n)
{
    for (int i = 0; i < n; i ++)
    {
        cout << "Wow! ";
        st.show_stn();
    }
}
