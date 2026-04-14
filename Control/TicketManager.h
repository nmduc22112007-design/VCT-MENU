//
// Created by PC on 4/9/2026.
//

#ifndef VCT_PACIFIC_STAGE_1_TICKERMANAGER_H
#define VCT_PACIFIC_STAGE_1_TICKERMANAGER_H

#include <vector>
#include <algorithm>

template<typename T>
double tinhTong(const std::vector<T>& ds) {
    double sum = 0;
    for (auto& x : ds) sum += x;
    return sum;
}


#endif //VCT_PACIFIC_STAGE_1_TICKERMANAGER_H