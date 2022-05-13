namespace FOV {

	Memory::Hook* camera_get_fov;

	typedef void(*Camera_set_fieldOfView_t)(Camera* this_, float fov);
	Camera_set_fieldOfView_t Camera_set_fieldOfView;

	void Camera_set_fieldOfView_hk(Camera* this_, float fov) {
		return;
	}

	typedef float (*Camera_get_fieldOfView_t)(Camera* this_);
	Camera_get_fieldOfView_t Camera_get_fieldOfView;

	float Camera_get_fieldOfView_hk(Camera* this_) {
		return Config::fov;
	}

	void Update(Camera* this_) {
		Camera_set_fieldOfView(this_, Config::fov);
	}

	void Initialize() {
		EventManager::Add("Render", FOV::Update);
		camera_get_fov = Method("UnityEngine.CoreModule", "UnityEngine", "Camera", "set_fieldOfView", 1)->Hook<Camera_set_fieldOfView_t>(Camera_set_fieldOfView_hk, &Camera_set_fieldOfView);
		camera_get_fov = Method("UnityEngine.CoreModule", "UnityEngine", "Camera", "get_fieldOfView", 0)->Hook<Camera_get_fieldOfView_t>(Camera_get_fieldOfView_hk, &Camera_get_fieldOfView);
	}
}