#include "ATarget.hpp"

ATarget::ATarget()
{
}

ATarget::~ATarget()
{
}

ATarget::ATarget(const std::string &type) : type(type)
{
}

ATarget::ATarget(const ATarget &other)
{
    this->type = other.getType();
}

ATarget &ATarget::operator=(const ATarget &other)
{
    this->type = other.getType();
    return *this;
}

const std::string &ATarget::getType() const
{
    return this->type;
}

void ATarget::getHitBySpell(const ASpell &spell) const
{
    std::cout << type << " has been " << spell.getEffects() << "!" << std::endl;
}