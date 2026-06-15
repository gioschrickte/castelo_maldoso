#pragma once

#include "Personagem.h"
// nÃ£o incluir Inimigo.hpp aqui; forward declare:
namespace Entidades {
	namespace Personagens {
		namespace Inimigos { class Inimigo; }

		namespace Jogadores {
			class Jogador : public Personagem {
			private:
				bool ataqueAtivo;
				sf::Clock relogioAtaque;
				float danoAtaque;
			public:
				Jogador(const sf::Vector2f pos = sf::Vector2f(0.0f, 0.0f), const sf::Vector2f tam = sf::Vector2f(50.0f, 50.0f));
				~Jogador();
				void executar();
				void colidir(Entidades::Personagens::Inimigos::Inimigo* inimigo);
				void setChao(bool noChao) { this->noChao = noChao; }
				void atacar();
				bool estaAtacando() const;
				float getDanoAtaque() const;
				void salvar();
				void salvarDataBuffer();
			};
		}
	}
}
