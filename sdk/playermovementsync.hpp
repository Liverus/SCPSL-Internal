struct RotationVector {
public:
	RotationVector(Vector2 rot) {
		x = rot.x;
		y = rot.y;
	}

	RotationVector(unsigned short x_, unsigned short y_) {
		x = x_;
		y = y_;
	}

	unsigned short x;
	unsigned short y;
};

class PlayerMovementSync : public Object {
public:

	void SetRotation(Vector2 rot) {
		typedef void (*PlayerMovementSync_set_NetworkRotationSync_t)(PlayerMovementSync* this_, Vector2 rot);
		return Function<PlayerMovementSync_set_NetworkRotationSync_t>("Assembly-CSharp", "", "PlayerMovementSync", "set_Rotations", 1)(this, rot);
	}
	void SetNetworkRotation(Vector2 rot) {
		auto real_dir = RotationVector(rot);
		typedef void (*PlayerMovementSync_set_NetworkRotationSync_t)(PlayerMovementSync* this_, RotationVector real_dir);
		return Function<PlayerMovementSync_set_NetworkRotationSync_t>("Assembly-CSharp", "", "PlayerMovementSync", "set_Rotations", 1)(this, real_dir);
	}
};