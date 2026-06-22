#include "Ente.h"


Gerenciador::GerenciadorGrafico* Jogo::Ente::pGG = nullptr;	

Jogo::Ente::Ente()
	: corpo(), id(IDs::IDs::vazio)
{
}

Jogo::Ente::Ente(const sf::Vector2f pos, const sf::Vector2f tam, const IDs::IDs id)
	: corpo(sf::RectangleShape(tam)), id(id)
{
	corpo.setPosition(pos);
}

Jogo::Ente::~Ente()
{
}

void Jogo::Ente::desenhar()
{
	if (temSprite)
	{
		sprite.setPosition(corpo.getPosition());
		pGG->desenhaSprite(sprite);
	}
	else
		pGG->desenhaElemento(corpo);
}

const sf::RectangleShape Jogo::Ente::getCorpo() const
{
	return corpo;
}

const sf::Vector2f Jogo::Ente::getPosicao() const
{
	return corpo.getPosition();
}

const sf::Vector2f Jogo::Ente::getTamanho() const
{
	return corpo.getSize();
}

void Jogo::Ente::setGG(Gerenciador::GerenciadorGrafico* pgg) 
{
	pGG = pgg;
}
