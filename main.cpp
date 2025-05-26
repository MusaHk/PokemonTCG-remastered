#include "WelcomeScreen.h"

int main() {
    WelcomeScreen ws; // Add functionality to continue playing music when window's being dragged.
    ws.init_window();
    ws.init_music();
    ws.while_window_open();
    ws.clear_music();
    ws.clear_window();

    return 0;
}