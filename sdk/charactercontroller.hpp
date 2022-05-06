
class CharacterController : public OBJECT {
public:

	void SetSlopeLimit(float limit) {
		typedef void(*CharacterController_set_slopeLimit_t)(CharacterController* this_, float limit);
		return Function<CharacterController_set_slopeLimit_t>("UnityEngine.PhysicsModule.dll", "UnityEngine", "CharacterController", "set_slopeLimit", 1)(this, limit);
	}

	void SetSkinWidth(float width) {
		typedef void(*CharacterController_set_skinWidth_t)(CharacterController* this_, float width);
		return Function<CharacterController_set_skinWidth_t>("UnityEngine.PhysicsModule.dll", "UnityEngine", "CharacterController", "set_skinWidth", 1)(this, width);
	}

	void SetCenter(Vector3 center) {
		typedef void(*CharacterController_set_center_t)(CharacterController* this_, Vector3 center);
		return Function<CharacterController_set_center_t>("UnityEngine.PhysicsModule.dll", "UnityEngine", "CharacterController", "set_center", 1)(this, center);
	}

	void SetHeight(float height) {
		typedef void(*CharacterController_set_height_t)(CharacterController* this_, float height);
		return Function<CharacterController_set_height_t>("UnityEngine.PhysicsModule.dll", "UnityEngine", "CharacterController", "set_height", 1)(this, height);
	}

	void SetStepOffset(float offset) {
		typedef void(*CharacterController_et_stepOffset_t)(CharacterController* this_, float offset);
		return Function<CharacterController_et_stepOffset_t>("UnityEngine.PhysicsModule.dll", "UnityEngine", "CharacterController", "set_stepOffset", 1)(this, offset);
	}
};