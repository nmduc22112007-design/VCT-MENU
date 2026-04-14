//
// Created by PC on 4/9/2026.
//

#ifndef VCT_PACIFIC_STAGE_1_TIERS_H
#define VCT_PACIFIC_STAGE_1_TIERS_H
#include "Ve.h"

class TierS : public Ve {
public:
    TierS(std::string ngay);
    double tinhHeSoGia() const override;
};


#endif //VCT_PACIFIC_STAGE_1_TIERS_H