class Screen : public OBJECT {
public:

	static int Width() {
		typedef int (*Screen_get_width_t)();
		return Function<Screen_get_width_t>("UnityEngine.CoreModule", "UnityEngine", "Screen", "get_width", 0)();
	}

	static int Height() {
		typedef int (*Screen_get_height_t)();
		return Function<Screen_get_height_t>("UnityEngine.CoreModule", "UnityEngine", "Screen", "get_height", 0)();
	}
};