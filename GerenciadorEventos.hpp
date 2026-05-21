#pragma once
#include "Jogador.hpp"
#include "GerenciadorGrafico.hpp"

namespace Gerenciador {
	
	class GerenciadorEvento
	{
	private:
		GerenciadorGrafico* pGrafico;
		Entidade::Personagem::Jogador::Jogador* pJogador;

		static GerenciadorEvento* pEvento;
		GerenciadorEvento();
	public:
		~GerenciadorEvento();
		static GerenciadorEvento* getGerenciadorEvento();
		void setJogador(Entidade::Personagem::Jogador::Jogador* pJ);
		void verificaTeclaPressionada(sf::Keyboard::Key tecla);
		void verificaTeclaSolta(sf::Keyboard::Key tecla);
		void executar();
	};
}