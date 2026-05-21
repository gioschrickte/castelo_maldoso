#include "Jogador.hpp"

Entidade::Personagem::Jogador::Jogador::Jogador(const sf::Vector2f pos, const sf::Vector2f tam)
	: Personagem(pos, tam, 200.0f)
{
	corpo.setFillColor(sf::Color::Blue);
}

Entidade::Personagem::Jogador::Jogador::~Jogador()
{

}


void Entidade::Personagem::Jogador::Jogador::atualizar()
{
	if (podeAndar)
	{
		atualizarPosicao();
	}

	relogio.restart();
}