cmake_minimum_required(VERSION 4.1)
project(VCT_Pacific_Stage_1)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
        Model
        View
        Controller
        Utils
        Exception
)


add_executable(VCT_Pacific_Stage_1
        main.cpp
        Model/Entity.cpp
        Model/Entity.h
        Model/Ve.cpp
        Model/Ve.h
        Model/TierA.cpp
        Model/TierA.h
        Model/TierB.cpp
        Model/TierB.h
        Model/TierS.cpp
        Model/TierS.h
        Model/ThreeDayPass.cpp
        Model/ThreeDayPass.h
        Model/KhachHang.cpp
        Model/KhachHang.h

        Control/TicketManager.cpp
        Control/TicketManager.h

        View/Menu.cpp
        View/Menu.h

        Utils/Utils.cpp
        Utils/Utils.h
        Exception/BaseException.h
        Exception/InvalidMatchDayException.h
        Exception/TicketLimitExceededException.h
        Exception/RefundQuantityException.h
        Exception/InvalidTicketIndexException.h
)