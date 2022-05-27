class Transform : public Object {
public:

	void LookAt(Vector3 pos) {
		typedef void (*Transform_LookAt_t)(Transform* this_, Vector3 pos);
		return Function<Transform_LookAt_t>("UnityEngine.CoreModule", "UnityEngine", "Transform", "LookAt", 1)(this, pos);
	}

	int ChildCount() {
		typedef int (*Transform_get_childCount_t)(Transform* this_);
		return Function<Transform_get_childCount_t>("UnityEngine.CoreModule", "UnityEngine", "Transform", "get_childCount", 0)(this);
	}

	Transform* GetChild(int index) {
		typedef Transform* (*Transform_GetChild_t)(Transform* this_, int index);
		return Function<Transform_GetChild_t>("UnityEngine.CoreModule", "UnityEngine", "Transform", "GetChild", 1)(this, index);
	}

	Vector3 GetPosition() {
		typedef Vector3 (*Transform_get_position_t)(Transform* this_);
		return Function<Transform_get_position_t>("UnityEngine.CoreModule", "UnityEngine", "Transform", "get_position", 0)(this);
	}

	Vector3 Forward() {
		typedef Vector3(*Transform_get_forward_t)(Transform* this_);
		return Function<Transform_get_forward_t>("UnityEngine.CoreModule", "UnityEngine", "Transform", "get_forward", 0)(this);
	}
};