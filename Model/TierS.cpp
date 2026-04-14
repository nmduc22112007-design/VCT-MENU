//
// Created by PC on 4/9/2026.
//

#include "../Model/TierS.h"

TierS::TierS(std::string ngay)
    : Ve(ngay, 1200000) {}

double TierS::tinhHeSoGia() const {
    return 1.0;
}
