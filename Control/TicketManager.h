#ifndef VCT_PACIFIC_STAGE_1_TICKERMANAGER_H
#define VCT_PACIFIC_STAGE_1_TICKERMANAGER_H

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../Model/KhachHang.h"
#include "../Model/Ve.h"

class TicketManager {
private:
    std::vector<std::shared_ptr<KhachHang>> dsKhachHang;
    std::string khachHangFilePath;
    std::string veFilePath;

public:
    void loadKhachHangCSV(const std::string& path);
    void loadVeCSV(const std::string& path);
    void saveKhachHangCSV() const;
    void saveVeCSV() const;

    std::vector<std::shared_ptr<KhachHang>>& getDanhSachKhachHang();

    std::shared_ptr<KhachHang> timKhachHangTheoMa(const std::string& maKH);
    std::shared_ptr<KhachHang> timKhachHangTheoSoDienThoai(const std::string& sdt);
    bool tonTaiKhachHangTheoMa(const std::string& maKH) const;
    bool tonTaiKhachHangTheoSoDienThoai(const std::string& sdt) const;
    std::string taoMaKhachHangMoi() const;
    std::shared_ptr<KhachHang> themKhachHang(const std::string& ten,
                                             const std::string& sdt,
                                             bool& daTonTai);

    bool gheDaDuocDat(const std::string& ngay,
                      const std::string& zone,
                      const std::string& seat) const;
    bool datVeChoKhachHang(const std::shared_ptr<KhachHang>& kh,
                           const std::shared_ptr<Ve>& ve,
                           std::string& thongBao);
    bool hoanVeChoKhachHang(const std::shared_ptr<KhachHang>& kh,
                            size_t index,
                            std::string& thongBao);

    void hienThiTatCaKhachHang() const;
    void hienThiTatCaVeDaBan() const;
};

#endif //VCT_PACIFIC_STAGE_1_TICKERMANAGER_H
