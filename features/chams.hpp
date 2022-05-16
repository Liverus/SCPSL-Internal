namespace Chams {
	Memory::Hook* refresh_ply_model;
	Memory::Hook* update;

	Color rainbow_color = Color(1, 0, 0);

	Shader* chams_shader;
	Shader* standard_shader;

	void ApplyChams(GameObject* model, Shader* shader, Color color) {

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

				material->SetShader(shader);
				material->SetColor(color);
			}
		}
	}

	Color GetColor(ReferenceHub* hub) {

		Color color = Color(1, 1, 1, 1);

		if (Config::chams) {
			if (Aimbot::target.hub != hub) {
				if (Config::chams_rgb) {
					color = rainbow_color;
				}
				else {
					color = hub->GetRoleColor();
				}
			}

			if (hub->IsSpawnProtected()) {
				color.a = 0.1f;
			} else {
				color.a = Config::chams_alpha;
			}
		}

		return color;
	}

	Shader* GetShader() {
		if (Config::chams) {
			return chams_shader;
		} else {
			return standard_shader;
		}
	}

	void OnGUI() {

		if (!chams_shader) {
			chams_shader = Shader::Find("GUI/Text Shader");
		}

		if (!standard_shader) {
			standard_shader = Shader::Find("Standard");
		}

		if (Config::chams_rgb) {
			rainbow_color = Color::Rainbow(0.01f + Config::chams_rgb_speed * 0.1f);
		}

		auto shader = GetShader();

		auto hubs_dict = ReferenceHub::GetAllHubs();
		auto localplayer = ReferenceHub::GetLocalHub();

		auto entries = hubs_dict->GetEntries();
		auto entries_count = entries->MaxLength();

		for (size_t i = 0; i < entries_count; i++) {

			auto entry = entries->GetValue(i);

			auto game_object = entry.key;
			auto reference_hub = entry.value;

			if (game_object && reference_hub) {

				if (!Config::chams_local && reference_hub->IsLocalPlayer()) continue;
				if (!reference_hub->IsAlive()) continue;

				auto class_manager = reference_hub->GetValue<ClassManager*>("characterClassManager");
				auto model = class_manager->GetValue<GameObject*>("MyModel");

				if (!model) continue;

				auto clr = GetColor(reference_hub);

				ApplyChams(game_object, shader, clr);
			}
		}
	}
	
	void Initialize() {
		EventManager::Add("OnGUI", Chams::OnGUI);
		// refresh_ply_model = Method("Assembly-CSharp", "", "CharacterClassManager", "RefreshPlyModel", 1)->Hook<CharacterClassManager_RefreshPlyModel_t>(CharacterClassManager_RefreshPlyModel_hk, &CharacterClassManager_RefreshPlyModel);
	}

	void Enable() {
	}

	void Disable() {
	}
}