#pragma once

#include "Inimigo.h"

namespace Entidades { class Projetil; } // pra nao dar erro

namespace Entidades
{
	namespace Personagens
	{
		namespace Inimigos
		{
			class Mago : public Inimigo
			{
			private:
				short int forca;
				Entidades::Projetil* projetil;
				sf::Clock relogioTiro;
				bool  projetilEstavaAtivo;
				short moveAleatorio;

				void atualizarTiro();
			public:
				Mago(Jogadores::Jogador* j,
					const sf::Vector2f pos = sf::Vector2f(0.0f, 0.0f));
				~Mago();
				void executar() override;
				void danificar(Jogadores::Jogador* pJog) override;

				void setProjetil(Entidades::Projetil* p) { projetil = p; }

				void persegueJogador(sf::Vector2f posJogador, sf::Vector2f posMago);
				void movAleatorio();
                void salvar();
				void salvarDataBuffer();

			};
		}
	}
}
