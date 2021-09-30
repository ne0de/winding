// Este programa sobreescribe una dirección memoria de un proceso de windows.
// Utiliza game.cpp para probar el programa.

#include <iostream>
#include <windows.h>

#define DIRECCION 0x0061FE1C

int main(int argc, char const *argv[])
{
    DWORD pid;
    HWND Proceso = FindWindow(NULL, "Game");
    int NuevaVida = 5000;

    if(!Proceso){
        puts("No se encontro la ventana.");
        return EXIT_FAILURE;
    }

    GetWindowThreadProcessId(Proceso, &pid);
    HANDLE NuevoProceso = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
    WriteProcessMemory(NuevoProceso, (LPVOID) DIRECCION, &NuevaVida, sizeof(NuevaVida), 0);
    puts("Vida cambiada correctamente.");
  
    return EXIT_SUCCESS;
}
