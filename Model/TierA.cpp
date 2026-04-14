//
// Created by PC on 4/9/2026.
//

#include "TierA.h"

TierA::TierA(std::string ngay)
    : Ve(ngay, 779000) {}

double TierA::tinhHeSoGia() const {
    return 1.0;
}