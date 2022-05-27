namespace AmbientLight {

	Memory::Hook* get_ambientLight;

	typedef Color (*RenderSettings_get_Ambient_t)(Object* this_);
	RenderSettings_get_Ambient_t RenderSettings_get_Ambient;

	Color get_Ambient_hk(Object* this_) {
		if (Config::no_ambient_light) {
			return Color(0.0f, 0.0f, 0.0f, 0.0f);
		}
		else {
			return RenderSettings_get_Ambient(this_);
		}
	}

	void Initialize() {
		get_ambientLight = Method::Resolve("UnityEngine.CoreModule", "UnityEngine", "RenderSettings", "get_ambientLight", 0)->Hook<RenderSettings_get_Ambient_t>(get_Ambient_hk, &RenderSettings_get_Ambient);
	}

	void Enable() {
		get_ambientLight->Load();
	}

	void Disable() {
		get_ambientLight->Unload();
	}
}