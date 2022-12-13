#include "NameGenerator.h"

std::string fgvm::NameGenerator::get(std::string name)
{
    hit_count[name]++;
    if (exist(name))
        name += std::to_string(hit_count[name] - 1);
    variables.insert(name);
    return name;
}

std::string fgvm::NameGenerator::latest(std::string name)
{
    if (hit_count[name] > 1) {
        std::string latest_ver = name + std::to_string(hit_count[name] - 1);
        FGError::ASSERT(variables.find(latest_ver) != variables.end());
        return latest_ver;
    } else if (hit_count[name] <= 1) {
        // if (hit_count[name] == 0) 
        //      throw FGError::notAllowed("Symbol does not exist", name + " is not assigned yet");
        return name;
    }
    throw FGError::notExpected("Unexpected behavior : control path taken not expected");
}

bool fgvm::NameGenerator::exist(std::string name)
{
    return variables.find(name) != variables.end();
}

std::unordered_set<std::string> fgvm::NameGenerator::getNonAvailaibleNames()
{
    return variables;
}
