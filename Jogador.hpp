#pragma once
#include "Personagem.hpp"
#include "Inimigo.hpp"
#include <iostream>
using namespace std;

namespace Entidade
{
	namespace Personagem
	{
		namespace Jogador
		{
			class Jogador : public Personagem
			{
			private:
				// int vidas;
				void inicializa();
			public:
				Jogador(const sf::Vector2f pos = sf::Vector2f(0.0f, 0.0f), const sf::Vector2f tam = sf::Vector2f(50.0f, 50.0f));
				~Jogador();
				void atualizar();
				void colidir(Inimigo::Inimigo* pIn);
			};
		}
	}

}

