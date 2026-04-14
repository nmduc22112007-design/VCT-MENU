//
// Created by PC on 4/9/2026.
//

#ifndef VCT_PACIFIC_STAGE_1_KHACHHANG_H
#define VCT_PACIFIC_STAGE_1_KHACHHANG_H

#include <string>
#include <vector>
#include <memory>
#include "Ve.h"

class KhachHang {
private:
    std::string ten;
    std::vector<std::shared_ptr<Ve>> danhSachVe;

public:
    // Constructor & Destructor
    KhachHang(std::string t);
    ~KhachHang();

    // Rule of Five
    KhachHang(const KhachHang& other);
    KhachHang& operator=(const KhachHang& other);
    KhachHang(KhachHang&& other) noexcept;
    KhachHang& operator=(KhachHang&& other) noexcept;

    // ===== CAC HAM CO BAN =====
    std::string getTen() const;
    bool themVe(std::shared_ptr<Ve> ve);
    double tongTien() const;

    // ===== CAC HAM PHUC VU HOAN VE =====
    bool hoanVe(size_t index);     // Hoan 1 ve
    void hoanTatCaVe();            // Hoan toan bo ve
    size_t getSoLuongVe() const;   // So luong ve hien tai

    // ===== HIEN THI =====
    void hienThiThongTin() const;
};




#endif //VCT_PACIFIC_STAGE_1_KHACHHANG_H