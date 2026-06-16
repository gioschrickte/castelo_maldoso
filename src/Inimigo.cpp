#include "Inimigo.h"
#include "Jogador.h"
#include <cmath>

#define COOLDOWN_HIT 1.0f

Entidades::Personagens::Inimigos::Inimigo::Inimigo(Jogadores::Jogador* pjogador, const sf::Vector2f pos, const sf::Vector2f tam, const float vel)
	: Personagem(pos, tam, 100.0f, IDs::IDs::inimigo), jogador(pjogador), jogador2(nullptr), relogioAleatorio(), relogioHit(), primeiroHit(true), dano(0.0f)
{
	temSprite = false;
}

Entidades::Personagens::Inimigos::Inimigo::~Inimigo(){}

// Retorna o jogador vivo mais proximo deste inimigo. Se so um vive, retorna esse;
// se nenhum vive, retorna 'jogador' (a fase encerra de qualquer forma).
Entidades::Personagens::Jogadores::Jogador* Entidades::Personagens::Inimigos::Inimigo::getAlvo() const
{
	bool vivo1 = jogador && jogador->getAtiva();
	bool vivo2 = jogador2 && jogador2->getAtiva();

	if (vivo1 && vivo2)
	{
		sf::Vector2f p = getPosicao();
		sf::Vector2f p1 = jogador->getPosicao();
		sf::Vector2f p2 = jogador2->getPosicao();
		float d1 = fabs(p1.x - p.x) + fabs(p1.y - p.y);
		float d2 = fabs(p2.x - p.x) + fabs(p2.y - p.y);
		return (d1 <= d2) ? jogador : jogador2;
	}
	if (vivo2) return jogador2;
	return jogador;
}

bool Entidades::Personagens::Inimigos::Inimigo::podeHitar()
{
	if (primeiroHit || relogioHit.getElapsedTime().asSeconds() >= COOLDOWN_HIT)
	{
		primeiroHit = false;
		relogioHit.restart();
		return true;
	}
	return false;
}

void Entidades::Personagens::Inimigos::Inimigo::danificar(Jogadores::Jogador* pJog)
{
	// Aqui vocÃª pode implementar a lÃ³gica de dano ao jogador, como reduzir a vida ou reiniciar o jogo
	std::cout << "O inimigo danificou o jogador!" << std::endl;
	pJog->tomarDano(1.0f); // Exemplo: reduz a vida do jogador em 1 ponto
}

void Entidades::Personagens::Inimigos::Inimigo::salvarDataBuffer()
{
	Entidades::Personagens::Personagem::salvarDataBuffer();
	
}

