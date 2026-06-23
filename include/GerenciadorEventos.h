#pragma once
#include "Jogador.h"
#include "GerenciadorGrafico.h"

// Ref: Giovane Limas Salvi


namespace Jogo {
    namespace Fases {
        class Fase;
    }
}

namespace Gerenciador {
	
	class GerenciadorEvento
	{
	private:
		GerenciadorGrafico* pGrafico;
		Entidades::Personagens::Jogadores::Jogador* pJogador;
		Entidades::Personagens::Jogadores::Jogador* pJogador2;


		Jogo::Fases::Fase* pFase;
		

		static GerenciadorEvento* pEvento;
		GerenciadorEvento();
	public:
		~GerenciadorEvento();
		static GerenciadorEvento* getGerenciadorEvento();
		void setJogador(Entidades::Personagens::Jogadores::Jogador* pJ);
		void setJogador2(Entidades::Personagens::Jogadores::Jogador* pJ2);
		void verificaTeclaPressionada(sf::Keyboard::Key tecla);
		void verificaTeclaSolta(sf::Keyboard::Key tecla);
		void executar();
		void setFase(Jogo::Fases::Fase* f) {pFase = f;}
	};
}
