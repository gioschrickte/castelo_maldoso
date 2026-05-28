#include "Entidade.hpp"

Entidades::Entidade::Entidade()
	: Jogo::Ente()
{

}

Entidades::Entidade::Entidade(const sf::Vector2f pos, const sf::Vector2f tam, const IDs::IDs id)
	: Jogo::Ente(pos, tam, id)
{
}

Entidades::Entidade::~Entidade()
{

}

const IDs::IDs Entidades::Entidade::getId() const
{
	return id;
}

const sf::Vector2f Entidades::Entidade::getPosicao() const
{
	return corpo.getPosition();
}

const sf::Vector2f Entidades::Entidade::getTamanho() const
{
	return corpo.getSize();
}

const sf::RectangleShape Entidades::Entidade::getCorpo() const
{
	return corpo;
}

void Entidades::Entidade::mover(sf::Vector2f ds)
{
	corpo.move(ds);
}

