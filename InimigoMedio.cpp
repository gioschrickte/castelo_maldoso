#include "InimigoMedio.hpp"
#include "Jogador.hpp"
#define RAIO_PERSEGUIR 400.0f

Entidades::Personagens::Inimigos::InimigoMedio::InimigoMedio(Jogadores::Jogador* j, const sf::Vector2f pos)
    : Inimigo(j, pos, sf::Vector2f(60.0f, 60.0f), 150.0f)  // maior e mais rápido
{
    corpo.setFillColor(sf::Color::Magenta);
}

void Entidades::Personagens::Inimigos::InimigoMedio::executar()
{
	// O inimigo médio vai ficar pulando e perseguindo o jogador, ou seja, a direção do pulo é determinada pelo jogador
	
	sf::Vector2f posJogador = jogador->getPosicao();
	sf::Vector2f posInimigo = getPosicao();
	float distancia = sqrt(pow(posJogador.x - posInimigo.x, 2) + pow(posJogador.y - posInimigo.y, 2));
	if (distancia <= RAIO_PERSEGUIR)
	{
		// Persegue o jogador
		if (posJogador.x < posInimigo.x) { andar(true); } // para esquerda
		else { andar(false); } // para direita
		if (noChao) { pular(); }
	}
	else
	{
		// Fica pulando no lugar
		parar();
		if (noChao) { pular(); }
	}
	
	float dt = calcularDt();
	if(podeAndar) {
		atualizarX(dt);
	}
	atualizarY(dt);
}