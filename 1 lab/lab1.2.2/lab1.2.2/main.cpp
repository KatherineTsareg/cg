#include "stdafx.h"
#include "Window.h"
#include <SDL2/SDL.h>

int main(int, char *[])
{
    glewInit();

    CWindow window;
    window.Show({1200, 700});
    window.DoGameLoop();

    return 0;
}
