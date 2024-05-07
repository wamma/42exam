#include "SpellBook.hpp"

SpellBook::SpellBook()
{
}

SpellBook::~SpellBook()
{
}

void SpellBook::learnSpell(ASpell *spell)
{
    if (spell && spellBook.find(spell->getName()) == spellBook.end())
    {
        spellBook[spell->getName()] = spell->clone();
    }
}

void SpellBook::forgetSpell(const std::string &spellName)
{
    if (spellBook.find(spellName) != spellBook.end())
    {
        delete (spellBook[spellName]);
        spellBook.erase(spellName);
    }
}

ASpell *SpellBook::createSpell(const std::string &spellName)
{
    ASpell *tmp = NULL;
    if (spellBook.find(spellName) != spellBook.end())
        tmp = spellBook[spellName];
    return tmp;
}