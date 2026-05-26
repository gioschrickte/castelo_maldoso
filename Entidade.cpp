#include "Entidade.hpp"

Entidades::Entidade::Entidade()
	: corpo()
{

}

Entidades::Entidade::Entidade(const sf::Vector2f pos, const sf::Vector2f tam)
	: corpo(sf::RectangleShape(tam))
{
	corpo.setPosition(pos);
}

Entidades::Entidade::~Entidade()
{

}

const sf::RectangleShape Entidades::Entidade::getCorpo() const
{
	return corpo;
}

void Entidades::Entidade::mover(sf::Vector2f ds)
{
	corpo.move(ds);
}

