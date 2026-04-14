#include "../Model/KhachHang.h"
#include <iostream>
#include <iomanip>
#include "../Utils/Utils.h"
// ===== CONSTRUCTOR / DESTRUCTOR =====
KhachHang::KhachHang(std::string t) : ten(t) {}
KhachHang::~KhachHang() {}

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
                  << " | Ngay: " << danhSachVe[i]->getNgaySuDung()
                  << " | Gia: "
                  << formatTien(danhSachVe[i]->tinhGia())
                  << " VND\n";
    }

    std::cout << "Tong tien: "
              << formatTien(tongTien())
              << " VND\n";
    std::cout << "----------------------------------\n";
}