#pragma once

namespace Lista {

	template<class TE>
	class Elemento {
	private:
		Elemento<TE>* pProx;
		TE* elemento;
	public:
		Elemento();
		~Elemento();
		void setProx(Elemento<TE>* prox);
		void setElemento(TE* elem);
		Elemento<TE>* getProx();
		TE* getElemento();
	};

	template<class TE>
	Elemento<TE>::Elemento()
		: pProx(nullptr), elemento(nullptr)
	{

	}

	template<class TE>
	Elemento<TE>::~Elemento() {}

	template<class TE>
	void Elemento<TE>::setProx(Elemento<TE>* prox)
	{
		pProx = prox;
	}

	template<class TE>
	void Elemento<TE>::setElemento(TE* elem)
	{
		elemento = elem;
	}

	template <class TE>
	Elemento<TE>* Elemento<TE>::getProx()
	{
		return pProx;
	}

	template <class TE>
	TE* Elemento<TE>::getElemento()
	{
		return elemento;
	}
}