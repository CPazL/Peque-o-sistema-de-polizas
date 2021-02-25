#include <stdio.h>
#include <stdlib.h>
#include "VerificaArchivos.h"
#include "inicio.h"
#include <windows.h>
#include <ctype.h>
int main()
{
    verificarArchivos();
    Sleep(500);
    system("cls");
    inicio();
    return 0;
}
