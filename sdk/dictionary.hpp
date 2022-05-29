template <class TKey, class TValue>
class Dictionary : public Object {
public:
	template <class TKey, class TValue>
	struct Entry {
		int hashCode;
		int next;
		TKey key;
		TValue value;
	};

	int Count() {
		return this->GetValue<int>("count");
	}

	Array<Entry<TKey, TValue>>* GetEntries() {
		return this->GetValue<Array<Entry<TKey, TValue>>*>("entries");
	}

	bool TryGetValue(TKey key, TValue* value) {
		typedef bool (*Dictionary_TryGetValue_t)(Dictionary* this_, TKey key, TValue* value);
		return Function<Dictionary_TryGetValue_t>("mscorlib", "System.Collections.Generic", "Dictionary`2", "TryGetValue", 2)(this, key, value);
	}
};