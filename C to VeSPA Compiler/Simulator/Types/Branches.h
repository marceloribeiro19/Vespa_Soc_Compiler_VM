#ifndef ROCKETSIM_BRANCHES_H
#define ROCKETSIM_BRANCHES_H


typedef enum
{
    COND_BRA = 0b0000,
    COND_BCC,
    COND_BVC,
    COND_BEQ,
    COND_BGE,
    COND_BGT,
    COND_BPL,
    COND_BNV,
    COND_BCS,
    COND_BVS,
    COND_BNE,
    COND_BLT,
    COND_BLE,
    COND_BMI,
    COND_INVAL
}branch_cond_et;
#endif