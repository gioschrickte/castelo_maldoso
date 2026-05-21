#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Entidade.hpp"

namespace Entidade
{
	namespace Personagem {
		class Personagem : public Entidade
		{
		protected:
			sf::Vector2f velFinal;
			bool podeAndar;
			bool paraEsquerda;
			sf::Clock relogio;
			float dt;
		public:
			Personagem(const sf::Vector2f pos = sf::Vector2f(0.0f, 0.0f), const sf::Vector2f tam = sf::Vector2f(50.0f, 50.0f), const float vel = 0.01f);
			~Personagem();
			void andar(const bool paraEsquerda);
			void parar();
			void atualizarPosicao();
		};
	}
}


