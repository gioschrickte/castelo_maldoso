#include "Inimigo.hpp"

Entidade::Personagem::Inimigo::Inimigo::Inimigo(Jogador::Jogador* pjogador, const sf::Vector2f pos, const sf::Vector2f tam, const float vel)
	: Personagem(pos, tam, 100.0f,IDs::IDs::inimigo), jogador(pjogador)
{
	corpo.setFillColor(sf::Color::Red);
	srand(time(NULL));
	moveAleatorio = rand() % 4;
}

void Entidade::Personagem::Inimigo::Inimigo::persegueJogador(sf::Vector2f posJogador, sf::Vector2f posInimigo)
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

void Entidade::Personagem::Inimigo::Inimigo::movAleatorio()
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
void Entidade::Personagem::Inimigo::Inimigo::atualizar()
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

void Entidade::Personagem::Inimigo::Inimigo::colisao(Entidade* outraEntidade, sf::Vector2f ds)
{
	// vazio por enquanto
}