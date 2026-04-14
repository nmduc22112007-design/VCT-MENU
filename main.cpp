#include <iostream>
#include <vector>
#include <memory>
#include<windows.h>


#include "Model/KhachHang.h"
#include "View/Menu.h"
#include "Model/TierB.h"
#include "Model/TierA.h"
#include "Model/TierS.h"
#include "Model/ThreeDayPass.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    std::vector<std::shared_ptr<KhachHang>> danhSachKhachHang;

    // ===== 1️⃣ TAO 9 DU LIEU MAU =====
    for (int i = 1; i <= 9; ++i) {
        auto kh = std::make_shared<KhachHang>("Khach hang thu " + std::to_string(i));

        kh->themVe(std::make_shared<TierB>("15/05/2026"));
        kh->themVe(std::make_shared<TierA>("16/05/2026"));
        kh->themVe(std::make_shared<TierS>("17/05/2026"));

        if (i % 3 == 0) {
            kh->themVe(std::make_shared<ThreeDayPass>());
        }

        danhSachKhachHang.push_back(kh);
    }

    // ===== 2️⃣ DU LIEU THU 10 - NGUOI DUNG NHAP =====
    std::string ten;
    std::cout << "Nhap ten khach hang thu 10: ";
    std::getline(std::cin, ten);

    auto khNguoiDung = std::make_shared<KhachHang>(ten);
    Menu::xuLyMuaVe(*khNguoiDung);

    danhSachKhachHang.push_back(khNguoiDung);

    // ===== 3️⃣ HIEN THI THONG TIN CA 10 KHACH HANG =====
    std::cout << "\n===== DANH SACH 10 KHACH HANG =====\n";
    for (const auto& kh : danhSachKhachHang) {
        kh->hienThiThongTin();
    }

    return 0;
}
