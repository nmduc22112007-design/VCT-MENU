//
// Created by ZuraZOR on 4/13/2026.
//

#ifndef VCT_PACIFIC_STAGE_1_BASEEXCEPTION_H
#define VCT_PACIFIC_STAGE_1_BASEEXCEPTION_H

#include <exception>
#include <string>

/*
 * BaseException
 * --------------
 * Lớp ngoại lệ cơ sở cho toàn bộ hệ thống bán vé.
 * Mọi exception khác đều kế thừa từ lớp này.
 */
class BaseException : public std::exception {
protected:
    std::string message;

public:
    explicit BaseException(std::string msg) : message(std::move(msg)) {}

    // Trả về thông báo lỗi
    const char* what() const noexcept override {
        return message.c_str();
    }
};


#endif //VCT_PACIFIC_STAGE_1_BASEEXCEPTION_H