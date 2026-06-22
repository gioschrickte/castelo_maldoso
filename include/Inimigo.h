#pragma once
#include "Personagem.h"
#define RAIO_PERSEGUIR 200.0f

namespace Entidades {
	namespace Personagens {
		namespace Jogadores { class Jogador; } // forward declaration

		namespace Inimigos {
			class Inimigo : public Personagem {
			protected:
				Entidades::Personagens::Jogadores::Jogador* jogador;
				Entidades::Personagens::Jogadores::Jogador* jogador2; // segundo alvo (nulo em 1 jogador)
				sf::Clock relogioAleatorio;
				sf::Clock relogioHit;
				bool primeiroHit;
				float dano;

				// Jogador vivo mais proximo entre 'jogador' e 'jogador2' 
				Entidades::Personagens::Jogadores::Jogador* getAlvo() const;
			public:
				Inimigo(Entidades::Personagens::Jogadores::Jogador* pjogador,
					const sf::Vector2f pos = sf::Vector2f(0.0f, 0.0f),
					const sf::Vector2f tam = sf::Vector2f(50.0f, 50.0f),
					const float vel = 100.0f,
					const IDs::IDs id = IDs::IDs::inimigo);
				virtual ~Inimigo();
				void setJogador2(Entidades::Personagens::Jogadores::Jogador* j2) { jogador2 = j2; }
				bool podeHitar();
				virtual void executar() = 0;
				virtual void danificar(Entidades::Personagens::Jogadores::Jogador* pJog) = 0;
				void salvarDataBuffer();
				virtual void salvar() = 0;
				virtual void persegueJogador(sf::Vector2f posJogador, sf::Vector2f posInim);
				
			};
		}
	}
}
