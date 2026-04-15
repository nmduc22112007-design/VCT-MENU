cmake_minimum_required(VERSION 4.1)
project(VCT_Pacific_Stage_1)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
# ===== INCLUDE PATHS =====
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        Model
        View
        Control
        Utils
        Exception
)

# ===== EXECUTABLE =====
add_executable(VCT_Pacific_Stage_1
        main.cpp

        # ===== MODEL =====
        Model/Entity.cpp
        Model/Ve.cpp
        Model/TierA.cpp
        Model/TierB.cpp
        Model/TierS.cpp
        Model/ThreeDayPass.cpp
        Model/KhachHang.cpp

        # ===== CONTROLLER =====
        Control/TicketManager.cpp

        # ===== VIEW =====
        View/Menu.cpp

        # ===== UTILS =====
        Utils/Utils.cpp
        Utils/CSVReader.cpp
        Exception/InvalidTicketIndexException.h
)

# ===== ROOT INCLUDE (DE INCLUDE "Control/..." ) =====
target_include_directories(VCT_Pacific_Stage_1 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)