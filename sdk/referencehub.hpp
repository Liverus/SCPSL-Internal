
class ReferenceHub : public  OBJECT {
public:

	static Dictionary* GetAllHubs() {
		typedef Dictionary* (*ReferenceHub_GetAllHubs_t)();
		return Function<ReferenceHub_GetAllHubs_t>("Assembly-CSharp", "", "ReferenceHub", "GetAllHubs", 0)();
	}

	static ReferenceHub* GetHub(int id) {
		typedef ReferenceHub* (*ReferenceHub_GetHub_t)(int id);
		return Function<ReferenceHub_GetHub_t>("Assembly-CSharp", "", "ReferenceHub", "GetHub", 1)(id);
	}

	static ReferenceHub* GetLocalHub() {
		typedef ReferenceHub* (*ReferenceHub_GetHub_t)();
		return Function<ReferenceHub_GetHub_t>("Assembly-CSharp", "", "ReferenceHub", "get_LocalHub", 0)();
		
	}

	ClassManager* GetClassManager() {
		return this->GetValue<ClassManager*>("characterClassManager");
	}

	OBJECT* GetRole() {
		auto class_manager = GetClassManager();

		return class_manager->GetRole();
	}

	//Role GetRoleID() {
	//	auto role = GetRole();

	//	return role->GetValue<Role>("roleId");
	//}

	Color GetRoleColor() {
		auto role = GetRole();

		return role->GetValue<Color>("classColor");
	}

	//Team GetTeam() {
	//	auto class_manager = GetClassManager();

	//	return class_manager->GetTeam();
	//}

	int PlayerID() {
		typedef int (*ReferenceHub_get_playerId_t)(ReferenceHub* this_);
		return Function<ReferenceHub_get_playerId_t>("Assembly-CSharp", "", "ReferenceHub", "get_playerId", 0)(this);
	}

	bool IsLocalPlayer() {
		typedef bool (*ReferenceHub_get_isLocalPlayer_t)(ReferenceHub* this_);
		return Function<ReferenceHub_get_isLocalPlayer_t>("Assembly-CSharp", "", "ReferenceHub", "get_isLocalPlayer", 0)(this);
	}

	bool Ready() {
		typedef bool (*ReferenceHub_get_Ready_t)(ReferenceHub* this_);
		return Function<ReferenceHub_get_Ready_t>("Assembly-CSharp", "", "ReferenceHub", "get_Ready", 0)(this);
	}

	static void Loop(bool(*callback)(ReferenceHub*, GameObject*), bool include_localplayer = false, bool include_dead = false) {
		auto hubs_dict = GetAllHubs();
		
		auto hubs_count = hubs_dict->Count();
		auto hubs_entries = hubs_dict->Entries();

		for (size_t i = 0; i < hubs_count; i++)
		{
			auto entry = hubs_entries->GetValue(i);
			auto hub = entry->GetValue<ReferenceHub*>("value");
			auto obj = entry->GetValue<GameObject*>("key");

			if (hub->Ready()) {
				if (hub->IsLocalPlayer() && !include_localplayer) continue;
				//if (!hub->IsAlive() && !include_dead) continue;

				callback(hub, obj);
			}
		}
	}
};