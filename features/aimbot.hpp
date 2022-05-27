

namespace Aimbot {

	struct AimbotTarget {
		bool found;
		ReferenceHub* hub;
		HitboxIdentity* hitbox;
		Vector3 pos;
		int multiplier;
		float distance;
	};

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

	AimbotTarget target { false, 0, 0, Vector3(0, 0, 0), 0, 0 };
	Camera* camera;

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

	bool CanSee(Vector3 pos, ReferenceHub* hub) {

		auto origin = camera->GetPosition();

		RaycastHit hit_info;
		auto hit = Physics::Linecast(origin, pos, &hit_info, 1208238081, 0);

		return !hit;
	}

	void FindTarget() {

		target = { false, 0, 0, Vector3(0, 0, 0), 0, 0 };

		auto hubs_dict = ReferenceHub::GetAllHubs();
		auto localplayer = ReferenceHub::GetLocalHub();

		if (!localplayer || !hubs_dict) return;

		//auto gen_klass = hubs_dict->GetGeneric({
		//	IL2CPP::Class("UnityEngine.CoreModule", "UnityEngine", "GameObject"),
		//	IL2CPP::Class("Assembly-CSharp", "", "ReferenceHub")
		//});
		
		auto entries = hubs_dict->GetEntries();
		auto entries_count = entries->GetMaxLength();

		for (size_t i = 0; i < entries_count; i++){

			auto entry = entries->GetValue(i);

			auto game_object = entry.key;
			auto reference_hub = entry.value;

			if (game_object && reference_hub) {

				if (reference_hub->IsLocalPlayer()) continue;
				if (!reference_hub->IsAlive()) continue;
				if (reference_hub->IsSpawnProtected()) continue;
				if (!Config::aimbot_friendlyfire && HitboxIdentity::IsFriendlyFire(localplayer, reference_hub)) continue;

				static auto hitboxreg_class = Class::Resolve("Assembly-CSharp", "", "HitboxIdentity");

				auto hitbox_array = game_object->GetComponents<HitboxIdentity>(hitboxreg_class);
				auto hitbox_count = hitbox_array->GetMaxLength();

				for (size_t j = 0; j < hitbox_count; j++)
				{
					auto hitbox = hitbox_array->GetValue(j);
					auto hitbox_multiplier = hitbox->GetDamageMultiplier();

					auto hitbox_pos = hitbox->GetMassCenter();

					if (!CanSee(hitbox_pos, reference_hub)) continue;

					float dist = CalculateDistance(hitbox_pos);

					if (Config::aimbot_fov && !IsInFOV(dist)) continue;

					if (!target.found || (hitbox_multiplier >= target.multiplier && dist < target.distance)) {
						target = { true, reference_hub, hitbox, hitbox_pos, hitbox_multiplier, dist };
					}
				}
			}
		}
	}

	typedef bool (*StandardHitregBase_ClientCalculateHit_t)(Object* this_, ShotMessage* a);
	StandardHitregBase_ClientCalculateHit_t StandardHitregBase_ClientCalculateHit;

	bool StandardHitregBase_ClientCalculateHit_hk(Object* this_, ShotMessage* msg) {

		auto res = StandardHitregBase_ClientCalculateHit(this_, msg);

		if (Config::aimbot) {
			if (target.found) {

				std::cout << target.hitbox->GetDamageMultiplier() << std::endl;

				auto origin = msg->ShooterPosition;
				auto delta_angle = origin.DeltaAngle(target.pos);

				msg->ShooterCameraRotation = delta_angle.x;
				msg->ShooterCharacterRotation = delta_angle.y;

				return true;
			}

			if (Config::aimbot_autoshoot) {
				return false;
			}
		}

		return res;
	}

	void OnGUI() {
		camera = Camera::Current();
		if (!camera) return;

		FindTarget();
	}

	void Initialize() {
		EventManager::Add("Update", Aimbot::OnGUI);

		// Method("Assembly-CSharp", "", "PlayerMovementSync", "SendPosition", 2)->Hook<sendpos_t>(sendpos_hk, &sendpos);
		Method::Resolve("Assembly-CSharp", "InventorySystem.Items.Firearms.Modules", "StandardHitregBase", "ClientCalculateHit", 1)->Hook<StandardHitregBase_ClientCalculateHit_t>(StandardHitregBase_ClientCalculateHit_hk, &StandardHitregBase_ClientCalculateHit);
	}
}