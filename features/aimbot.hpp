

namespace Aimbot {

	Memory::Hook* update;

	Camera* camera;

	struct AimbotTarget {
		ReferenceHub* hub;
		HitboxIdentity hitbox;
		float distance;
	};

	float CalculateDistance(Vector3 pos) {
		auto screen_pos = camera->ToScreen(pos);

		auto width = Screen::Width();
		auto height = Screen::Height();

		auto screen_center = Vector2(width / 2, height / 2);
		auto screen_delta = screen_pos - screen_center;

		auto screen_dist = screen_delta.Length();

		return screen_dist;
	}

	bool IsInFOV(float dist) {
		return dist <= Config::aimbot_fov_value;
	}

	bool CanSee(Vector3 pos) {

		// static int mask = Field("Assembly-CSharp", "InventorySystem.Items.Firearms.Modules", "StandardHitregBase", "HitregMask")->GetStaticValue<int>();

		//auto transform = camera->GetTransform();

		//auto origin = transform->GetPosition() + transform->Forward() * 10;

		//std::cout << origin << " " << pos << std::endl;

		//RaycastHit hit_info;
		//auto hit = linecast(pos, origin, &hit_info, 0);

		//std::cout << hit << " " << hit_info.m_Distance << " " << hit_info.m_Collider << std::endl;

		return true;
	}

	bool FindTarget(Vector3* target) {

		bool first_target = true;
		float min_distance = 0;
		auto hubs_dict = ReferenceHub::GetAllHubs();

		//auto gen_klass = hubs_dict->GetGeneric({
		//	IL2CPP::Class("UnityEngine.CoreModule", "UnityEngine", "GameObject"),
		//	IL2CPP::Class("Assembly-CSharp", "", "ReferenceHub")
		//});
		
		auto entries = hubs_dict->GetEntries();
		auto entries_count = entries->MaxLength();

		for (size_t i = 0; i < entries_count; i++)
		{
			auto entry = entries->GetValue(i);

			auto game_object = entry.key;
			auto reference_hub = entry.value;

			if (game_object && reference_hub) {

				if (reference_hub->IsLocalPlayer()) continue;
				if (!reference_hub->IsAlive()) continue;

				static auto hitboxreg_class = Class("Assembly-CSharp", "", "HitboxIdentity");

				auto hitbox_array = game_object->GetComponents<HitboxIdentity>(hitboxreg_class);
				auto hitbox_count = hitbox_array->MaxLength();

				for (size_t j = 0; j < hitbox_count; j++)
				{
					auto hitbox = hitbox_array->GetValue(j);

					if (!reference_hub->GetClassManager()->IsAnySCP() && hitbox->GetDamageMultiplier() != 350) continue;

					auto hitbox_pos = hitbox->GetMassCenter();

					float dist = CalculateDistance(hitbox_pos);

					if (!CanSee(hitbox_pos)) continue;
					if (Config::aimbot_fov && !IsInFOV(dist)) continue;

					if (first_target || (dist < min_distance)) {
						min_distance = dist;
						*target = hitbox_pos;

						first_target = false;
					}
				}
			}
		}
	
		return min_distance != 0;
	}

	void AimAt(Vector3 pos) {

	}

	void Update(Camera* this_) {

		// Aim
		camera = this_;

		//Vector3 target;
		//bool found_target = FindTarget(&target);

		//if (found_target) {
		//	std::cout << "target: " << target << std::endl;
		//}

		//auto localplayer = ReferenceHub::GetLocalHub();
		//auto movesync = localplayer->GetMovementSync();
		//movesync->SetRotation(Vector2(0, 0));


		//static int mask = Field("Assembly-CSharp", "InventorySystem.Items.MicroHID", "MicroHIDItem", "_mask")->GetStaticValue<int>();
		//std::cout << "hid: " << mask << std::endl;

		//if ((GetKeyState(VK_DOWN) & 1)) {
		//	this_->SetNoclip(true);
		//	std::cout << "toggled" << std::endl;
		//}
	}

	//typedef void(*sendpos_t)(PlayerMovementSync* sync, bool a, bool b);
	//sendpos_t sendpos;
	//void sendpos_hk(PlayerMovementSync* sync, bool a, bool b) {

	//	auto fpc = sync->GetValue<OBJECT*>("_fpc");
	//	auto look = fpc->GetValue<OBJECT*>("_mouseLook");

	//	auto lola = GetKeyState(VK_DOWN);
	//	typedef void(*lol2_t)(OBJECT* this_, float x, bool a, float y, bool b);

	//	Function<lol2_t>("Assembly-CSharp", "", "MouseLook", "OverrideRotation", 4)(look, 0, true, 0, true);
	//	sendpos(sync, a, b);
	//}

	struct ShotMessage {
	public:
		unsigned int TargetNetId;
		Vector3 TargetPosition;
		Quaternion TargetRotation;
		unsigned short ShooterWeaponSerial;
		Vector3 ShooterPosition;
		float ShooterCharacterRotation;
		float ShooterCameraRotation;
	};

	typedef bool (*StandardHitregBase_ClientCalculateHit_t)(OBJECT* this_, ShotMessage* a);
	StandardHitregBase_ClientCalculateHit_t StandardHitregBase_ClientCalculateHit;

	bool StandardHitregBase_ClientCalculateHit_hk(OBJECT* this_, ShotMessage* msg) {
		auto res = StandardHitregBase_ClientCalculateHit(this_, msg);

		if (Config::aimbot) {

			Vector3 target = Vector3(0, 0, 0);
			bool found_target = FindTarget(&target);

			if (found_target) {
				auto origin = msg->ShooterPosition;
				auto delta_angle = origin.DeltaAngle(target);

				msg->ShooterCameraRotation = delta_angle.x;
				msg->ShooterCharacterRotation = delta_angle.y;

				return true;
			}
		}

		return res;
	}

	void Initialize() {
		EventManager::Add("Render", Aimbot::Update);

		// Method("Assembly-CSharp", "", "PlayerMovementSync", "SendPosition", 2)->Hook<sendpos_t>(sendpos_hk, &sendpos);
		Method("Assembly-CSharp", "InventorySystem.Items.Firearms.Modules", "StandardHitregBase", "ClientCalculateHit", 1)->Hook<StandardHitregBase_ClientCalculateHit_t>(StandardHitregBase_ClientCalculateHit_hk, &StandardHitregBase_ClientCalculateHit);
	}
}