
class ReferenceHub : public  Object {
public:

	static Dictionary<GameObject*, ReferenceHub*>* GetAllHubs() {
		typedef Dictionary<GameObject*, ReferenceHub*>* (*ReferenceHub_GetAllHubs_t)();
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

	Object* GetRole() {
		auto class_manager = GetClassManager();

		return class_manager->GetRole();
	}

	Color GetRoleColor() {
		auto role = GetRole();

		return role->GetValue<Color>("classColor");
	}

	int PlayerID() {
		typedef int (*ReferenceHub_get_playerId_t)(ReferenceHub* this_);
		return Function<ReferenceHub_get_playerId_t>("Assembly-CSharp", "", "ReferenceHub", "get_playerId", 0)(this);
	}

	PlayerMovementSync* GetMovementSync() {
		return this->GetValue<PlayerMovementSync*>("playerMovementSync");
	}

	bool IsAlive() {
		return this->GetClassManager()->IsAlive();
	}

	bool IsSpawnProtected() {
		return this->GetClassManager()->IsSpawnProtected();
	}

	bool IsLocalPlayer() {
		typedef bool (*ReferenceHub_get_isLocalPlayer_t)(ReferenceHub* this_);
		return Function<ReferenceHub_get_isLocalPlayer_t>("Assembly-CSharp", "", "ReferenceHub", "get_isLocalPlayer", 0)(this);
	}

	bool Ready() {
		typedef bool (*ReferenceHub_get_Ready_t)(ReferenceHub* this_);
		return Function<ReferenceHub_get_Ready_t>("Assembly-CSharp", "", "ReferenceHub", "get_Ready", 0)(this);
	}
};