#pragma once
#include <iostream>
using namespace std;

namespace Lista {

	template <class TL>
	class Lista {
	private:
		// Elemento e um detalhe interno da Lista (so existe como no encadeado dela),
		// entao fica aninhado e privado. Por estar dentro do template, usa o proprio TL.
		class Elemento {
		private:
			Elemento* pProx;
			TL* elemento;
		public:
			Elemento() : pProx(nullptr), elemento(nullptr) {}
			~Elemento() {}
			void setProx(Elemento* prox) { pProx = prox; }
			void setElemento(TL* elem) { elemento = elem; }
			Elemento* getProx() { return pProx; }
			TL* getElemento() { return elemento; }
		};

		Elemento* pInicio;
		Elemento* pUltimo;
		unsigned int tam;
	public:
		class Iterator
		{
		private:
			Elemento* atual;
		public:
			Iterator(Elemento* cabeca = nullptr)
				: atual(cabeca)
			{
			}
			~Iterator()
			{
				atual = nullptr;
			}
			TL* operator*()
			{
				return atual->getElemento();
			}
			Iterator& operator++()
			{
				if (atual)
					atual = atual->getProx();
				return *this;
			}
			const bool operator==(const Iterator& valor) const
			{
				return atual == valor.atual;
			}
			const bool operator!=(const Iterator& valor) const
			{
				return atual != valor.atual;
			}
			Elemento* getAtual() const
			{
				return atual;
			}
		};

		Lista();
		~Lista();
		void addElemento(TL* info);
		void removerElemento(TL* info);
		void removerElemento(int pos);
		int getTam();
		void limpaLista();
		TL* operator[](int pos);

		Iterator inicio()
		{
			return Iterator(pInicio);
		}
		Iterator fim()
		{
			// past-the-end: pUltimo->getProx() == nullptr
			return Iterator(nullptr);
		}

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
			Elemento* pAux = pInicio;
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
			pInicio = new Elemento;
			pInicio->setProx(nullptr);
			pUltimo = pInicio;
			pInicio->setElemento(info);
		}
		else
		{
			pUltimo->setProx(new Elemento);
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
			Elemento* pAux = pInicio;
			while (pAux != nullptr && pAux->getElemento() != info)
			{
				pAux = pAux->getProx();
			}
			if (pAux != nullptr && pAux->getElemento() == info)
			{
				Elemento* pAux2 = pAux;
				pAux = pAux->getProx();
				delete(pAux2);
				pAux2 = nullptr;
				tam--;
			}
			else {
				cout << "Elemento nao encontrado na lista!" << endl;
			}
		}
		else {
			cout << "Lista vazia." << endl;
		}
	}

	template <class TL>
	void Lista<TL>::removerElemento(int pos)
	{
		if (pos < (int)tam && tam > 0)
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
		if (pos < (int)tam && tam > 0)
		{
			Elemento* pAux = pInicio;
			for (int c = 0; c < pos; c++)
			{
				pAux = pAux->getProx();
			}
			return pAux->getElemento();
		}
		return nullptr;
	}
}
