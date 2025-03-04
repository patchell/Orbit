#include "pch.h"

CVector CVector::CRossProduct(CVector Vect)
{
    CVector Result;

    Result.m_x = m_y * Vect.m_z - m_z * Vect.m_y;
    Result.m_y = m_z * Vect.m_x - m_x * Vect.m_z;
    Result.m_z = m_x * Vect.m_y - m_y * Vect.m_x;
    return Result;
}

double CVector::Distance(CVector Other) 
{
	return sqrt(DistanceSQ(Other));;
}

double CVector::DistanceSQ(CVector Other) 
{
	double Distance = 0;

	Distance += (m_x - Other.m_x) * (m_x - Other.m_x);
	Distance += (m_y - Other.m_y) * (m_y - Other.m_y);
	Distance += (m_z - Other.m_z) * (m_z - Other.m_z);
	return Distance;
}

void CVector::Print(const char *s) 
{
	if (theApp.HasConsol()) printf("%s:X=%lf  Y=%lf  Z=%lf\n", s, m_x, m_y, m_z);
}