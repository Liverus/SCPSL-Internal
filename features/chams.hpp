namespace Chams {
	Memory::Hook* refresh_ply_model;
	Memory::Hook* update;

	Color rainbow_color = Color(1, 0, 0);

	Shader* shader;

	void ApplyChams(ReferenceHub* hub) {

		if (!shader) {
			shader = Shader::Find("GUI/Text Shader");
		}

		auto class_manager = hub->GetValue<ClassManager*>("characterClassManager");
		auto model = class_manager->GetValue<GameObject*>("MyModel");

		if (!model) return;

		auto renderer_class = Class("UnityEngine.CoreModule", "UnityEngine", "Renderer");

		auto renderer_array = model->GetComponents<Renderer>(renderer_class);
		auto renderer_count = renderer_array->MaxLength();

		for (size_t i = 0; i < renderer_count; i++)
		{
			auto renderer = renderer_array->GetValue(i);

			if (!renderer) continue;

			auto material_array = renderer->GetMaterials();
			auto material_count = material_array->MaxLength();

			for (size_t j = 0; j < material_count; j++)
			{
				auto material = material_array->GetValue(j);
			
				if (!material) continue;

				//auto shader_color = Color(1, 0, 0, 0.6);
				auto shader_color = hub->GetRoleColor();
				//auto shader_color = rainbow_color;

				shader_color.a = 0.4f;

				material->SetShader(shader);
				material->SetColor(shader_color);
			}
		}
	}

	void HideChams(ReferenceHub* hub) {

		auto default_shader = Shader::Find("Standard");

		auto class_manager = hub->GetValue<ClassManager*>("characterClassManager");
		auto model = class_manager->GetValue<GameObject*>("MyModel");

		if (!model) return;

		auto renderer_class = Class("UnityEngine.CoreModule", "UnityEngine", "Renderer");

		auto renderer_array = model->GetComponents<Renderer>(renderer_class);
		auto renderer_count = renderer_array->MaxLength();

		for (size_t i = 0; i < renderer_count; i++)
		{
			auto renderer = renderer_array->GetValue(i);

			if (!renderer) continue;

			auto material_array = renderer->GetMaterials();
			auto material_count = material_array->MaxLength();

			for (size_t j = 0; j < material_count; j++)
			{
				auto material = material_array->GetValue(j);

				if (!material) continue;

				material->SetShader(default_shader);
				material->SetColor(Color(1, 1, 1));
			}
		}
	} 

	typedef void(*CharacterClassManager_RefreshPlyModel_t)(ClassManager* this_, OBJECT* class_id);
	CharacterClassManager_RefreshPlyModel_t CharacterClassManager_RefreshPlyModel;

	void CharacterClassManager_RefreshPlyModel_hk(ClassManager* this_, OBJECT* class_id) {

		CharacterClassManager_RefreshPlyModel(this_, class_id);

		auto hub = this_->GetValue<ReferenceHub*>("_hub");
		ApplyChams(hub);
	}

	typedef void(*CharacterClassManager_Update_t)(ClassManager* this_);
	CharacterClassManager_Update_t CharacterClassManager_Update;

	void CharacterClassManager_Update_hk(ClassManager* this_) {

		CharacterClassManager_Update(this_);

		// rainbow_color = Color::Rainbow();
		// auto hub = this_->GetValue<ReferenceHub*>("_hub");
		// ApplyChams(hub);

		int width = Screen::Width() / 2;
		int height = Screen::Height() / 2;

		GUI::Label(Rect(10, 30, 500, 30), "Damithe");
	}

	typedef void(*Camera_Render_t)(Camera* this_);
	Camera_Render_t Camera_Render;

	void Camera_Render_hk(Camera* this_) {
		Camera_Render(this_);


	}

	void Initialize() {
		refresh_ply_model = Method("Assembly-CSharp", "", "CharacterClassManager", "RefreshPlyModel", 1)->Hook<CharacterClassManager_RefreshPlyModel_t>(CharacterClassManager_RefreshPlyModel_hk, &CharacterClassManager_RefreshPlyModel);
		//update = Method("Assembly-CSharp", "", "CharacterClassManager", "Update", 0)->Hook<CharacterClassManager_Update_t>(CharacterClassManager_Update_hk, &CharacterClassManager_Update);
		//auto render = Method("UnityEngine.CoreModule", "UnityEngine", "Camera", "Render", 0)->Hook<CharacterClassManager_Update_t>(CharacterClassManager_Update_hk, &CharacterClassManager_Update);
	}

	void Enable() {
		refresh_ply_model->Load();
	}

	void Disable() {
		refresh_ply_model->Unload();
	}
}