#pragma once

#include "ASpell.hpp"
#include <iostream>
#include <map>

class ASpell;

class SpellBook
{
  private:
    std::map<std::string, ASpell *> spellBook;
    SpellBook &operator=(const SpellBook &other);
    SpellBook(const SpellBook &other);

  public:
    SpellBook();
    ~SpellBook();
    void learnSpell(ASpell *spell);
    void forgetSpell(const std::string &spellName);
    ASpell *createSpell(const std::string &spellName);
};