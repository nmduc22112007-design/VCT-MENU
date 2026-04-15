//
// Created by PC on 4/9/2026.
//

#ifndef VCT_PACIFIC_STAGE_1_VE_H
#define VCT_PACIFIC_STAGE_1_VE_H
#pragma once
#include "Entity.h"
#include <string>

class Ve : public Entity {
protected:
    std::string ngaySuDung;
    std::string khuVucGhe;   // A, B, C...
    std::string soGhe;       // A12, B3...
    double giaCoBan;

public:
    Ve(const std::string& ngay,
       const std::string& zone,
       const std::string& seat,
       double gia);

    // ✅ BẮT BUỘC – IMPLEMENT HÀM THUẦN ẢO
    double tinhGia() const override;

    virtual ~Ve() = default;

    std::string getNgaySuDung() const;
    std::string getKhuVuc() const;
    std::string getSoGhe() const;

    virtual std::string getTenTier() const = 0;
    virtual double tinhHeSoGia() const = 0;
};


#endif //VCT_PACIFIC_STAGE_1_VE_H