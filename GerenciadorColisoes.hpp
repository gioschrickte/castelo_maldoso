#pragma once
#include "ListaEntidade.hpp"
#include "Inimigo.hpp"
#include "Jogador.hpp"
#include "Obstaculo.hpp"
#include <vector>
#include <list>
#include <set>

namespace Gerenciador {

	class GerenciadorColisoes 
	{
		private:
			vector<Entidades::Personagens::Inimigos::Inimigo*>LIs;
			list<Entidades::Obstaculos::Obstaculo*>LOs;
			//Projetil
			Entidades::Personagens::Jogadores::Jogador* pJog1;

			//Entidades::Personagens::Jogadores::Jogador* pJog2;		
			GerenciadorColisoes();	 // Padrão singleton: Construtora como atributo privado
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
			//void tratarColisoesJogsProjeteis();
			void tratarColisoesInimgsObstacs();
			void incluirInimigo(Entidades::Personagens::Inimigos::Inimigo* pInim);
			void incluirObstaculo(Entidades::Obstaculos::Obstaculo* pObst);
			//void incluirProjetil(pj: *Projetil);
			
			
	};
}