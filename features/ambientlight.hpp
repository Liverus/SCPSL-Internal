namespace AmbientLight {

	Memory::Hook* get_ambientLight;

	typedef bool(*RenderSettings_get_Ambient_t)(OBJECT* this_);

	Color get_Ambient_hk(OBJECT* this_) {
		return Color(0.0f, 0.0f, 0.0f, 0.0f);
	}

	void Initialize() {
		get_ambientLight = Method("UnityEngine.CoreModule", "UnityEngine", "RenderSettings", "get_ambientLight", 0)->Hook<RenderSettings_get_Ambient_t>(get_Ambient_hk);
	}

	void Enable() {
		get_ambientLight->Load();
	}

	void Disable() {
		get_ambientLight->Unload();
	}
}