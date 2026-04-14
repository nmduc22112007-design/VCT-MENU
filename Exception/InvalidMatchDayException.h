//
// Created by ZuraZOR on 4/13/2026.
//

#ifndef VCT_PACIFIC_STAGE_1_INVALIDMATCHDAYEXCEPTION_H
#define VCT_PACIFIC_STAGE_1_INVALIDMATCHDAYEXCEPTION_H


#include "BaseException.h"

/*
 * InvalidMatchDayException
 * ------------------------
 * Phát sinh khi người dùng nhập ngày thi đấu KHÔNG hợp lệ.
 * Chỉ chấp nhận:
 *  - 15/05/2026
 *  - 16/05/2026
 *  - 17/05/2026
 */
class InvalidMatchDayException : public BaseException {
public:
    explicit InvalidMatchDayException(const std::string& ngay)
        : BaseException("Ngay thi dau khong hop le: " + ngay +
        ". Chi chap nhan 15/05/2026, 16/05/2026, 17/05/2026.") {}
};



#endif //VCT_PACIFIC_STAGE_1_INVALIDMATCHDAYEXCEPTION_H