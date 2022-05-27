class GameObject : public Object {
public:

	static void Create(GameObject* object, const char* object_name) {
		auto il2cpp_name = String::NewLen(object_name);

		typedef void (*GameObject_Internal_CreateGameObject_t)(GameObject* object, String* object_name);
		return Function<GameObject_Internal_CreateGameObject_t>("UnityEngine.CoreModule", "UnityEngine", "GameObject", "Internal_CreateGameObject", 2)(object, il2cpp_name);
	}

	void DontDestroyOnLoad() {
		typedef void (*GameObject_DontDestroyOnLoad_t)(GameObject* obj);
		return Function<GameObject_DontDestroyOnLoad_t>("UnityEngine.CoreModule", "UnityEngine", "GameObject", "DontDestroyOnLoad", 1)(this);
	}

	template <class T>
	Array<T*>* GetComponents(Class* component_class, bool inactives = false) {
		auto component_obj = component_class->GetObject();

		typedef Array<T*>* (*GameObject_GetComponentsInternal_t)(GameObject* this_, Object* component_obj, bool use_type, bool recursive, bool inactives, bool reverse, void* list);
		return Function<GameObject_GetComponentsInternal_t>("UnityEngine.CoreModule", "UnityEngine", "GameObject", "GetComponentsInternal", 6)(this, component_obj, false, true, inactives, false, nullptr);
	}

	template <class T>
	T* AddComponent(Class* component_class) {
		auto component_obj = component_class->GetObject();

		std::cout << component_obj << std::endl;
		
		typedef T* (*GameObject_AddComponent_t)(GameObject* this_, Object* component_obj);
		return Function<GameObject_AddComponent_t>("UnityEngine.CoreModule", "UnityEngine", "GameObject", "Internal_AddComponentWithType", 1)(this, component_obj);
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