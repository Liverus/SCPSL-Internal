
#include <map>
#include <vector>

namespace EventManager {

	typedef void(*event_callback_t)(void* this_);

	extern std::map<const char*, std::vector<event_callback_t>> events;

	void Add(const char* name, void* callback);
	void Call(const char* name, void* arg);
}