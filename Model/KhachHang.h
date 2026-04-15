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
    std::string maKH;
    std::string sdt;
    std::vector<std::shared_ptr<Ve>> danhSachVe;


public:

    // ===== GETTER =====
    std::string getMaKH() const;
    std::string getSoDienThoai() const;

    bool daTonTaiGhe(const std::string& ngay,
                 const std::string& zone,
                 const std::string& seat) const;
    // Constructor mới (dùng cho CSV)
    KhachHang(const std::string& ma,
              const std::string& t,
              const std::string& phone);

    // Constructor cũ (giữ lại cho menu)
    explicit KhachHang(const std::string& t);

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
    const std::vector<std::shared_ptr<Ve>>& getDanhSachVe() const;

    // ===== HIEN THI =====
    void hienThiThongTin() const;
};




#endif //VCT_PACIFIC_STAGE_1_KHACHHANG_H
