#include "Inimigo.hpp"
#include "Jogador.hpp"

Entidades::Personagens::Inimigos::Inimigo::Inimigo(Jogadores::Jogador* pjogador, const sf::Vector2f pos, const sf::Vector2f tam, const float vel)
	: Personagem(pos, tam, 100.0f, IDs::IDs::inimigo), jogador(pjogador)
{
	corpo.setFillColor(sf::Color::Red);
	moveAleatorio = rand() % 4;
}

Entidades::Personagens::Inimigos::Inimigo::~Inimigo()
{
}

void Entidades::Personagens::Inimigos::Inimigo::persegueJogador(sf::Vector2f posJogador, sf::Vector2f posInimigo)
{
	if (posJogador.x - posInimigo.x > 0.0f) // à direita
	{
		andar(false);
	}
	else
	{
		andar(true);
	}
}

void Entidades::Personagens::Inimigos::Inimigo::movAleatorio()
{
	if (moveAleatorio == 0)
	{
		andar(false);
	}
	else if (moveAleatorio == 1)
	{
		andar(true);
	}
	else
		parar();

	float dt = relogioAleatorio.getElapsedTime().asSeconds();
	if (dt >= 1.0f)
	{
		moveAleatorio = rand() % 4;
		relogioAleatorio.restart();
	}

}
void Entidades::Personagens::Inimigos::Inimigo::executar()
{
	sf::Vector2f posJogador = jogador->getCorpo().getPosition();
	sf::Vector2f posInimigo = corpo.getPosition();

	if ((fabs(posJogador.x - posInimigo.x) <= RAIO_PERSEGUIR))
	{
		persegueJogador(posJogador, posInimigo);
	}
	else
	{
		movAleatorio();
	}

	if (podeAndar)
	{
		atualizarPosicao();
	}

	relogio.restart();
}