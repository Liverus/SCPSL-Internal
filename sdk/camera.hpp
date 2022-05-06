class Camera : public OBJECT {
public:

	static Camera* Main() {
		typedef Camera* (*Camera_get_main_t)();
		return Function<Camera_get_main_t>("UnityEngine.CoreModule", "UnityEngine", "Camera", "get_main", 0)();
	}

	static Camera* Current() {
		typedef Camera* (*Camera_get_current_t)();
		return Function<Camera_get_current_t>("UnityEngine.CoreModule", "UnityEngine", "Camera", "get_current", 0)();
	}
};