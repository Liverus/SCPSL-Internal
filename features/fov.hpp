namespace FOV {

	Memory::Hook* camera_set_fov;

	typedef void(*Camera_set_fieldOfView_t)(Camera* this_, float fov);
	Camera_set_fieldOfView_t Camera_set_fieldOfView;

	void Camera_set_fieldOfView_hk(Camera* this_, float fov) {
		Camera_set_fieldOfView(this_, Config::fov);
	}

	typedef float (*Camera_get_fieldOfView_t)(Camera* this_);
	Camera_get_fieldOfView_t Camera_get_fieldOfView;

	Camera* camera;

	void Update() {
		if (!camera) return;

		Camera_set_fieldOfView(camera, Config::fov);
	}

	void Start() {
		camera = Camera::Main();
	}

	void Initialize() {
		EventManager::Add("Start", FOV::Start);
		EventManager::Add("Update", FOV::Update);

		camera_set_fov = Method::Resolve("UnityEngine.CoreModule", "UnityEngine", "Camera", "set_fieldOfView", 1)->Hook<Camera_set_fieldOfView_t>(Camera_set_fieldOfView_hk, &Camera_set_fieldOfView);
	}
}