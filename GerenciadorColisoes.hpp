#pragma once
#include "Lista.hpp"
#include "ListaEntidade.hpp"
#include "Entidade.hpp"
#include "Inimigo.hpp"
#include "Personagem.hpp"
#include "Obstaculo.hpp"
#include <vector>
#include <list>
#include <set>

namespace Gerenciador {

	class GerenciadorColisoes 
	{
		private:
			vector<Entidade::Personagem::Inimigo::Inimigo*>LIs;
			list<Entidade::Obstaculo::Obstaculo*>LOs;
			//Projetil
			Entidade::Personagem::Jogador::Jogador* pJog1;
			//Entidade::Personagem::Jogador::Jogador* pJog2;


			

		public:
			GerenciadorColisoes(Entidade::Personagem::Jogador::Jogador* p);
			~GerenciadorColisoes();
			const sf::Vector2f calculaColisao(Entidade::Entidade* ent1, Entidade::Entidade* ent2);
			void executar();
			const bool verificarColisao(Entidade::Entidade* ent1, Entidade::Entidade* ent2);
			void tratarColisoesJogsObstacs();
			void tratarColisoesJogsInimgs();
			void tratarColisoesJogsProjeteis();
			void incluirInimigo(Entidade::Personagem::Inimigo::Inimigo* pInim);
			void incluirObstaculo(Entidade::Obstaculo::Obstaculo* pObst);
			//void incluirProjetil(pj: *Projetil);
			
			
	};
}