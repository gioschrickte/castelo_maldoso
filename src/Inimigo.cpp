#include "Inimigo.h"
#include "Jogador.h"

#define COOLDOWN_HIT 1.0f

Entidades::Personagens::Inimigos::Inimigo::Inimigo(Jogadores::Jogador* pjogador, const sf::Vector2f pos, const sf::Vector2f tam, const float vel)
	: Personagem(pos, tam, 100.0f, IDs::IDs::inimigo), jogador(pjogador), relogioAleatorio(), relogioHit(), primeiroHit(true), dano(0.0f)
{
	temSprite = false;
}

Entidades::Personagens::Inimigos::Inimigo::~Inimigo(){}

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
	
}

