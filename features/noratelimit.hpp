namespace NoRateLimit {

	Memory::Hook* can_execute;

	typedef bool(*RateLimit_CanExecute_t)(OBJECT* this_, bool count);
	bool RateLimit_CanExecute_hk(OBJECT* this_, bool count) {
		return true;
	}

	void Initialize() {
		can_execute = Method("Assembly-CSharp", "Security", "RateLimit", "CanExecute", 1)->Hook<RateLimit_CanExecute_t>(RateLimit_CanExecute_hk);
	}

	void Enable() {
		can_execute->Load();
	}

	void Disable() {
		can_execute->Unload();
	}
}