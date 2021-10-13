#include <iostream>

struct NodoNumero
{
    int numero;
    NodoNumero *siguiente;
};

struct NodoCaracter
{
    char caracter;
    NodoCaracter *siguiente;
    NodoNumero *listaNumeros;
};

NodoCaracter *agregarCaracter(NodoCaracter *&raiz, char caracter)
{
    NodoCaracter *nuevo = new NodoCaracter();
    nuevo->caracter = caracter;
    if (raiz)
    {
        nuevo->siguiente = raiz->siguiente;
        raiz->siguiente = nuevo;
    }
    else
    {
        nuevo->siguiente = raiz;
        raiz = nuevo;
    }
    return nuevo;
}

char buscarNumero(NodoCaracter *&raiz, int numero)
{
    NodoCaracter *aux = raiz;
    while (aux)
    {
        while (aux->listaNumeros)
        {
            std::cout << aux->listaNumeros->numero << std::endl;
            if (aux->listaNumeros->numero == numero)
                return aux->caracter;
            aux->listaNumeros = aux->listaNumeros->siguiente;
        }
        aux = aux->siguiente;
    }
    return '0';
}

void agregarNumero(NodoNumero *&raiz, int numero)
{
    NodoNumero *nuevo = new NodoNumero();
    nuevo->numero = numero;
    if (raiz)
    {
        nuevo->siguiente = raiz->siguiente;
        raiz->siguiente = nuevo;
    }
    else
    {
        nuevo->siguiente = raiz;
        raiz = nuevo;
    }
    return;
}

int main(int argc, char const *argv[])
{
    NodoCaracter *listaCaracteres = NULL, *nuevo = NULL;

    nuevo = agregarCaracter(listaCaracteres, 'a');
    agregarNumero(nuevo->listaNumeros, 10);
    agregarNumero(nuevo->listaNumeros, 20);

    nuevo = agregarCaracter(listaCaracteres, 'b');
    agregarNumero(nuevo->listaNumeros, 50);
    agregarNumero(nuevo->listaNumeros, 30);

    std::cout << buscarNumero(listaCaracteres, 20);
    return 0;
}
