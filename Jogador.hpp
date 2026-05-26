#pragma once

#include "Personagem.hpp"
// não incluir Inimigo.hpp aqui; forward declare:
namespace Entidades {
	namespace Personagens {
		namespace Inimigos { class Inimigo; }

		namespace Jogadores {
			class Jogador : public Personagem {
			private:
				void inicializa();
			public:
				Jogador(const sf::Vector2f pos = sf::Vector2f(0.0f, 0.0f), const sf::Vector2f tam = sf::Vector2f(50.0f, 50.0f));
				~Jogador();
				void executar();
				void colidir(Entidades::Entidade* outraEntidade, sf::Vector2f ds = sf::Vector2f(0.0f, 0.0f));
				void colidir(Entidades::Personagens::Inimigos::Inimigo* inimigo);
			};
		}
	}
}