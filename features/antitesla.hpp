namespace AntiTesla {

	Memory::Hook* player_in_range;

	typedef bool(*TeslaGate_PlayerInHurtRange_t)(OBJECT* this_, OBJECT* ply);
	bool TeslaGate_PlayerInHurtRange_hk(OBJECT* this_, OBJECT* ply) {
		return false;
	}

	void Initialize() {
		player_in_range = Method("Assembly-CSharp", "", "TeslaGate", "PlayerInHurtRange", 1)->Hook<TeslaGate_PlayerInHurtRange_t>(TeslaGate_PlayerInHurtRange_hk);
	}

	void Enable() {
		player_in_range->Load();
	}

	void Disable() {
		player_in_range->Unload();
	}
}