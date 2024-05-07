#pragma once

#include "ASpell.hpp"
#include <iostream>
#include <map>
#include <string>

class ASpell;

class Warlock
{
  private:
    std::string name;
    std::string title;
    std::map<std::string, ASpell *> spellBook;

    Warlock();
    Warlock &operator=(const Warlock &other);
    Warlock(const Warlock &other);

  public:
    ~Warlock();
    Warlock(const std::string &name, const std::string &title);

    const std::string &getName() const;
    const std::string &getTitle() const;
    void setTitle(const std::string &title);
    void introduce() const;

    void learnSpell(ASpell *spell);
    void forgetSpell(const std::string &spellName);
    void launchSpell(const std::string &spellName, const ATarget &target);
};