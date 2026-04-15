#include "TicketManager.h"

#include <fstream>
#include <iostream>

#include "../Model/ThreeDayPass.h"
#include "../Model/TierA.h"
#include "../Model/TierB.h"
#include "../Model/TierS.h"
#include "../Utils/CSVReader.h"
#include "../Utils/Utils.h"
namespace {
bool ngayBiTrungLich(const std::string& ngay1, const std::string& ngay2) {
    if (ngay1 == ngay2) {
        return true;
    }

    const std::string ve3Ngay = "15-16-17/05/2026";
    const bool laVe3Ngay1 = ngay1 == ve3Ngay;
    const bool laVe3Ngay2 = ngay2 == ve3Ngay;

    if (laVe3Ngay1 && (ngay2 == "15/05/2026" || ngay2 == "16/05/2026" || ngay2 == "17/05/2026")) {
        return true;
    }

    if (laVe3Ngay2 && (ngay1 == "15/05/2026" || ngay1 == "16/05/2026" || ngay1 == "17/05/2026")) {
        return true;
    }

    return false;
}

std::shared_ptr<Ve> taoVeTuDuLieu(const std::string& tier,
                                  const std::string& ngay,
                                  const std::string& zone,
                                  const std::string& seat) {
    if (tier == "TierB") {
        return std::make_shared<TierB>(ngay, zone, seat);
    }
    if (tier == "TierA") {
        return std::make_shared<TierA>(ngay, zone, seat);
    }
    if (tier == "TierS") {
        return std::make_shared<TierS>(ngay, zone, seat);
    }
    if (tier == "3DayPass") {
        return std::make_shared<ThreeDayPass>(zone, seat);
    }
    return nullptr;
}
}

void TicketManager::loadKhachHangCSV(const std::string& path) {
    khachHangFilePath = path;
    auto rows = CSVReader::readCSV(path);

    for (const auto& r : rows) {
        if (r.size() < 3) {
            continue;
        }

        const std::string& maKH = r[0];
        const std::string& ten = r[1];
        const std::string& sdt = r[2];

        if (tonTaiKhachHangTheoMa(maKH)) {
            std::cout << "[TRUNG] Bo qua khach hang co ma bi trung: " << maKH << "\n";
            continue;
        }

        if (tonTaiKhachHangTheoSoDienThoai(sdt)) {
            std::cout << "[TRUNG] Bo qua khach hang co so dien thoai bi trung: " << sdt << "\n";
            continue;
        }

        dsKhachHang.push_back(std::make_shared<KhachHang>(maKH, ten, sdt));
    }

    std::cout << "[INFO] Da load " << dsKhachHang.size() << " khach hang tu CSV.\n";
}

void TicketManager::loadVeCSV(const std::string& path) {
    veFilePath = path;
    auto rows = CSVReader::readCSV(path);
    size_t soVeDaLoad = 0;

    for (const auto& r : rows) {
        if (r.size() < 6) {
            continue;
        }

        const std::string& maKH = r[1];
        const std::string& tier = r[2];
        const std::string& ngay = r[3];
        const std::string& zone = r[4];
        const std::string& seat = r[5];

        auto kh = timKhachHangTheoMa(maKH);
        if (!kh) {
            std::cout << "[LOI] Khong tim thay khach hang " << maKH << " cho ve trong CSV.\n";
            continue;
        }

        if (gheDaDuocDat(ngay, zone, seat)) {
            std::cout << "[TRUNG] Bo qua ve bi trung ghe: " << ngay << " - " << zone << seat << "\n";
            continue;
        }

        auto ve = taoVeTuDuLieu(tier, ngay, zone, seat);
        if (!ve) {
            std::cout << "[LOI] Loai ve khong hop le trong CSV: " << tier << "\n";
            continue;
        }

        if (!kh->themVe(ve)) {
            std::cout << "[LOI] Khach hang " << maKH
                      << " vuot gioi han 4 ve khi load du lieu.\n";
            continue;
        }

        ++soVeDaLoad;
    }

    std::cout << "[INFO] Da load " << soVeDaLoad << " ve tu CSV.\n";
}

void TicketManager::saveKhachHangCSV() const {
    if (khachHangFilePath.empty()) {
        return;
    }

    std::ofstream file(khachHangFilePath);
    file << "customer_id,name,phone\n";
    for (const auto& kh : dsKhachHang) {
        file << kh->getMaKH() << ','
             << kh->getTen() << ','
             << kh->getSoDienThoai() << '\n';
    }
}

void TicketManager::saveVeCSV() const {
    if (veFilePath.empty()) {
        return;
    }

    std::ofstream file(veFilePath);
    file << "ticket_id,customer_id,tier,match_day,seat_zone,seat_number\n";

    int stt = 1;
    for (const auto& kh : dsKhachHang) {
        for (const auto& ve : kh->getDanhSachVe()) {
            file << "VE";
            if (stt < 10) {
                file << "00";
            } else if (stt < 100) {
                file << '0';
            }
            file << stt++ << ','
                 << kh->getMaKH() << ','
                 << ve->getTenTier() << ','
                 << ve->getNgaySuDung() << ','
                 << ve->getKhuVuc() << ','
                 << ve->getSoGhe() << '\n';
        }
    }
}

std::vector<std::shared_ptr<KhachHang>>& TicketManager::getDanhSachKhachHang() {
    return dsKhachHang;
}

std::shared_ptr<KhachHang> TicketManager::timKhachHangTheoMa(const std::string& maKH) {
    for (auto& kh : dsKhachHang) {
        if (kh->getMaKH() == maKH) {
            return kh;
        }
    }
    return nullptr;
}

std::shared_ptr<KhachHang> TicketManager::timKhachHangTheoSoDienThoai(const std::string& sdt) {
    for (auto& kh : dsKhachHang) {
        if (kh->getSoDienThoai() == sdt) {
            return kh;
        }
    }
    return nullptr;
}

bool TicketManager::tonTaiKhachHangTheoMa(const std::string& maKH) const {
    for (const auto& kh : dsKhachHang) {
        if (kh->getMaKH() == maKH) {
            return true;
        }
    }
    return false;
}

bool TicketManager::tonTaiKhachHangTheoSoDienThoai(const std::string& sdt) const {
    for (const auto& kh : dsKhachHang) {
        if (kh->getSoDienThoai() == sdt) {
            return true;
        }
    }
    return false;
}

std::string TicketManager::taoMaKhachHangMoi() const {
    const int soThuTu = static_cast<int>(dsKhachHang.size()) + 1;
    if (soThuTu < 10) {
        return "KH00" + std::to_string(soThuTu);
    }
    if (soThuTu < 100) {
        return "KH0" + std::to_string(soThuTu);
    }
    return "KH" + std::to_string(soThuTu);
}

std::shared_ptr<KhachHang> TicketManager::themKhachHang(const std::string& ten,
                                                        const std::string& sdt,
                                                        bool& daTonTai) {
    auto kh = timKhachHangTheoSoDienThoai(sdt);
    if (kh) {
        daTonTai = true;
        return kh;
    }

    daTonTai = false;
    auto khMoi = std::make_shared<KhachHang>(taoMaKhachHangMoi(), ten, sdt);
    dsKhachHang.push_back(khMoi);
    return khMoi;
}

bool TicketManager::gheDaDuocDat(const std::string& ngay,
                                 const std::string& zone,
                                 const std::string& seat) const {
    for (const auto& kh : dsKhachHang) {
        for (const auto& ve : kh->getDanhSachVe()) {
            if (ve->getKhuVuc() == zone &&
                ve->getSoGhe() == seat &&
                ngayBiTrungLich(ve->getNgaySuDung(), ngay)) {
                return true;
            }
        }
    }
    return false;
}

bool TicketManager::datVeChoKhachHang(const std::shared_ptr<KhachHang>& kh,
                                      const std::shared_ptr<Ve>& ve,
                                      std::string& thongBao) {
    if (!kh || !ve) {
        thongBao = "[LOI] Du lieu dat ve khong hop le.";
        return false;
    }

    if (gheDaDuocDat(ve->getNgaySuDung(), ve->getKhuVuc(), ve->getSoGhe())) {
        thongBao = "[TRUNG] Ghe " + ve->getSoGhe() + " da duoc dat, vui long chon ghe khac.";
        return false;
    }

    if (!kh->themVe(ve)) {
        thongBao = "[LOI] Khach hang da dat toi da 4 ve.";
        return false;
    }

    thongBao = "[OK] Mua ve thanh cong.";
    return true;
}

bool TicketManager::hoanVeChoKhachHang(const std::shared_ptr<KhachHang>& kh,
                                       size_t index,
                                       std::string& thongBao) {
    if (!kh) {
        thongBao = "[LOI] Khong tim thay khach hang.";
        return false;
    }

    if (!kh->hoanVe(index)) {
        thongBao = "[LOI] So thu tu ve khong hop le.";
        return false;
    }

    thongBao = "[OK] Hoan ve thanh cong.";
    return true;
}

void TicketManager::hienThiTatCaKhachHang() const {
    if (dsKhachHang.empty()) {
        std::cout << "[INFO] Chua co khach hang nao.\n";
        return;
    }

    std::cout << "\n===== DANH SACH KHACH HANG =====\n";
    for (const auto& kh : dsKhachHang) {
        std::cout << kh->getMaKH()
                  << " | " << kh->getTen()
                  << " | " << kh->getSoDienThoai()
                  << " | So ve: " << kh->getSoLuongVe()
                  << '\n';
    }
}

void TicketManager::hienThiTatCaVeDaBan() const {
    std::cout << "\n===== DANH SACH VE DA BAN =====\n";
    bool coVe = false;

    for (const auto& kh : dsKhachHang) {
        for (const auto& ve : kh->getDanhSachVe()) {
            coVe = true;
            std::cout << kh->getMaKH()
                      << " | " << kh->getTen()
                      << " | " << ve->getTenTier()
                      << " | " << ve->getNgaySuDung()
                      << " | " << ve->getSoGhe()
                      << " | " << formatTien(ve->tinhGia()) << " VND\n";
        }
    }

    if (!coVe) {
        std::cout << "[INFO] Chua co ve nao duoc ban.\n";
    }
}
