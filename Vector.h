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

	CVector operator - () {
		CVector r;
		r.m_x = -m_x;
		r.m_y = -m_y;
		r.m_z = -m_z;
		return r;
	}
	CVector operator - (CVector& r) {
		CVector v;

		r = -r;
		v = *this + r;
		return v;
	}
	CVector operator + (CVector& r) {
		CVector v;

		v.m_x = m_x + r.m_x;
		v.m_y = m_y + r.m_y;
		v.m_z = m_z + r.m_z;
		return v;
	}
	CVector operator * (double s)
	{
		CVector r;

		r.m_x = s * m_x;
		r.m_y = s * m_y;
		r.m_z = s * m_z;
		return r;
	}

	CVector operator = (CVector& r) {
		CVector x;
		m_x = x.m_x = r.m_x;
		m_y = x.m_y = r.m_y;
		m_z = x.m_z = r.m_z;
		return x;
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
	CPoint ToPoint() {
		return CPoint(int(m_x), int(m_y));
	}
	CVector CRossProduct(CVector Vect);
	void Print(const char* s);
};


