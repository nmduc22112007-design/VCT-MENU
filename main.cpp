#include <iostream>
#include <filesystem>
#include <windows.h>

#include "Control/TicketManager.h"
#include "View/Menu.h"

// =================================================
// ✅ HAM TIM DUONG DAN DATA
// =================================================
namespace {
    std::string timDuongDanData(const std::string& fileName) {
        namespace fs = std::filesystem;

        fs::path current = fs::current_path();
        for (int i = 0; i < 5; ++i) {
            fs::path candidate = current / "Data" / fileName;
            if (fs::exists(candidate)) {
                return candidate.string();
            }

            if (!current.has_parent_path()) {
                break;
            }
            current = current.parent_path();
        }

        return (fs::path("Data") / fileName).string();
    }
}

// =================================================
// ✅ HAM MAIN
// =================================================
int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    TicketManager manager;

    manager.loadKhachHangCSV(timDuongDanData("KhachHang.csv"));
    manager.loadVeCSV(timDuongDanData("Ve.csv"));

    Menu::xuLyMenu(manager);
    return 0;
}

