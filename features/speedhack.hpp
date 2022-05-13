
namespace Speedhack {

	Memory::Hook* get_speed;

	typedef void (*GetSpeed_t)(OBJECT* this_, float* out, bool idk);
	GetSpeed_t GetSpeed;

	void GetSpeed_hk(OBJECT* this_, float* speed, bool idk) {
		GetSpeed(this_, speed, idk);

		auto hub = this_->GetValue<ReferenceHub*>("_hub");

		if (hub->IsLocalPlayer()) {
			*speed = *speed * Config::speedhack_multiplier;
		}
	}

	void Initialize() {
		get_speed = Method("Assembly-CSharp", "", "FirstPersonController", "GetSpeed", 2)->Hook<GetSpeed_t>(GetSpeed_hk, &GetSpeed);
	}

	void Enable() {
		get_speed->Load();
	}

	void Disable() {
		get_speed->Unload();
	}
}