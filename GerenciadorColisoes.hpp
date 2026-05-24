#pragma once
#include "Lista.hpp"
#include "ListaEntidade.hpp"
#include "Entidade.hpp"

namespace Gerenciador {

	class GerenciadorColisoes 
	{
		private:
			Lista::ListaEntidade* listaPersonagem;
			Lista::ListaEntidade* listaObstaculo;
		public:
			GerenciadorColisoes(Lista::ListaEntidade* listaPersonagem, Lista::ListaEntidade* listaObstaculo);
			~GerenciadorColisoes();
			const sf::Vector2f calculaColisao(Entidade::Entidade* ent1, Entidade::Entidade* ent2);
			void executar();



			

	};
}