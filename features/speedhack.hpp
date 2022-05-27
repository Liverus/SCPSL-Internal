
namespace Speedhack {

	Memory::Hook* get_speed;

	typedef void (*GetSpeed_t)(Object* this_, float* out, bool idk);
	GetSpeed_t GetSpeed;

	void GetSpeed_hk(Object* this_, float* speed, bool idk) {
		GetSpeed(this_, speed, idk);

		if (Config::speedhack) {
			*speed = *speed * (1 + 0.3 * Config::speedhack_multiplier);
		}
	}

	void Initialize() {
		get_speed = Method::Resolve("Assembly-CSharp", "", "FirstPersonController", "GetSpeed", 2)->Hook<GetSpeed_t>(GetSpeed_hk, &GetSpeed);
	}

	void Enable() {
		get_speed->Load();
	}

	void Disable() {
		get_speed->Unload();
	}
}