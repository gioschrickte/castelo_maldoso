#pragma once
#include "Personagem.hpp"
#define RAIO_PERSEGUIR 200.0f

namespace Entidades {
	namespace Personagens {
		namespace Jogadores { class Jogador; } // forward declaration

		namespace Inimigos {
			class Inimigo : public Personagem {
			private:
				Entidades::Personagens::Jogadores::Jogador* jogador;
				short moveAleatorio;
				sf::Clock relogioAleatorio;
			public:
				Inimigo(Entidades::Personagens::Jogadores::Jogador* pjogador,
					const sf::Vector2f pos = sf::Vector2f(0.0f, 0.0f),
					const sf::Vector2f tam = sf::Vector2f(50.0f, 50.0f),
					const float vel = 100.0f);
				virtual ~Inimigo();
				void persegueJogador(sf::Vector2f posJogador, sf::Vector2f posInimigo);
				void movAleatorio();
				void executar() override;
				virtual void danificar(Entidades::Personagens::Jogadores::Jogador* pJog) = 0;
			};
		}
	}
}