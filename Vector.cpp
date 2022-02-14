#include "pch.h"

CVector CVector::CRossProduct(CVector Vect)
{
    CVector Result;

    Result.m_x = m_y * Vect.m_z - m_z * Vect.m_y;
    Result.m_y = m_z * Vect.m_x - m_x * Vect.m_z;
    Result.m_z = m_x * Vect.m_y - m_y * Vect.m_x;
    return Result;
}

void CVector::Print(const char *s)
{
//    printf("%s:X=%lf  Y=%lf  Z=%lf\n", s, m_x, m_y, m_z);
}