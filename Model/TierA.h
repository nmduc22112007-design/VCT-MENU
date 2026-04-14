//
// Created by PC on 4/9/2026.
//

#ifndef VCT_PACIFIC_STAGE_1_TIERA_H
#define VCT_PACIFIC_STAGE_1_TIERA_H

#include "Ve.h"

class TierA : public Ve {
public:
    TierA(std::string ngay);
    double tinhHeSoGia() const override;
};

#endif //VCT_PACIFIC_STAGE_1_TIERA_H