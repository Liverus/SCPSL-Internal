namespace Aimbot {

	Memory::Hook* update;


	bool CanSee(ReferenceHub* hub) {
		return true;
	}

	ReferenceHub* FindTarget() {

		
		auto hubs_dict = ReferenceHub::GetAllHubs();

		// auto hubs_count = hubs_dict->Count();

		if (hubs_dict) {
			std::cout << hubs_dict << std::endl;
		}
		
		//auto hubs_entries = hubs_dict->Entries();

		//for (size_t i = 0; i < hubs_count; i++)
		//{
			//auto entry = hubs_entries->GetValue(i);
			//auto hub = entry->GetValue<ReferenceHub*>("value");
			//auto obj = entry->GetValue<GameObject*>("key");

			//std::cout << hub << std::endl;

			//if (hub->Ready()) {
			//	auto class_manager = hub->GetClassManager();

			//	if (hub->IsLocalPlayer()) continue;
			//	if (!class_manager->IsAlive()) continue;
			//	if (!CanSee(hub)) continue;

			//	std::cout << "AAAA " << hub << std::endl;
			//}
		//}

		return 0;
	}

	typedef void(*CharacterClassManager_Update_t)(ClassManager* this_);
	CharacterClassManager_Update_t CharacterClassManager_Update;

	void CharacterClassManager_Update_hk(ClassManager* this_) {

		CharacterClassManager_Update(this_);

		// Aim
		//auto target = FindTarget();
		//std::cout << target << std::endl;

		

		//if ((GetKeyState(VK_DOWN) & 1)) {
		//	this_->SetNoclip(true);
		//	std::cout << "toggled" << std::endl;
		//}
	}

	void Initialize() {
		update = Method("Assembly-CSharp", "", "CharacterClassManager", "Update", 0)->Hook<CharacterClassManager_Update_t>(CharacterClassManager_Update_hk, &CharacterClassManager_Update);
	}

	void Enable() {
		//player_in_range->Load();
	}

	void Disable() {
		//player_in_range->Unload();
	}
}