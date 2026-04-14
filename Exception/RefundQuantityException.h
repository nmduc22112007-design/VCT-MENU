//
// Created by ZuraZOR on 4/13/2026.
//

#ifndef VCT_PACIFIC_STAGE_1_REFUNDQUANTITYEXCEPTION_H
#define VCT_PACIFIC_STAGE_1_REFUNDQUANTITYEXCEPTION_H


#include "BaseException.h"

/*
 * RefundQuantityException
 * -----------------------
 * Phát sinh khi người dùng cố gắng hoàn
 * nhiều vé hơn số vé hiện có.
 *
 * Ví dụ:
 *  - Có 3 vé nhưng yêu cầu hoàn 4 vé
 */
class RefundQuantityException : public BaseException {
public:
    RefundQuantityException(int dangCo, int muonHoan)
        : BaseException("Khong the hoan " +
                        std::to_string(muonHoan) +
                        " ve khi chi co " +
                        std::to_string(dangCo) + " ve.") {}
};


#endif //VCT_PACIFIC_STAGE_1_REFUNDQUANTITYEXCEPTION_H