#include "../Model/KhachHang.h"
#include <iostream>
#include <iomanip>
#include "../Utils/Utils.h"

bool KhachHang::daTonTaiGhe(const std::string& ngay,
                            const std::string& zone,
                            const std::string& seat) const {
    for (const auto& ve : danhSachVe) {
        if (ve->getNgaySuDung() == ngay &&
            ve->getKhuVuc() == zone &&
            ve->getSoGhe() == seat) {


            // ✅ 3-Day Pass không so ngày
            if (ve->getTenTier() == "3DayPass")
                return true;

            if (ve->getNgaySuDung() == ngay)
                return true;
            }
    }
    return false;
}

// ========= HOAN VE THEO SO GHE ===========
bool KhachHang::hoanVeTheoGhe(const std::string& ngay,
                               const std::string& seat) {
    for (auto it = danhSachVe.begin(); it != danhSachVe.end(); ++it) {
        if ((*it)->getSoGhe() == seat &&
            (*it)->getNgaySuDung() == ngay) {
            danhSachVe.erase(it);
            return true;
            }
    }
    return false;
}


// ===== CONSTRUCTOR TU CSV =====
KhachHang::KhachHang(const std::string& ma,
                     const std::string& t,
                     const std::string& phone)
    : maKH(ma), ten(t), sdt(phone) {}

// ===== CONSTRUCTOR CU =====
KhachHang::KhachHang(const std::string& t)
    : ten(t) {}

// ===== RULE OF FIVE =====
KhachHang::KhachHang(const KhachHang& other)
    : ten(other.ten), danhSachVe(other.danhSachVe) {}

KhachHang& KhachHang::operator=(const KhachHang& other) {
    if (this != &other) {
        ten = other.ten;
        danhSachVe = other.danhSachVe;
    }
    return *this;
}

KhachHang::KhachHang(KhachHang&& other) noexcept
    : ten(std::move(other.ten)),
      danhSachVe(std::move(other.danhSachVe)) {}

KhachHang& KhachHang::operator=(KhachHang&& other) noexcept {
    if (this != &other) {
        ten = std::move(other.ten);
        danhSachVe = std::move(other.danhSachVe);
    }
    return *this;
}

// ===== CAC HAM CO BAN =====
std::string KhachHang::getTen() const {
    return ten;
}

bool KhachHang::themVe(std::shared_ptr<Ve> ve) {
    if (danhSachVe.size() >= 4)
        return false;

    danhSachVe.push_back(ve);
    return true;
}

double KhachHang::tongTien() const {
    double tong = 0;
    for (const auto& ve : danhSachVe)
        tong += ve->tinhGia();
    return tong;
}

// ===== CAC HAM HOAN VE =====
bool KhachHang::hoanVe(size_t index) {
    if (index >= danhSachVe.size())
        return false;

    danhSachVe.erase(danhSachVe.begin() + index);
    return true;
}

void KhachHang::hoanTatCaVe() {
    danhSachVe.clear();
}

size_t KhachHang::getSoLuongVe() const {
    return danhSachVe.size();
}

// ===== HIEN THI =====
void KhachHang::hienThiThongTin() const {
    std::cout << "Khach hang: " << ten << "\n";
    std::cout << "So luong ve: " << danhSachVe.size() << "\n";

    for (size_t i = 0; i < danhSachVe.size(); ++i) {
        std::cout << "  Ve " << i + 1
                  << " | Loai: " << danhSachVe[i]->getTenTier()
                  << " | Ngay: " << danhSachVe[i]->getNgaySuDung()
                  << " | Ghe: " << danhSachVe[i]->getSoGhe()
                  << " | Gia: "
                  << formatTien(danhSachVe[i]->tinhGia())
                  << " VND\n";
    }

    std::cout << "Tong tien: "
              << formatTien(tongTien())
              << " VND\n";
    std::cout << "----------------------------------\n";
}

std::string KhachHang::getMaKH() const {
    return maKH;
}

std::string KhachHang::getSoDienThoai() const {
    return sdt;
}

const std::vector<std::shared_ptr<Ve>>& KhachHang::getDanhSachVe() const {
    return danhSachVe;
}
