#pragma once
#include "Jogador.h"
#include "GerenciadorGrafico.h"

namespace Gerenciador {
	
	class GerenciadorEvento
	{
	private:
		GerenciadorGrafico* pGrafico;
		Entidades::Personagens::Jogadores::Jogador* pJogador;

		static GerenciadorEvento* pEvento;
		GerenciadorEvento();
	public:
		~GerenciadorEvento();
		static GerenciadorEvento* getGerenciadorEvento();
		void setJogador(Entidades::Personagens::Jogadores::Jogador* pJ);
		void verificaTeclaPressionada(sf::Keyboard::Key tecla);
		void verificaTeclaSolta(sf::Keyboard::Key tecla);
		void executar();
	};
}
