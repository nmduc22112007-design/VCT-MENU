#include "Menu.h"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string>

#include "../Model/TierB.h"
#include "../Model/TierA.h"
#include "../Model/TierS.h"
#include "../Model/ThreeDayPass.h"
#include "../Utils/Utils.h"

// ===== EXCEPTION =====
#include "../Exception/InvalidMatchDayException.h"
#include "../Exception/RefundQuantityException.h"
#include "../Exception/BaseException.h"

// ===== DANH SACH NGAY HOP LE =====
static const std::vector<std::string> NGAY_HOP_LE = {
        "15/05/2026",
        "16/05/2026",
        "17/05/2026"
};

// ===== HIEN THI MENU =====
void Menu::hienThiMenu() {
    std::cout << "\n===== HE THONG BAN VE VCT PACIFIC STAGE 1 =====\n";
    std::cout << "1. Mua ve Tier B\n";
    std::cout << "2. Mua ve Tier A\n";
    std::cout << "3. Mua ve Tier S\n";
    std::cout << "4. Mua ve 3-Day Pass (Tier S)\n";
    std::cout << "5. Hoan ve\n";
    std::cout << "0. Ket thuc\n";
    std::cout << "============================================\n";
}

// ===== XU LY MUA / HOAN VE =====
void Menu::xuLyMuaVe(KhachHang& kh) {
    int choice;

    do {
        try {
            hienThiMenu();
            std::cout << "Lua chon cua ban: ";
            std::cin >> choice;

            if (choice == 0) break;

            std::string ngay;
            if (choice >= 1 && choice <= 3) {
                std::cout << "Nhap ngay 15/05/2026, 16/05/2026 hoac 17/05/2026: ";
                std::cin >> ngay;

                // ===== KIEM TRA NGOAI LE NGAY =====
                if (std::find(NGAY_HOP_LE.begin(),
                              NGAY_HOP_LE.end(),
                              ngay) == NGAY_HOP_LE.end()) {
                    throw InvalidMatchDayException(ngay);
                }
            }

            bool thanhCong = true;

            switch (choice) {
                case 1:
                    thanhCong = kh.themVe(std::make_shared<TierB>(ngay));
                    break;

                case 2:
                    thanhCong = kh.themVe(std::make_shared<TierA>(ngay));
                    break;

                case 3:
                    thanhCong = kh.themVe(std::make_shared<TierS>(ngay));
                    break;

                case 4:
                    thanhCong = kh.themVe(std::make_shared<ThreeDayPass>());
                    break;

                case 5: {   // ===== HOAN VE =====
                    if (kh.getSoLuongVe() == 0) {
                        std::cout << "[INFO] Khach hang khong co ve nao de hoan!\n";
                        break;
                    }

                    kh.hienThiThongTin();

                    int luaChonHoan;
                    std::cout << "1. Hoan 1 ve\n";
                    std::cout << "2. Hoan nhieu ve\n";
                    std::cout << "Lua chon: ";
                    std::cin >> luaChonHoan;

                    if (luaChonHoan == 1) {
                        size_t idx;
std::cout << "Nhap so thu tu ve muon hoan: ";
                        std::cin >> idx;

                        if (kh.hoanVe(idx - 1)) {
                            std::cout << "[OK] Hoan ve thanh cong!\n";
                            kh.hienThiThongTin();
                        } else {
                            std::cout << "[ERROR] Ve khong hop le!\n";
                        }
                    }
                    else if (luaChonHoan == 2) {
                        int soLuong;
                        std::cout << "Nhap so luong ve muon hoan: ";
                        std::cin >> soLuong;

                        if (soLuong > kh.getSoLuongVe()) {
                            throw RefundQuantityException(
                                    kh.getSoLuongVe(), soLuong);
                        }

                        std::vector<size_t> dsIndex;
                        for (int i = 0; i < soLuong; ++i) {
                            size_t idx;
                            std::cout << "Nhap so thu tu ve thu " << i + 1 << ": ";
                            std::cin >> idx;
                            dsIndex.push_back(idx - 1);
                        }

                        std::sort(dsIndex.rbegin(), dsIndex.rend());

                        for (size_t index : dsIndex) {
                            kh.hoanVe(index);
                        }

                        std::cout << "[OK] Da hoan ve theo yeu cau!\n";
                        kh.hienThiThongTin();
                    }
                    else {
                        std::cout << "[ERROR] Lua chon khong hop le!\n";
                    }
                    break;
                }

                default:
                    std::cout << "[ERROR] Lua chon khong hop le!\n";
                    continue;
            }

            // ===== THONG BAO MUA VE =====
            if (!thanhCong && choice >= 1 && choice <= 4) {
                std::cout << "[ERROR] Da dat gioi han toi da 4 ve!\n";
                break;
            }

            if (thanhCong && choice >= 1 && choice <= 4) {
                std::cout << "[OK] Mua ve thanh cong!\n";
            }

        }
        catch (const BaseException& e) {
            std::cout << "[EXCEPTION] " << e.what() << "\n";
        }

    } while (true);

    std::cout << "Tong tien phai thanh toan: "
              << formatTien(kh.tongTien())
              << " VND\n";
}