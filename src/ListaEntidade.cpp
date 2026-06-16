#include "ListaEntidade.h"
Lista::ListaEntidade::ListaEntidade() :
	objListaEntidade()
{

}

Lista::ListaEntidade::~ListaEntidade()
{

}

void Lista::ListaEntidade::addEntidade(Entidades::Entidade* entidade)
{
	objListaEntidade.addElemento(entidade);
}

void Lista::ListaEntidade::removerEntidade(Entidades::Entidade* entidade)
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

Entidades::Entidade* Lista::ListaEntidade::operator[](int pos)
{
	return objListaEntidade.operator[](pos);
}

void Lista::ListaEntidade::executar(sf::RenderWindow* window)
{
	int tam = objListaEntidade.getTam();
	Entidades::Entidade* aux = nullptr;
	for (int i = 0; i < tam; i++)
	{
		aux = objListaEntidade[i];
		aux->executar();
		window->draw(aux->getCorpo());
	}
}

void Lista::ListaEntidade::salvarEntidades()
{
	for (auto it = objListaEntidade.inicio(); it != objListaEntidade.fim(); ++it)
    {
        if (*it != nullptr)
        {
            (*it)->salvar();
        }
    }
}
