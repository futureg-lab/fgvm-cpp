#pragma once

#include <unordered_set>
#include <unordered_map>
#include <string>

namespace fgvm {
	class NameGenerator {
	private:
		std::unordered_set<std::string> variables;
		std::unordered_map<std::string, int> hit_count;
	public:
		// Returns a unique name based on name
		std::string get(std::string name);

		// Returns true if the name has been emitted
		bool exist(std::string name);

		// Returns all names that has been emitted
		std::unordered_set<std::string> getNonAvailaibleNames();
	};
}