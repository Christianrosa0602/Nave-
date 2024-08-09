#include <stdio.h>
#include <Windows.h>
#include <conio.h>

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80

void gotoxy(int x, int y) {
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;    //Variable para almacenar coordernadas
    dwPos.X = x;
    dwPos.Y = y;

    SetConsoleCursorPosition(hCon, dwPos);  //Mueve el cursor de la consola a la posición especificada por dwPos
}

void OcultarCursor() {
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 2;
    cci.bVisible = FALSE;

    SetConsoleCursorInfo(hCon,&cci);
}

class NAVE {
    int x,y;
public:
    NAVE(int _x, int _y) : x(_x), y(_y) {};
    void pintar();
    void borrar();
    void mover();
};

void NAVE::pintar() {
    gotoxy(x,y); printf("  %c",94);
    gotoxy(x,y+1); printf(" %c%c%c", 174, 207, 175);
    gotoxy(x,y+2); printf("%C%C %C%C", 94, 190, 190, 94);
}

void NAVE::borrar() {
    gotoxy(x,y);   printf("         ");
    gotoxy(x,y+1); printf("         ");
    gotoxy(x,y+2); printf("         ");
}

void NAVE::mover() {
    if (_kbhit()) {
        char tecla = _getch();
        borrar();
        //Indica donde moverse
        if (tecla == IZQUIERDA) x--;
        if (tecla == DERECHA) x++;
        if (tecla == ARRIBA) y--;
        if (tecla == ABAJO) y++;
        pintar();
    }
}

int main(){
    OcultarCursor();
    NAVE N(7, 7);
    N.pintar();
    bool game_over = false;
    while (!game_over) {
        N.mover();
        Sleep(30);
    }

    return 0;
}