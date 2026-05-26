#include "Jogador.hpp"
#include "Inimigo.hpp"

Entidades::Personagens::Jogadores::Jogador::Jogador(const sf::Vector2f pos, const sf::Vector2f tam)
	: Personagem(pos, tam, 200.0f)
{
	corpo.setFillColor(sf::Color::Blue);
}

Entidades::Personagens::Jogadores::Jogador::~Jogador()
{

}


void Entidades::Personagens::Jogadores::Jogador::executar()
{
	if (podeAndar)
	{
		atualizarPosicao();
	}

	relogio.restart();
}

void Entidades::Personagens::Jogadores::Jogador::colidir(Entidades::Personagens::Inimigos::Inimigo* pIn)
{
	// Da pra fazer o jogador ficar um pouco vermelho, ou receber um knock-back
	pIn->danificar(this);
}