#include "labs/Lab3.h"

static void pullDesktopResolution(int& horizontal, int& vertical)
{
    RECT desktop;

    const HWND hDesktop = GetDesktopWindow();

    GetWindowRect(hDesktop, &desktop);

    horizontal = desktop.right;
    vertical = desktop.bottom;
}

int main() {
    Operations::Definition::init();

    int width, height;
    pullDesktopResolution(width, height);

    Lab3::work(width, height);

    return 0;
}
