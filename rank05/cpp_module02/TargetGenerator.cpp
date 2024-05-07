#include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator()
{
}

TargetGenerator::~TargetGenerator()
{
}

void TargetGenerator::learnTargetType(ATarget *target)
{
    if (target && targetBook.find(target->getType()) == targetBook.end())
    {
        targetBook[target->getType()] = target->clone();
    }
}

void TargetGenerator::forgetTargetType(const std::string &targetName)
{
    if (targetBook.find(targetName) != targetBook.end())
    {
        delete (targetBook[targetName]);
        targetBook.erase(targetName);
    }
}

ATarget *TargetGenerator::createTarget(const std::string &targetName)
{
    ATarget *tmp = NULL;
    if (targetBook.find(targetName) != targetBook.end())
        tmp = targetBook[targetName];
    return tmp;
}