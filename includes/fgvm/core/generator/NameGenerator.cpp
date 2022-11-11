#include "NameGenerator.h"

std::string fgvm::NameGenerator::get(std::string name)
{
    hit_count[name]++;
    if (exist(name))
        name += std::to_string(hit_count[name]);
    variables.insert(name);
    return name;
}

bool fgvm::NameGenerator::exist(std::string name)
{
    return variables.find(name) != variables.end();
}

std::unordered_set<std::string> fgvm::NameGenerator::getNonAvailaibleNames()
{
    return variables;
}
