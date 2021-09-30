#include <iostream>
#include <windows.h>

using namespace std;

int main(int argc, char const *argv[])
{
    HANDLE OutputHandler = GetStdHandle(STD_OUTPUT_HANDLE);

    int num = 0;
    int health = 200;

    SetConsoleTitle("Game");
    SetConsoleTextAttribute(OutputHandler, 0x0C);

    while (health != 0)
    {
        cin >> num;
        health -= num;
        cout << "Health: " << health;
    }

    SetConsoleTextAttribute(OutputHandler, 0xFF);
    return EXIT_SUCCESS;
}
