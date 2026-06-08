#include "Ente.h"

// DefiniÃ§Ã£o do membro estÃ¡tico (uma Ãºnica vez em todo o projeto)
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

void Jogo::Ente::setGG(Gerenciador::GerenciadorGrafico* pgg) // serÃ¡ tratado na Principal, onde o GG Ã© criado e passado para as entidades, para que elas possam desenhar a si mesmas
{
	pGG = pgg;
}
