namespace HearEveryone {

	Memory::Hook* get_roundended_chat;

	typedef bool(*Radio_get_roundEnded_t)(Object* this_);
	bool Radio_get_roundEnded_hk(Object* this_) {
		return Config::hear_everyone;
	};

	void Initialize() {
		get_roundended_chat = Method::Resolve("Assembly-CSharp", "", "Radio", "get_roundEnded", 0)->Hook<Radio_get_roundEnded_t>(Radio_get_roundEnded_hk);
	}

	void Enable() {
		get_roundended_chat->Load();
	}

	void Disable() {
		get_roundended_chat->Unload();
	}
}