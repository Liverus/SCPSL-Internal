
#include <vector>
#include <map>

template <class T>
struct HookInfo {
	const char* name;
	vector<T> callbacks;
};

namespace HookManager {
	void Add();
	void Call();
}