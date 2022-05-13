class HitboxIdentity : public OBJECT {
public:
	Vector3 GetMassCenter() {
		typedef Vector3 (*HitboxIdentity_get_CenterOfMass_t)(HitboxIdentity* this_);
		return Function<HitboxIdentity_get_CenterOfMass_t>("Assembly-CSharp", "", "HitboxIdentity", "get_CenterOfMass", 0)(this);
	}

	int GetDamageMultiplier() {
		return this->GetValue<int>("_dmgMultiplier");
	}

	ReferenceHub* GetOwner() {
		typedef ReferenceHub* (*HitboxIdentity_get_TargetHub_t)(HitboxIdentity* this_);
		return Function<HitboxIdentity_get_TargetHub_t>("Assembly-CSharp", "", "HitboxIdentity", "get_TargetHub", 0)(this);
	}
};