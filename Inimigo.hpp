#pragma once

#include "Jogador.hpp"
#define RAIO_PERSEGUIR 200.0f

namespace Entidade
{
	namespace Personagem
	{
		namespace Inimigo
		{
			class Inimigo : public Personagem
			{
			private:
				Jogador::Jogador* jogador;
				short moveAleatorio;
				sf::Clock relogioAleatorio;
				void inicializa();
			public:
				Inimigo(Jogador::Jogador* pjogador, const sf::Vector2f pos = sf::Vector2f(0.0f, 0.0f), const sf::Vector2f tam = sf::Vector2f(50.0f, 50.0f), const float vel = 0.01f);
				~Inimigo();
				void persegueJogador(sf::Vector2f posJogador, sf::Vector2f posInimigo);
				void movAleatorio();
				void atualizar();
			};
		}
	}
}


