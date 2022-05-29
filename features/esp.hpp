namespace Esp {

	Camera* camera;

	void OnGUI() {

		if (!Config::esp) return;

		camera = Camera::Main();

		auto height = Screen::Height();

		GUI::Label(Rect(5, 30, 200, 15), "Damithe Internal");

		auto hubs_dict = ReferenceHub::GetAllHubs();

		if (!hubs_dict) return;

		auto style = GUIStyle::GetLabelStyle();

		auto entries = hubs_dict->GetEntries();
		auto entries_count = entries->GetMaxLength();

		int margin = 0;

		for (size_t i = 0; i < entries_count; i++) {

			auto entry = entries->GetValue(i);

			auto game_object = entry.key;
			auto reference_hub = entry.value;

			if (game_object && reference_hub) {
				if (!reference_hub->IsReady()) continue;
				if (reference_hub->IsServer()) continue;

				auto player_name = reference_hub->GetNickname();
				auto role_name = reference_hub->GetRoleName();
				auto role_color = reference_hub->GetRoleColor();

				// Player List

				if (Config::esp_player_list) {
					GUI::SetColor(role_color);
					GUI::Label(Rect(5, 60 + margin * 15, 200, 15), player_name);
					GUI::Label(Rect(220, 60 + margin * 15, 200, 15), role_name);

					margin++;
				}

				// Player ESP

				if (Config::esp_player_list) {
					if (reference_hub->IsLocalPlayer()) continue;

					auto player_pos = game_object->GetPosition() + Vector3(0, 1, 0);
					auto screen_pos = camera->ToScreen(player_pos);

					if (screen_pos.z < 0) continue;

					style->SetAlignment(TextAnchor::MiddleCenter);

					if (Config::aimbot && Aimbot::target.hub) {
						auto target = Aimbot::target;

						auto target_screen_pos = camera->ToScreen(target.pos);

						if (target.hub == reference_hub) {
							GUI::SetColor(Color(1, 1, 1));
							GUI::Label(Rect(screen_pos.x - 100, height - screen_pos.y - 7.5, 200, 15), "Aimbot");
							GUI::Label(Rect(target_screen_pos.x - 100, height - target_screen_pos.y - 7.5, 200, 15), "O");
							GUI::SetColor(role_color);
						}
					}

					GUI::Label(Rect(screen_pos.x - 100, height - screen_pos.y - 7.5, 200, 15), player_name);
					GUI::Label(Rect(screen_pos.x - 100, height - screen_pos.y + 15 - 7.5, 200, 15), role_name);
				}

				// Hitbox ESP

				//auto hitbox_array = game_object->GetComponents<HitboxIdentity>(Class::Resolve("Assembly-CSharp", "", "HitboxIdentity"));
				//auto hitbox_count = hitbox_array->GetMaxLength();

				//for (size_t j = 0; j < hitbox_count; j++)
				//{
				//	auto hitbox = hitbox_array->GetValue(j);
				//	auto hitbox_multiplier = hitbox->GetDamageMultiplier();

				//	auto hitbox_pos = hitbox->GetMassCenter();

				//	auto hitbox_screen_pos = camera->ToScreen(hitbox_pos);

				//	if (hitbox_screen_pos.z < 0) continue;

				//	GUI::SetColor(Color(1,1,1));

				//	char buf[10];
				//	sprintf_s(buf, "%i", hitbox_multiplier);

				//	GUI::Label(Rect(hitbox_screen_pos.x-100, height-hitbox_screen_pos.y-7.5, 200, 15), buf);
				//}

				// Reset Alignment

				style->SetAlignment(TextAnchor::MiddleLeft);
			}
		}

		return;

		auto pickup_list = Field::Resolve("Assembly-CSharp", "InventorySystem.Items.Pickups", "PhysicsPredictionPickup", "AllPickups")->GetStaticValue<List<Object*>*>();
		auto item_list = Field::Resolve("Assembly-CSharp", "InventorySystem", "InventoryItemLoader", "_loadedItems")->GetStaticValue<Dictionary<int, Object*>*>();

		auto values = pickup_list->GetValues();
		auto values_count = pickup_list->Count();

		for (size_t i = 0; i < values_count; i++) {
			auto item = values->GetValue(i);
			auto item_info = item->GetValue<Object*>("Info");

			auto item_pos = item_info->GetValue<Vector3>("Position");
			auto item_id = item_info->GetValue<int>("ItemId");

			Object* itembase;

			auto texture = itembase->GetValue<Object*>("Icon");

			auto item_screen_pos = camera->ToScreen(item_pos);

			GUI::DrawTexture(Rect(item_screen_pos.x - 100, height - item_screen_pos.y - 7.5, 200, 15), texture);
		}
	}

	void Start() {
		camera = nullptr;
	}

	void Initialize() {
		//EventManager::Add("Start", Esp::Start);
		EventManager::Add("OnGUI", Esp::OnGUI);
	}

	void Enable() {}
	void Disable() {}
}