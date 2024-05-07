#pragma once

#include "ATarget.hpp"
#include <iostream>
#include <map>

class ATarget;

class TargetGenerator
{
  private:
    std::map<std::string, ATarget *> targetBook;
    TargetGenerator &operator=(const TargetGenerator &other);
    TargetGenerator(const TargetGenerator &other);

  public:
    TargetGenerator();
    ~TargetGenerator();
    void learnTargetType(ATarget *target);
    void forgetTargetType(const std::string &targetName);
    ATarget *createTarget(const std::string &targetName);
};