#pragma once
#include "Jogador.h"
#include "GerenciadorGrafico.h"


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
		Jogo::Fases::Fase* pFase;
		

		static GerenciadorEvento* pEvento;
		GerenciadorEvento();
	public:
		~GerenciadorEvento();
		static GerenciadorEvento* getGerenciadorEvento();
		void setJogador(Entidades::Personagens::Jogadores::Jogador* pJ);
		void verificaTeclaPressionada(sf::Keyboard::Key tecla);
		void verificaTeclaSolta(sf::Keyboard::Key tecla);
		void executar();
		void setFase(Jogo::Fases::Fase* f) {pFase = f;}
	};
}
