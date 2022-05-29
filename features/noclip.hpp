//bool noclip = false;
//
//if (GetKeyState(VK_UP)) {
//	noclip = true;
//}
//
//this_->SetValue<bool>("NoclipEnabled", &noclip);

namespace Noclip {

	ReferenceHub* local_player;

	void Update() {
		//if (!local_player) return;

		local_player = ReferenceHub::GetLocalHub();
		
		auto class_manager = local_player->GetClassManager();
		class_manager->SetValue<bool>("NoclipEnabled", &Config::noclip);
	}

	void Start() {
		local_player = ReferenceHub::GetLocalHub();
	}

	void Initialize() {
		//EventManager::Add("Start", Noclip::Start);
		EventManager::Add("Update", Noclip::Update);
	}

	void Enable() {}

	void Disable() {}
}