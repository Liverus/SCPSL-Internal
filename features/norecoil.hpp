namespace NoRecoil {

	Memory::Hook* recoil_shake;

	typedef void(*CameraShaking_RecoilShake_t)(Object* this_, Object* settings, Object* firearm, float multip);
	CameraShaking_RecoilShake_t CameraShaking_RecoilShake;

	void CameraShaking_RecoilShake_hk(Object* this_, Object* settings, Object* firearm, float multip) {
		if (!Config::aimbot_norecoil) {
			CameraShaking_RecoilShake(this_, settings, firearm, multip);
		}
	};
	
	void Initialize() {
		recoil_shake = Method::Resolve("Assembly-CSharp", "CameraShaking", "RecoilShake", ".ctor", 3)->Hook<CameraShaking_RecoilShake_t>(CameraShaking_RecoilShake_hk, &CameraShaking_RecoilShake);
	}

	void Enable() {
		recoil_shake->Load();
	}

	void Disable() {
		recoil_shake->Unload();
	}
}