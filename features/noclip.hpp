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
		
		auto class_manager = local_player->GetClassManager();

		class_manager->SetNoclip(&Config::noclip);
	}

	void Initialize() {
		EventManager::Add("OnGUI", Noclip::OnGUI);
	}

	void Enable() {}

	void Disable() {}
}