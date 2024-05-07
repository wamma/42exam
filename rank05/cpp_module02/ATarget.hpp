#pragma once

#include "ASpell.hpp"
#include <iostream>

class ASpell;

class ATarget
{
  private:
    std::string type;

  public:
    ATarget();
    virtual ~ATarget();
    ATarget(const ATarget &other);
    ATarget(const std::string &type);
    ATarget &operator=(const ATarget &other);
    const std::string &getType() const;
    virtual ATarget *clone() const = 0;
    void getHitBySpell(const ASpell &spell) const;
};