#pragma once

#include "ATarget.hpp"
#include <iostream>

class ATarget;

class ASpell
{
  private:
    std::string name;
    std::string effects;

  public:
    ASpell();
    virtual ~ASpell();
    ASpell(const ASpell &other);
    ASpell &operator=(const ASpell &other);
    ASpell(const std::string &name, const std::string &effects);
    const std::string &getName() const;
    const std::string &getEffects() const;
    virtual ASpell *clone() const = 0;
    void launch(const ATarget &target) const;
};