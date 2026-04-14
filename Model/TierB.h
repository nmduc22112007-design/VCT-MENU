//
// Created by PC on 4/9/2026.
//

#ifndef VCT_PACIFIC_STAGE_1_TIERB_H
#define VCT_PACIFIC_STAGE_1_TIERB_H
#include "Ve.h"

class TierB : public Ve {
public:
    TierB(std::string ngay);
    double tinhHeSoGia() const override;
};

#endif //VCT_PACIFIC_STAGE_1_TIERB_H