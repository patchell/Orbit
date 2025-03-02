#pragma once

struct CVector {
	double m_x;
	double m_y;
	double m_z;
	CVector() {
		m_x = 0.0;
		m_y = 0.0;
		m_z = 0.0;
	}
	CVector(double x, double y, double z = 0) {
		m_x = x;
		m_y = y;
		m_z = z;
	}

	CVector operator - (CVector r) {

		CVector Result;

		Result.m_x = m_x - r.m_x;
		Result.m_y = m_y - r.m_y;
		Result.m_z = m_z - r.m_z;
		return Result;
	}
	CVector operator + (CVector r) {
		CVector Result;

		Result.m_x = m_x + r.m_x;
		Result.m_y = m_y + r.m_y;
		Result.m_z = m_z + r.m_z;
		return Result;
	}
	CVector operator * (double s)
	{
		CVector Result;

		Result.m_x = m_x * s;
		Result.m_y = m_y * s;
		Result.m_z = m_z * s;
		return Result;
	}

	CVector operator = (CVector r) {
		m_x = r.m_x;
		m_y = r.m_y;
		m_z = r.m_z;
		return *this;
	}

	double Mag() {
		double mag;
		mag = sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
		return mag;
	}
	void Clear() {
		m_x = 0.0;
		m_y = 0.0;
		m_z = 0.0;
	}
	CPoint ToPoint(double Scale) {
		return CPoint(int(m_x / Scale), int(m_y/ Scale));
	}
	CVector CRossProduct(CVector Vect);
	double Distance(CVector Other) ;
	double DistanceSQ(CVector Other) ;
	void Print(const char* s)  ;
};


