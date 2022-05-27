namespace Fog {

	Memory::Hook* get_fog;

	typedef bool(*RenderSettings_get_Fog_t)(Object* this_);

	bool get_Fog_hk(Object* this_) {
		return !Config::no_fog;
	}

	void Initialize() {
		get_fog = Method::Resolve("UnityEngine.CoreModule", "UnityEngine", "RenderSettings", "get_fog", 0)->Hook<RenderSettings_get_Fog_t>(get_Fog_hk);
	}

	void Enable() {
		get_fog->Load();
	}

	void Disable() {
		get_fog->Unload();
	}
}