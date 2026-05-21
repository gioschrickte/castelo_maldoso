#include "ListaEntidade.hpp"

Lista::ListaEntidade::ListaEntidade() :
	objListaEntidade()
{

}

Lista::ListaEntidade::~ListaEntidade()
{

}

void Lista::ListaEntidade::addEntidade(Entidade::Entidade* entidade)
{
	objListaEntidade.addElemento(entidade);
}

void Lista::ListaEntidade::removerEntidade(Entidade::Entidade* entidade)
{
	objListaEntidade.removerElemento(entidade);
}

void Lista::ListaEntidade::removerEntidade(int pos)
{
	objListaEntidade.removerElemento(pos);
}

int Lista::ListaEntidade::getTam()
{
	return objListaEntidade.getTam();
}

void Lista::ListaEntidade::limpaLista()
{
	objListaEntidade.limpaLista();
}

Entidade::Entidade* Lista::ListaEntidade::operator[](int pos)
{
	return objListaEntidade.operator[](pos);
}

void Lista::ListaEntidade::executar(sf::RenderWindow* window)
{
	int tam = objListaEntidade.getTam();
	Entidade::Entidade* aux = nullptr;
	for (int i = 0; i < tam; i++)
	{
		aux = objListaEntidade[i];
		aux->atualizar();
		window->draw(aux->getCorpo());
	}
}