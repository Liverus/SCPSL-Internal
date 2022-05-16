class Color {
public:
	Color() {};

	Color(float r_, float g_, float b_, float a_ = 1.0f) {
		r = r_;
		g = g_;
		b = b_;
		a = a_;
	}

	friend std::ostream& operator<<(std::ostream& os, const Color& clr) {
		return os << "Color(" << clr.r << ", " << clr.g << ", " << clr.b << ", " << clr.a << ")";
	}

    static Color Rainbow(float speed=0.1f)
    {
        static uint32_t cnt = 0;

        Color color = Color(
            std::sin(speed * cnt + 0) * 0.5 + 0.5,
            std::sin(speed * cnt + 2) * 0.5 + 0.5,
            std::sin(speed * cnt + 4) * 0.5 + 0.5,
            1);

        // Probably redundant
        if (cnt++ >= (uint32_t)-1) cnt = 0;

        return color;
    }

	float r;
	float g;
	float b;
	float a;
};