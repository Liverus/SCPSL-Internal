
#include "event_manager.h"

namespace EventManager {
	std::map<const char*, std::vector<event_callback_t>> events;
}

void EventManager::Add(const char* name, void* callback) {
	events[name].push_back((event_callback_t)callback);
}

void EventManager::Call(const char* name) {
	auto callbacks = events[name];

	for (auto& callback : callbacks) {
		callback();
	}
}