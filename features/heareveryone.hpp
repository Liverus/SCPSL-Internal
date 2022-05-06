namespace HearEveryone {

	Memory::Hook* get_roundended_chat;
	
	bool Enabled = true;

	typedef bool(*Radio_get_roundEnded_t)(OBJECT* this_);
	bool Radio_get_roundEnded_hk(OBJECT* this_) {
		return Enabled;
	};

	void Initialize() {
		get_roundended_chat = Method("Assembly-CSharp", "", "Radio", "get_roundEnded", 0)->Hook<Radio_get_roundEnded_t>(Radio_get_roundEnded_hk);
	}

	void Enable() {
		get_roundended_chat->Load();
	}

	void Disable() {
		get_roundended_chat->Unload();
	}
}