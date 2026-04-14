//
// Created by PC on 4/9/2026.
//

#include "../Model/Ve.h"

Ve::Ve(std::string ngay, double gia)
    : ngaySuDung(ngay), giaCoBan(gia) {}

std::string Ve::getNgaySuDung() const {
    return ngaySuDung;
}

double Ve::getGiaCoBan() const {
    return giaCoBan;
}

double Ve::tinhGia() const {
    return giaCoBan * tinhHeSoGia();
}
