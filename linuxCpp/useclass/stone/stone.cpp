#include <iostream>
using std::cout;
#include "stonewt.h"

void display(const Stonewt &st, int n);
int main(void)
{
    Stonewt incognito = 275;
    Stonewt wolfe(285.7);
    Stonewt tafa(21, 8);

    cout << "The celebrity weighed ";
    incognito.show_stn();
    cout << "The detective weighed ";
    wolfe.show_stn();
    cout << "The President weighed ";
    tafa.show_lbs();
    incognito = 276.8;
    tafa = 325;
    cout << "After dinner, the celebrity weighed ";
    incognito.show_stn();
    cout << "After dinner, the Pressident weighed ";
    tafa.show_lbs();
    display(tafa, 2);
    cout << "The wrestler weighed even more.\n";
    display(422, 2);
    cout << "No stone left unearned\n";
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
