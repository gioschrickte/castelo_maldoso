#include "Entidade.hpp"

Entidade::Entidade::Entidade()
	: corpo(), id(IDs::IDs::jogador)
{

}

Entidade::Entidade::Entidade(const sf::Vector2f pos, const sf::Vector2f tam, IDs::IDs id)
	: corpo(sf::RectangleShape(tam)), id(id)
{
	corpo.setPosition(pos);
}

Entidade::Entidade::~Entidade()
{

}

const sf::RectangleShape Entidade::Entidade::getCorpo() const
{
	return corpo;
}

void Entidade::Entidade::mover(sf::Vector2f ds)
{
	corpo.move(ds);
}

