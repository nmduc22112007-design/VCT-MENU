#include <iostream>
#include <windows.h>

#include "Control/TicketManager.h"
#include "View/Menu.h"

int main() {
    // ===== UTF-8 CHO WINDOWS CONSOLE =====
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // ===== KHOI TAO CONTROLLER + LOAD DU LIEU THAT TU CSV =====
    TicketManager manager;
    manager.loadKhachHangCSV("Data/KhachHang.csv");
    manager.loadVeCSV("Data/Ve.csv");

    // ===== GOI MENU HE THONG =====
    Menu::xuLyMenu(manager);

    return 0;
}
