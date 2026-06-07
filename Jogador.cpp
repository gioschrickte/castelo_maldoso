#include "Jogador.hpp"
#include "Inimigo.hpp"

Entidades::Personagens::Jogadores::Jogador::Jogador(const sf::Vector2f pos, const sf::Vector2f tam)
	: Personagem(pos, tam, 200.0f, IDs::IDs::jogador)
{
	corpo.setFillColor(sf::Color::Blue);
	vidaMax = 20.0f;
	vida = vidaMax;
}

Entidades::Personagens::Jogadores::Jogador::~Jogador()
{

}


void Entidades::Personagens::Jogadores::Jogador::executar()
{	
	float dt = calcularDt();
	if (podeAndar) atualizarX(dt);
	atualizarY(dt);
}

void Entidades::Personagens::Jogadores::Jogador::colidir(Entidades::Personagens::Inimigos::Inimigo* inimigo)
{
	inimigo->danificar(this);
}