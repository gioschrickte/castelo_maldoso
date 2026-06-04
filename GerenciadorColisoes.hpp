#pragma once
#include "ListaEntidade.hpp"
#include "Inimigo.hpp"
#include "Jogador.hpp"
#include "Obstaculo.hpp"
#include "Projetil.hpp"
#include "Fase.hpp"
#include <vector>
#include <list>
#include <set>

namespace Gerenciador {

	class GerenciadorColisoes
	{
	private:
		vector<Entidades::Personagens::Inimigos::Inimigo*>LIs;
		list<Entidades::Obstaculos::Obstaculo*>LOs;
		set<Entidades::Projetil*> projeteis;
		Entidades::Personagens::Jogadores::Jogador* pJog1;
		Jogo::Fases::Fase* fase;


		//Entidades::Personagens::Jogadores::Jogador* pJog2;		
		GerenciadorColisoes();	 // Padrão singleton
		static GerenciadorColisoes* pGC;

	public:
		~GerenciadorColisoes();
		static GerenciadorColisoes* getGerenciadorColisoes();
		void setJogador1(Entidades::Personagens::Jogadores::Jogador* p);
		const sf::Vector2f calculaColisao(Entidades::Entidade* ent1, Entidades::Entidade* ent2);
		void executar();

		const bool verificarColisao(Entidades::Entidade* ent1, Entidades::Entidade* ent2);
		void tratarColisoesJogsObstacs();
		void tratarColisoesJogsInimgs();
		void tratarColisoesJogsProjeteis();
		void tratarColisoesInimgsObstacs();
		void tratarColisoesChao();


		void incluirInimigo(Entidades::Personagens::Inimigos::Inimigo* pInim);
		void incluirObstaculo(Entidades::Obstaculos::Obstaculo* pObst);
		void incluirProjetil(Entidades::Projetil* pProj);
		void setFase(Jogo::Fases::Fase* f);
		void limpar(); // Limpa as listas de inimigos e obstáculos

	};
}