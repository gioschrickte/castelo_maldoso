#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Entidade.h"

namespace Entidades
{
	namespace Personagens {
		class Personagem : public Entidade
		{
		protected:
			sf::Vector2f velFinal;
			bool podeAndar;
			bool paraEsquerda;
			sf::Clock relogio;
			bool noChao;
			float forcaPulo; // altura do pulo = forcaPulo^2 / (2 * GRAVIDADE)

			// Efeitos temporarios (lama etc.). 1.0 = normal; <1 = mais lento / pulo mais fraco.
			// Sao restaurados para 1.0 a cada frame, em atualizarY.
			float multiplicadorVel;
			float multiplicadorPulo;

			float vida;
			float vidaMax;
			sf::RectangleShape barraVida;//d

		public:
			Personagem(const sf::Vector2f pos = sf::Vector2f(0.0f, 0.0f), const sf::Vector2f tam = sf::Vector2f(50.0f, 50.0f), const float vel = 0.01f,
				const IDs::IDs id = IDs::IDs::vazio);
			virtual ~Personagem();
			void andar(const bool paraEsquerda);
			void parar();

			float calcularDt();
			void atualizarX(float dt);
			void atualizarY(float dt);

			void pular();
			void aterrissar();
			void baterCabeca();

			// Chamado pelos obstaculos de "zona" (ex.: Lama) enquanto ha contato.
			// Vale por 1 frame; se ninguem chamar, o personagem volta ao normal sozinho.
			void aplicarLentidao(float fatorVel, float fatorPulo);

			void tomarDano(float dano);
			float getVida() const;
			float getVidaMax() const;
			bool olhandoParaEsquerda() const { return paraEsquerda; }
			void atualizaVida();
			void desenhar();
			virtual void salvar() = 0;
			void salvarDataBuffer();
		};
	}
}
