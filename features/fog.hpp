namespace Fog {

	Memory::Hook* get_fog;

	typedef bool(*RenderSettings_get_Fog_t)(OBJECT* this_);

	bool get_Fog_hk(OBJECT* this_) {
		return false;
	}

	void Initialize() {
		get_fog = Method("UnityEngine.CoreModule", "UnityEngine", "RenderSettings", "get_fog", 0)->Hook<RenderSettings_get_Fog_t>(get_Fog_hk);
	}

	void Enable() {
		get_fog->Load();
	}

	void Disable() {
		get_fog->Unload();
	}
}