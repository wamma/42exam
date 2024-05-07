#pragma once

#include "ASpell.hpp"
#include <iostream>

class ASpell;

class Warlock
{
  private:
    std::string name;
    std::string title;

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
};