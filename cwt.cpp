// Este programa cambia el titulo de una vetana, solo funciona en un sistema operativo windows.

#include <iostream>

#ifdef _WIN32 
    #include <windows.h>
#else
    #error Sistema no compatible
#endif

using namespace std;

int main(int argc, char const *argv[])
{
    // Manipulador para el proceso.
    HWND Process;

    if(argc != 3){
        cout << "Use: " << argv[0] << " <window_title> <new_title>";
        return EXIT_FAILURE;
    }

    const char *window_title = argv[1];
    const char *new_title = argv[2];
  
    // Se obtiene el proceso a partir del titulo dado.
    Process = FindWindow(NULL, window_title);

    if(!Process){
        puts("Window not found");
        return EXIT_FAILURE;
    }

    SetWindowText(Process, new_title);
    puts("Windows title changed.");

    return EXIT_SUCCESS;
}
