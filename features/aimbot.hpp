

namespace Aimbot {

	struct AimbotTarget {
		float dist;
		ReferenceHub* hub;
		Vector3 pos;
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

	AimbotTarget target;
	Camera* camera;
	Class* hitboxreg_class;

	Memory::Hook* calculate_hit;

	float CalculateDistance(Vector3 pos) {
		auto screen_pos = camera->ToScreen(pos);

		auto width = Screen::Width();
		auto height = Screen::Height();

		auto screen_center = Vector2(width / 2, height / 2);
		auto screen_delta = Vector2(screen_pos.x, screen_pos.y) - screen_center;

		auto screen_dist = screen_delta.Length();

		return screen_dist;
	}

	bool IsInFOV(float dist) {
		return dist <= Config::aimbot_fov_value;
	}

	bool CanSee(Vector3 pos) {

		auto origin = camera->GetPosition();

		RaycastHit hit_info;
		auto hit = Physics::Linecast(origin, pos, &hit_info, 1208238081, 0);

		return !hit;
	}

	AimbotTarget FindHitbox(ReferenceHub* reference_hub, GameObject* game_object) {

		AimbotTarget new_target { 0, 0, Vector3(0, 0, 0) };

		if (reference_hub->GetRoleID() == RoleType::Scp049) {
			auto pos = game_object->GetPosition() + Vector3(0, 1, 0);
			auto dist = CalculateDistance(pos);

			return {
				dist,
				reference_hub,
				pos
			};
		}

		auto hitbox_array = game_object->GetComponents<HitboxIdentity>(hitboxreg_class);
		auto hitbox_count = hitbox_array->GetMaxLength();

		int actual_multiplier = 0;

		for (size_t j = 0; j < hitbox_count; j++)
		{
			auto hitbox = hitbox_array->GetValue(j);
			auto hitbox_multiplier = hitbox->GetDamageMultiplier();

			auto hitbox_pos = hitbox->GetMassCenter();
			float dist = CalculateDistance(hitbox_pos);

			if (!new_target.hub || (hitbox_multiplier >= actual_multiplier)) {

				actual_multiplier = hitbox_multiplier;

				new_target = {
					dist,
					reference_hub,
					hitbox_pos
				};
			}
		}

		return new_target;
	}

	void FindTarget() {

		target = { 0, 0, Vector3(0, 0, 0) };

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

				if (!reference_hub->IsReady()) continue;
				if (reference_hub->IsServer()) continue;
				if (reference_hub->IsLocalPlayer()) continue;
				if (!reference_hub->IsAlive()) continue;
				if (reference_hub->IsSpawnProtected()) continue;
				if (!Config::aimbot_friendlyfire && HitboxIdentity::IsFriendlyFire(localplayer, reference_hub)) continue;

				auto new_target = FindHitbox(reference_hub, game_object);

				if (Config::aimbot_fov && !IsInFOV(new_target.dist)) continue;
				if (Config::aimbot_visible && !CanSee(new_target.pos)) continue;

				if (!target.hub || new_target.dist < target.dist) {
					target = new_target;
				}
			}
		}
	}

	typedef bool (*StandardHitregBase_ClientCalculateHit_t)(Object* this_, ShotMessage* a);
	StandardHitregBase_ClientCalculateHit_t StandardHitregBase_ClientCalculateHit;

	bool StandardHitregBase_ClientCalculateHit_hk(Object* this_, ShotMessage* msg) {

		auto res = StandardHitregBase_ClientCalculateHit(this_, msg);

		if (Config::aimbot) {
			if (target.hub) {

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

	void Update() {
		if (!Config::aimbot) return;
		if (!camera) return;

		FindTarget();
	}

	void Start() {
		target = {false, nullptr, Vector3(0, 0, 0)};

		camera = Camera::Main();
		hitboxreg_class = Class::Resolve("Assembly-CSharp", "", "HitboxIdentity");
	}

	void Initialize() {
		EventManager::Add("Update", Aimbot::Update);
		EventManager::Add("Start", Aimbot::Start);

		calculate_hit = Method::Resolve("Assembly-CSharp", "InventorySystem.Items.Firearms.Modules", "StandardHitregBase", "ClientCalculateHit", 1)->Hook<StandardHitregBase_ClientCalculateHit_t>(StandardHitregBase_ClientCalculateHit_hk, &StandardHitregBase_ClientCalculateHit);
	}

	void Enable() {
		calculate_hit->Load();
	};

	void Disable() {
		calculate_hit->Unload();
	};
}