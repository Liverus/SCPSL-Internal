struct Ray {
public:
	Vector3 m_Origin;
	Vector3 m_Direction;
};

struct RaycastHit {
public:

	Transform* GetTransform() {
		typedef Transform* (*RaycastHit_get_transform_t)(RaycastHit this_);
		return Function<RaycastHit_get_transform_t>("UnityEngine.PhysicsModule", "UnityEngine", "RaycastHit", "get_transform", 0)(*this);
	}

	Vector3 GetPosition() {
		typedef Vector3(*RaycastHit_get_point_t)(RaycastHit this_);
		return Function<RaycastHit_get_point_t>("UnityEngine.PhysicsModule", "UnityEngine", "RaycastHit", "get_point", 0)(*this);
	}

	Object* GetCollider() {
		typedef Object* (*RaycastHit_get_collider_t)(RaycastHit this_);
		return Function<RaycastHit_get_collider_t>("UnityEngine.PhysicsModule", "UnityEngine", "RaycastHit", "get_collider", 0)(*this);
	}

	Object* GetRigidbody() {
		typedef Object* (*RaycastHit_get_rigidbody_t)(RaycastHit this_);
		return Function<RaycastHit_get_rigidbody_t>("UnityEngine.PhysicsModule", "UnityEngine", "RaycastHit", "get_rigidbody", 0)(*this);
	}

	float GetDistance() {
		typedef float (*RaycastHit_get_point_t)(RaycastHit this_);
		return Function<RaycastHit_get_point_t>("UnityEngine.PhysicsModule", "UnityEngine", "RaycastHit", "get_distance", 0)(*this);
	}

	Vector3 m_Point;
	Vector3 m_Normal;
	unsigned int m_FaceID;
	float m_Distance;
	Vector2 m_UV;
	int m_Collider;
};

class Physics : public Object {
public:
	static bool Raycast(Vector3 origin, Vector3 direction, RaycastHit* hit_info, float max_distance, int mask, int trigger=0) {
		typedef bool (*Physics_Raycast_t)(Vector3 origin, Vector3 direction, RaycastHit* hit_info, float max_distance, int mask, int trigger);
		return Function<Physics_Raycast_t>("UnityEngine.PhysicsModule", "UnityEngine", "Physics", "Raycast", 6)(origin, direction, hit_info, max_distance, mask, trigger);
	}

	static bool Linecast(Vector3 start, Vector3 end, RaycastHit* hit_info, int mask, int trigger=0) {
		typedef bool (*Physics_Linecast_t)(Vector3 start, Vector3 end, RaycastHit* hit_info, int mask, int trigger);
		return Function<Physics_Linecast_t>("UnityEngine.PhysicsModule", "UnityEngine", "Physics", "Linecast", 5)(start, end, hit_info, mask, trigger);
	}
};

class Debug : public Object {
public:
	static void DrawRay(Vector3 start, Vector3 dir, Color color, float duration) {
		typedef void (*Debug_DrawRay_t)(Vector3 start, Vector3 dir, Color color, float duration);
		return Function<Debug_DrawRay_t>("UnityEngine.CoreModule", "UnityEngine", "Debug", "DrawRay", 4)(start, dir, color, duration);
	}

	static void DrawLine(Vector3 start, Vector3 dir, Color color, float duration) {
		typedef void (*Debug_DrawLine_t)(Vector3 start, Vector3 dir, Color color, float duration);
		return Function<Debug_DrawLine_t>("UnityEngine.CoreModule", "UnityEngine", "Debug", "DrawLine", 4)(start, dir, color, duration);
	}
};