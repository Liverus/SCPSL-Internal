struct Rect {
public:
	Rect() {};
	Rect(float height_, float width_, float xmin_, float ymin_) {
		height = height_;
		width  = width_;
		xmin_  = xmin_;
		ymin_  = ymin_;
	}

	float height;
	float width;
	float xmin;
	float ymin;
};