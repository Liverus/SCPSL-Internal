namespace AntiTesla {

	Memory::Hook* player_in_range;

	typedef bool(*TeslaGate_PlayerInHurtRange_t)(OBJECT* this_, OBJECT* ply);
	TeslaGate_PlayerInHurtRange_t TeslaGate_PlayerInHurtRange;

	bool TeslaGate_PlayerInHurtRange_hk(OBJECT* this_, OBJECT* ply) {
		if (Config::anti_tesla) {
			return false;
		} else {
			return TeslaGate_PlayerInHurtRange(this_, ply);
		}
	}

	void Initialize() {
		player_in_range = Method("Assembly-CSharp", "", "TeslaGate", "PlayerInHurtRange", 1)->Hook<TeslaGate_PlayerInHurtRange_t>(TeslaGate_PlayerInHurtRange_hk, &TeslaGate_PlayerInHurtRange);
	}

	void Enable() {
		player_in_range->Load();
	}

	void Disable() {
		player_in_range->Unload();
	}
}