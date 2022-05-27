//bool noclip = false;
//
//if (GetKeyState(VK_UP)) {
//	noclip = true;
//}
//
//this_->SetValue<bool>("NoclipEnabled", &noclip);

namespace Noclip {


	void OnGUI() {
		auto local_player = ReferenceHub::GetLocalHub();

		if (!local_player) return;
		
		auto class_manager = local_player->GetClassManager();
		class_manager->SetNoclip(&Config::noclip);
	}

	void Initialize() {
		EventManager::Add("Update", Noclip::OnGUI);
	}

	void Enable() {}

	void Disable() {}
}