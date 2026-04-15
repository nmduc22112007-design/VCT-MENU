#include "Menu.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>

#include "../Exception/BaseException.h"
#include "../Exception/InvalidMatchDayException.h"
#include "../Exception/InvalidNameException.h"
#include "../Exception/InvalidPhoneNumberException.h"
#include "../Model/ThreeDayPass.h"
#include "../Model/TierA.h"
#include "../Model/TierB.h"
#include "../Model/TierS.h"
#include "../Utils/SeatValidator.h"
#include "../Utils/Utils.h"

enum class TrangThaiMuaVe {
    THANH_CONG,
    LOI,
    KHONG_LAM_GI
};

static const std::vector<std::string> NGAY_HOP_LE = {
    "15/05/2026",
    "16/05/2026",
    "17/05/2026"
};

namespace {
void boQuaDongDem() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool tenHopLe(const std::string& ten) {
    if (ten.empty()) {
        return false;
    }

    for (char c : ten) {
        if (!std::isalpha(static_cast<unsigned char>(c)) && c != ' ') {
            return false;
        }
    }
    return true;
}

bool sdtHopLe(const std::string& sdt) {
    if (sdt.length() != 10) {
        return false;
    }

    for (char c : sdt) {
        if (!std::isdigit(static_cast<unsigned char>(c))) {
            return false;
        }
    }
    return true;
}

TrangThaiMuaVe xuLyChonGhe(const std::string& tier,
                           std::string& seat,
                           std::string& zone) {
    while (true) {
        std::cout << "Cac khu vuc ghe hop le cho " << tier << ": ";
        for (const auto& z : SeatValidator::getAllowedSeats(tier)) {
            std::cout << z << ' ';
        }
        std::cout << "\nNhap so ghe (VD: B12): ";
        std::cin >> seat;

        if (!SeatValidator::normalizeSeat(seat, zone)) {
            std::cout << "[LOI] Dinh dang ghe sai. Vi du hop le: B12\n";
            continue;
        }

        if (!SeatValidator::isValidSeat(tier, zone)) {
            std::cout << "[LOI] Khu vuc " << zone << " khong hop le cho " << tier << "\n";
            continue;
        }

        return TrangThaiMuaVe::THANH_CONG;
    }
}

std::shared_ptr<Ve> taoVeTheoLuaChon(int choice,
                                     const std::string& ngay,
                                     const std::string& zone,
                                     const std::string& seat) {
    switch (choice) {
        case 1:
            return std::make_shared<TierB>(ngay, zone, seat);
        case 2:
            return std::make_shared<TierA>(ngay, zone, seat);
        case 3:
            return std::make_shared<TierS>(ngay, zone, seat);
        case 4:
            return std::make_shared<ThreeDayPass>(zone, seat);
        default:
            return nullptr;
    }
}
}

void Menu::hienThiMenu() {
    std::cout << "\n===== MENU MUA / HOAN VE =====\n";
    std::cout << "1. Mua ve Tier B\n";
    std::cout << "2. Mua ve Tier A\n";
    std::cout << "3. Mua ve Tier S\n";
    std::cout << "4. Mua ve 3-Day Pass\n";
    std::cout << "5. Hoan ve\n";
    std::cout << "6. Xem thong tin khach hang hien tai\n";
    std::cout << "0. Quay lai\n";
    std::cout << "================================\n";
}

void Menu::xuLyMenu(TicketManager& manager) {
    int luaChon = -1;

    do {
        std::cout << "\n===== HE THONG BAN VE VCT PACIFIC STAGE 1 =====\n";
        std::cout << "1. Tao hoac chon khach hang bang so dien thoai\n";
        std::cout << "2. Tim khach hang theo ma\n";
        std::cout << "3. Hien thi danh sach khach hang\n";
        std::cout << "4. Hien thi danh sach ve da ban\n";
        std::cout << "0. Luu va thoat\n";
        std::cout << "Lua chon cua ban: ";
        std::cin >> luaChon;
        boQuaDongDem();

        switch (luaChon) {
            case 1: {
                std::string ten;
                std::string sdt;

                while (true) {
                    try {
                        std::cout << "Nhap ho ten: ";
                        std::getline(std::cin, ten);
                        if (!tenHopLe(ten)) {
                            throw InvalidNameException(ten);
                        }
                        break;
                    } catch (const BaseException& e) {
                        std::cout << "[EXCEPTION] " << e.what() << "\n";
                    }
                }

                while (true) {
                    try {
                        std::cout << "Nhap so dien thoai: ";
                        std::getline(std::cin, sdt);
                        if (!sdtHopLe(sdt)) {
                            throw InvalidPhoneNumberException(sdt);
                        }
                        break;
                    } catch (const BaseException& e) {
                        std::cout << "[EXCEPTION] " << e.what() << "\n";
                    }
                }

                bool daTonTai = false;
                auto kh = manager.themKhachHang(ten, sdt, daTonTai);
                if (daTonTai) {
                    std::cout << "[TRUNG] So dien thoai da ton tai. Da mo khach hang cu: "
                              << kh->getMaKH() << " - " << kh->getTen() << "\n";
                } else {
                    std::cout << "[OK] Da tao khach hang moi: " << kh->getMaKH() << "\n";
                }

                xuLyMuaVe(manager, kh);
                break;
            }

            case 2: {
                std::string maKH;
                std::cout << "Nhap ma khach hang: ";
                std::getline(std::cin, maKH);

                auto kh = manager.timKhachHangTheoMa(maKH);
                if (!kh) {
                    std::cout << "[LOI] Khong tim thay khach hang.\n";
                    break;
                }

                std::cout << "[OK] Da tim thay " << kh->getTen() << "\n";
                xuLyMuaVe(manager, kh);
                break;
            }

            case 3:
                manager.hienThiTatCaKhachHang();
                break;

            case 4:
                manager.hienThiTatCaVeDaBan();
                break;

            case 0:
                manager.saveKhachHangCSV();
                manager.saveVeCSV();
                std::cout << "[OK] Da luu du lieu.\n";
                break;

            default:
                std::cout << "[LOI] Lua chon khong hop le.\n";
                break;
        }
    } while (luaChon != 0);
}

void Menu::xuLyMuaVe(TicketManager& manager, const std::shared_ptr<KhachHang>& kh) {
    int choice = -1;

    do {
        try {
            hienThiMenu();
            std::cout << "Lua chon cua ban: ";
            std::cin >> choice;

            if (choice == 0) {
                break;
            }

            std::string ngay;
            if (choice >= 1 && choice <= 3) {
                std::cout << "Nhap ngay (15/05/2026 - 17/05/2026): ";
                std::cin >> ngay;

                if (std::find(NGAY_HOP_LE.begin(), NGAY_HOP_LE.end(), ngay) == NGAY_HOP_LE.end()) {
                    throw InvalidMatchDayException(ngay);
                }
            }

            TrangThaiMuaVe trangThai = TrangThaiMuaVe::KHONG_LAM_GI;
            std::string thongBao;

            switch (choice) {
                case 1:
                case 2:
                case 3:
                case 4: {
                    std::string seat;
                    std::string zone;
                    const std::string tier = choice == 1 ? "TierB"
                                            : choice == 2 ? "TierA"
                                            : choice == 3 ? "TierS"
                                                          : "3DayPass";
                    trangThai = xuLyChonGhe(tier, seat, zone);
                    if (trangThai != TrangThaiMuaVe::THANH_CONG) {
                        break;
                    }

                    auto ve = taoVeTheoLuaChon(choice, ngay, zone, seat);
                    if (!manager.datVeChoKhachHang(kh, ve, thongBao)) {
                        std::cout << thongBao << "\n";
                        trangThai = TrangThaiMuaVe::LOI;
                    } else {
                        std::cout << thongBao << "\n";
                    }
                    break;
                }

                case 5: {
                    if (kh->getSoLuongVe() == 0) {
                        std::cout << "[INFO] Khong co ve nao de hoan.\n";
                        break;
                    }

                    kh->hienThiThongTin();
                    size_t index = 0;
                    std::cout << "Nhap so thu tu ve muon hoan (1-" << kh->getSoLuongVe() << "): ";
                    std::cin >> index;

                    if (!manager.hoanVeChoKhachHang(kh, index - 1, thongBao)) {
                        std::cout << thongBao << "\n";
                    } else {
                        std::cout << thongBao << "\n";
                    }
                    break;
                }

                case 6:
                    kh->hienThiThongTin();
                    break;

                default:
                    std::cout << "[LOI] Lua chon khong hop le.\n";
                    break;
            }
        } catch (const BaseException& e) {
            std::cout << "[EXCEPTION] " << e.what() << "\n";
        }
    } while (true);

    std::cout << "Tong tien hien tai cua khach hang: "
              << formatTien(kh->tongTien())
              << " VND\n";
}
