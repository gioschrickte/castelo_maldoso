#include "Entidade.hpp"

Entidade::Entidade::Entidade()
	: corpo()
{

}

Entidade::Entidade::Entidade(const sf::Vector2f pos, const sf::Vector2f tam)
	: corpo(sf::RectangleShape(tam))
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