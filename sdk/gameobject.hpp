class GameObject : public OBJECT {
public:
	template <class T>
	T* GetComponent(CLASS* component_class) {
		auto component_obj = component_class->Type()->Object();

		typedef T* (*GameObject_GetComponent_t)(GameObject* this_, OBJECT* component_obj);
		return Function<GameObject_GetComponent_t>("UnityEngine.CoreModule", "UnityEngine", "GameObject", "GetComponent", 1)(this, component_obj);
	}

	template <class T>
	T* GetComponentInChildren(CLASS* component_class, bool inactives = false) {
		auto component_obj = component_class->Type()->Object();

		typedef T* (*GameObject_GetComponentInChildren_t)(GameObject* this_, OBJECT* component_obj, bool inactives);
		return Function<GameObject_GetComponentInChildren_t>("UnityEngine.CoreModule", "UnityEngine", "GameObject", "GetComponentInChildren", 2)(this, component_obj, inactives);
	}

	template <class T>
	ARRAY<T*>* GetComponents(CLASS* component_class, bool inactives = false) {
		auto component_obj = component_class->Type()->Object();

		typedef ARRAY<T*>* (*GameObject_GetComponentsInternal_t)(GameObject* this_, OBJECT* component_obj, bool use_type, bool recursive, bool inactives, bool reverse, void* list);
		return Function<GameObject_GetComponentsInternal_t>("UnityEngine.CoreModule", "UnityEngine", "GameObject", "GetComponentsInternal", 6)(this, component_obj, false, true, inactives, false, nullptr);
	}

	template <class T>
	T* GetComponentInParent(CLASS* component_class) {
		auto component_obj = component_class->Type()->Object();

		typedef T* (*GameObject_GetComponentInParent_t)(GameObject* this_, OBJECT* component_obj);
		return Function<GameObject_GetComponentInParent_t>("UnityEngine.CoreModule", "UnityEngine", "GameObject", "GetComponentInParent", 1)(this, component_obj);
	}

	template <class T>
	T* AddComponent(CLASS* component_class) {
		auto component_obj = component_class->Type()->Object();
		
		typedef T* (*GameObject_AddComponent_t)(GameObject* this_, OBJECT* component_obj);
		return Function<GameObject_AddComponent_t>("UnityEngine.CoreModule", "UnityEngine", "GameObject", "AddComponent", 1)(this, component_obj);
	}

	Transform* GetTransform() {
		typedef Transform* (*GameObject_get_transform_t)(GameObject* this_);
		return Function<GameObject_get_transform_t>("UnityEngine.CoreModule", "UnityEngine", "GameObject", "get_transform", 0)(this);
	}

	Vector3 GetPosition() {
		return this->GetTransform()->GetPosition();
	}

	void SetActive(bool state) {
		typedef void(*GameObject_SetActive_t)(GameObject* this_, bool state);
		return Function<GameObject_SetActive_t>("UnityEngine.CoreModule", "UnityEngine", "GameObject", "SetActive", 1)(this, state);
	}
};