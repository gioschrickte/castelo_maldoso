#pragma once
#include <iostream>
#include "Elemento.hpp"
using namespace std;


namespace Lista {
	
	template <class TL>
	class Lista {
	private:
		Elemento<TL>* pInicio;
		Elemento<TL>* pUltimo;
		unsigned int tam;
	public:
		Lista();
		~Lista();
		void addElemento(TL* info);
		void removerElemento(TL* info);
		void removerElemento(int pos);
		int getTam();
		void limpaLista();
		TL* operator[](int pos);
	};

	template <class TL>
	Lista<TL>::Lista():
		pInicio(nullptr), pUltimo(nullptr), tam(0)
	{

	}

	template <class TL>
	Lista<TL>::~Lista()
	{
		while (pInicio != pUltimo)
		{
			Elemento<TL>* pAux = pInicio;
			pInicio = pInicio->getProx();
			delete(pAux);
			pAux = nullptr;
			tam--;
		}
		delete(pUltimo);
		pUltimo = nullptr;
	}

	template <class TL>
	void Lista<TL>::addElemento(TL* info)
	{
		if (pUltimo == nullptr)
		{
			pInicio = new Elemento<TL>;
			pInicio->setProx(nullptr);
			pUltimo = pInicio;
			pInicio->setElemento(info);
		}
		else
		{
			pUltimo->setProx(new Elemento<TL>);
			pUltimo = pUltimo->getProx();
			pUltimo->setElemento(info);
			pUltimo->setProx(nullptr);
		}
		tam++;
	}

	template <class TL>
	void Lista<TL>::removerElemento(TL* info)
	{
		if (tam > 0)
		{
			Elemento<TL>* pAux = pInicio;
			while (pAux->getElemento() != info && pAux != nullptr)
			{
				pAux = pAux->getProx();
			}
			if (pAux->getElemento() == info)
			{
				Elemento<TL>* pAux2 = pAux;
				pAux = pAux->getProx();
				delete(pAux2);
				pAux2 = nullptr;
				tam--;
			}
			else {
				cout << "Elemento não encontrado na lista!" << endl;
			}
		}
		else {
			cout << "Lista vazia." << endl;
		}
	}

	template <class TL>
	void Lista<TL>::removerElemento(int pos)
	{
		if (pos < tam && tam > 0)
		{
			removerElemento(this->operator[](pos));
		}
	}

	template <class TL>
	int Lista<TL>::getTam()
	{
		return tam;
	}
	
	template <class TL>
	void Lista<TL>::limpaLista()
	{
		while (tam > 0)
		{
			removerElemento(0);
		}
	}

	template <class TL>
	TL* Lista<TL>::operator[](int pos)
	{
		if (pos < tam && tam > 0)
		{	
			Elemento<TL>* pAux = pInicio;
			int c = 0;
			for (c; c < pos; c++)
			{
				pAux = pAux->getProx();
			}
			return pAux->getElemento();
		}
	}
}