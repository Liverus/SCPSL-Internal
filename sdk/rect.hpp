struct Rect {
public:
	Rect() {};
	Rect(float m_XMin_, float m_YMin_, float m_Width_, float m_Height_) {
		m_XMin   = m_XMin_;
		m_YMin   = m_YMin_;
		m_Width  = m_Width_;
		m_Height = m_Height_;
	}

	float m_XMin;
	float m_YMin;
	float m_Width;
	float m_Height;
};