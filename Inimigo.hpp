#pragma once

#include "Personagem.hpp"
#define RAIO_PERSEGUIR 200.0f

namespace Entidades {
	namespace Personagens {
		// forward declaration do Jogador (evita incluir Jogador.hpp aqui)
		namespace Jogadores { class Jogador; }

		namespace Inimigos {
			class Inimigo : public Personagem {
			private:
				Entidades::Personagens::Jogadores::Jogador* jogador;
				short moveAleatorio;
				sf::Clock relogioAleatorio;
				void inicializa();
			public:
				Inimigo(Entidades::Personagens::Jogadores::Jogador* pjogador, const sf::Vector2f pos = sf::Vector2f(0.0f, 0.0f), const sf::Vector2f tam = sf::Vector2f(50.0f, 50.0f), const float vel = 0.01f);
				~Inimigo();
				void persegueJogador(sf::Vector2f posJogador, sf::Vector2f posInimigo);
				void movAleatorio();
				void executar();
				void colidir(Entidades::Entidade* outraEntidade, sf::Vector2f ds = sf::Vector2f(0.0f, 0.0f));
				virtual void danificar(Entidades::Personagens::Jogadores::Jogador* pJog) {}
			};
		}
	}
}