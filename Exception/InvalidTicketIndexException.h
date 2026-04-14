//
// Created by ZuraZOR on 4/13/2026.
//

#ifndef VCT_PACIFIC_STAGE_1_INVALIDTICKETINDEXEXCEPTION_H
#define VCT_PACIFIC_STAGE_1_INVALIDTICKETINDEXEXCEPTION_H

#include "BaseException.h"

/*
 * InvalidTicketIndexException
 * ---------------------------
 * Phát sinh khi người dùng nhập số thứ tự vé
 * không tồn tại trong danh sách.
 */
class InvalidTicketIndexException : public BaseException {
public:
    explicit InvalidTicketIndexException(size_t index)
        : BaseException("So thu tu ve khong ton tai: " +
                        std::to_string(index + 1)) {}
};



#endif //VCT_PACIFIC_STAGE_1_INVALIDTICKETINDEXEXCEPTION_H