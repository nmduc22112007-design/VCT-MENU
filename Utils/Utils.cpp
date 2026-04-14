//
// Created by PC on 4/9/2026.
//

#include "Utils.h"

#include <string>

std::string formatTien(double soTien) {
    long long tien = static_cast<long long>(soTien);
    std::string s = std::to_string(tien);

    int dem = 0;
    for (int i = s.length() - 1; i > 0; --i) {
        dem++;
        if (dem == 3) {
            s.insert(i, ",");
            dem = 0;
        }
    }
    return s;
}
