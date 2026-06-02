#include "Inimigo.hpp"
#include "Jogador.hpp"

Entidades::Personagens::Inimigos::Inimigo::Inimigo(Jogadores::Jogador* pjogador, const sf::Vector2f pos, const sf::Vector2f tam, const float vel)
	: Personagem(pos, tam, 100.0f, IDs::IDs::inimigo), jogador(pjogador), relogioAleatorio()
{
	temSprite = false;
	//textura = pGG->carregarTextura("assets/zombie.png");
	//sprite.setTexture(textura);
	//sprite.setPosition(pos);
}

Entidades::Personagens::Inimigos::Inimigo::~Inimigo(){}
