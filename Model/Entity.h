//
// Created by PC on 4/9/2026.
//

#ifndef VCT_PACIFIC_STAGE_1_ENTITY_H
#define VCT_PACIFIC_STAGE_1_ENTITY_H
#pragma once
class Entity {
public:
    virtual ~Entity() = default;
    virtual double tinhGia() const = 0;
};

#endif //VCT_PACIFIC_STAGE_1_ENTITY_H