#ifndef VCT_PACIFIC_STAGE_1_MENU_H
#define VCT_PACIFIC_STAGE_1_MENU_H

#include <memory>

#include "../Control/TicketManager.h"
#include "../Model/KhachHang.h"

class Menu {
public:
    static void hienThiMenu();
    static void xuLyMuaVe(TicketManager& manager, const std::shared_ptr<KhachHang>& kh);
    static void xuLyMenu(TicketManager& manager);
};

#endif //VCT_PACIFIC_STAGE_1_MENU_H
