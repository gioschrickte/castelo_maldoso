#pragma once
#include "Lista.hpp"
#include "Entidade.hpp"
namespace Lista {

	class ListaEntidade {
	private:
		Lista<Entidades::Entidade> objListaEntidade;
	public:
		ListaEntidade();
		~ListaEntidade();
		void addEntidade(Entidades::Entidade* entidade);
		void removerEntidade(Entidades::Entidade* entidade);
		void removerEntidade(int pos);
		int getTam();
		void limpaLista();
		Entidades::Entidade* operator[](int pos);
		void executar(sf::RenderWindow* window); // pintar todas as entidades na tela
	};
}