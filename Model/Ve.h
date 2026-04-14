//
// Created by PC on 4/9/2026.
//

#ifndef VCT_PACIFIC_STAGE_1_VE_H
#define VCT_PACIFIC_STAGE_1_VE_H

#include "Entity.h"
#include <string>

class Ve : public Entity {
protected:
    std::string ngaySuDung;
    double giaCoBan;

public:
    Ve(std::string ngay, double gia);
    virtual ~Ve() = default;

    std::string getNgaySuDung() const;
    double getGiaCoBan() const;

    virtual double tinhHeSoGia() const = 0;
    double tinhGia() const override;
};


#endif //VCT_PACIFIC_STAGE_1_VE_H