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

	void SetFOV(float fov) {
		typedef void (*Camera_set_fieldOfView_t)(Camera* this_, float fov);
		return Function<Camera_set_fieldOfView_t>("UnityEngine.CoreModule", "UnityEngine", "Camera", "set_fieldOfView", 1)(this, fov);
	}
	
	float GetFOV() {
		typedef float (*Camera_get_fieldOfView_t)(Camera* this_);
		return Function<Camera_get_fieldOfView_t>("UnityEngine.CoreModule", "UnityEngine", "Camera", "get_fieldOfView", 0)(this);
	}

	Vector2 ToScreen(Vector3 pos) {
		typedef Vector3(*Camera_WorldToScreenPoint_t)(Camera* this_, Vector3 pos);
		auto screen_pos = Function<Camera_WorldToScreenPoint_t>("UnityEngine.CoreModule", "UnityEngine", "Camera", "WorldToScreenPoint", 1)(this, pos);

		return Vector2(screen_pos.x, screen_pos.y);
	}

	Transform* GetTransform() {
		typedef Transform* (*Camera_get_transform_t)(Camera* this_);
		return Function<Camera_get_transform_t>("UnityEngine.CoreModule", "UnityEngine", "Camera", "get_transform", 0)(this);
	}

	Vector3 GetPosition() {
		return this->GetTransform()->GetPosition();
	}
};