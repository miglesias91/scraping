#include <scraping/include/IAlmacenable.h>

// utiles
#include  <utiles/include/GestorIDs.h>

using namespace scraping;

IAlmacenable::IAlmacenable(std::string grupo) : id(nullptr), grupo(grupo)
{
}

IAlmacenable::~IAlmacenable()
{
    delete this->id;
    this->id = nullptr;
}

// GETTERS

herramientas::utiles::ID* IAlmacenable::getId()
{
    return this->id;
}

std::string IAlmacenable::getGrupo()
{
    return this->grupo;
}

// SETTERS

void IAlmacenable::setId(herramientas::utiles::ID * id)
{
    if (nullptr != this->id)
    {
        delete this->id;
    }

    this->id = id;
}

void IAlmacenable::setGrupo(std::string grupo)
{
    this->grupo = grupo;
}

// METODOS

bool IAlmacenable::comparador(IAlmacenable * a, IAlmacenable * b)
{
    return a->getId()->numero() < b->getId()->numero();
}