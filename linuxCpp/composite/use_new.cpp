#include <iostream>
using namespace std;

int main(void)
{
    int *pt = new int;
    *pt = 1001;

    cout << "int ";
    cout << "value = " << *pt << ": localton = " << pt << endl;

    double *pd = new double;
    *pd = 10000001.0;
    
    cout << "double ";
    cout << "value = " << *pd << ": localtion = " << pd << endl;
    cout << "size of pt = " << sizeof(pt);
    cout << ": size of *pt = " << sizeof(*pt) << endl;
    cout << "size of pd = " << sizeof pd;
    cout << ": size of *pd = " << sizeof(*pd) << endl;

    return 0;
}
