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

void Entidades::Personagens::Inimigos::Inimigo::danificar(Jogadores::Jogador* pJog)
{
	// Aqui você pode implementar a lógica de dano ao jogador, como reduzir a vida ou reiniciar o jogo
	std::cout << "O inimigo danificou o jogador!" << std::endl;
	pJog->tomarDano(1.0f); // Exemplo: reduz a vida do jogador em 1 ponto
}
