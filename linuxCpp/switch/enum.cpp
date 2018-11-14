#include <iostream>

using namespace std;

enum {red, orange, yellow, green, blue, violet, indigo};

int main(void)
{
    cout << " Enter color code (0-6)";

    int code;
    cin >> code;
    while(code >= red && code <= indigo)
    {
        switch(code)
        {
            case red:        cout << "Her lips ware red.\n"; break;
            case orange:     cout << "Her hair was orange.\n"; break;
            case yellow:     cout << "Her shoes were yellow.\n";break;
            case green:     cout << "Her nails were green.\n"; break;
            case blue:      cout << "Her sweatsuit was bule.\n";break;
            case violet:    cout << "her eyes were violet.\n"; break;
            case indigo:    cout << "her mood was indigo.\n"; break;
        }
        cout << "Enter color code (0-6):";
        cin >> code;
    }
    cout << "Bye\n";
    return 0;
}
