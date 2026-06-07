#pragma once
#include "Personagem.hpp"
#define RAIO_PERSEGUIR 200.0f

namespace Entidades {
	namespace Personagens {
		namespace Jogadores { class Jogador; } // forward declaration

		namespace Inimigos {
			class Inimigo : public Personagem {
			protected:
				Entidades::Personagens::Jogadores::Jogador* jogador;
				sf::Clock relogioAleatorio;
				float dano;
			public:
				Inimigo(Entidades::Personagens::Jogadores::Jogador* pjogador,
					const sf::Vector2f pos = sf::Vector2f(0.0f, 0.0f),
					const sf::Vector2f tam = sf::Vector2f(50.0f, 50.0f),
					const float vel = 100.0f);
				virtual ~Inimigo();
				virtual void executar() = 0;
				virtual void danificar(Entidades::Personagens::Jogadores::Jogador* pJog) = 0;
			};
		}
	}
}