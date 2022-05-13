
struct Quaternion {
public:
	Quaternion() {};
	Quaternion(float _x, float _y, float _z, float _w) {
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	};

	float x;
	float y;
	float z;
	float w;
};