#pragma once
#include "Lista.hpp"
#include "Entidade.hpp"

namespace Lista {

	class ListaEntidade {
	private:
		Lista<Entidade::Entidade> objListaEntidade;
	public:
		ListaEntidade();
		~ListaEntidade();
		void addEntidade(Entidade::Entidade* entidade);
		void removerEntidade(Entidade::Entidade* entidade);
		void removerEntidade(int pos);
		int getTam();
		void limpaLista();
		Entidade::Entidade* operator[](int pos);
		void executar(sf::RenderWindow* window); // pintar todas as entidades na tela
	};
}