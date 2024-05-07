#include "ASpell.hpp"

ASpell::ASpell()
{
}

ASpell::~ASpell()
{
}

ASpell::ASpell(const std::string &name, const std::string &effects) : name(name), effects(effects)
{
}

ASpell::ASpell(const ASpell &other)
{
    this->name = other.getName();
    this->effects = other.getEffects();
}

ASpell &ASpell::operator=(const ASpell &other)
{
    this->name = other.getName();
    this->effects = other.getEffects();
    return *this;
}

const std::string &ASpell::getName() const
{
    return this->name;
}

const std::string &ASpell::getEffects() const
{
    return this->effects;
}

void ASpell::launch(const ATarget &target) const
{
    target.getHitBySpell(*this);
}
