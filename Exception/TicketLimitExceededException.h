//
// Created by ZuraZOR on 4/13/2026.
//

#ifndef VCT_PACIFIC_STAGE_1_TICKETLIMITEXCEEDEDEXCEPTION_H
#define VCT_PACIFIC_STAGE_1_TICKETLIMITEXCEEDEDEXCEPTION_H


#include "BaseException.h"

/*
 * TicketLimitExceededException
 * ----------------------------
 * Phát sinh khi người dùng:
 *  - Mua quá 4 vé
 *  - Hoàn số vé vượt quá giới hạn cho phép
 */
class TicketLimitExceededException : public BaseException {
public:
    TicketLimitExceededException(int soLuongYeuCau, int toiDa)
        : BaseException("Vuot gioi han ve: Yeu cau " +
                        std::to_string(soLuongYeuCau) +
                        " ve, toi da cho phep " +
                        std::to_string(toiDa) + " ve.") {}
};

#endif //VCT_PACIFIC_STAGE_1_TICKETLIMITEXCEEDEDEXCEPTION_H