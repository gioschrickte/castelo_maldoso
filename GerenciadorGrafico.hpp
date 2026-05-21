#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

namespace Gerenciador
{
	class GerenciadorGrafico
	{
	private:
		sf::RenderWindow* window;

		static GerenciadorGrafico* pGrafico;
		GerenciadorGrafico(); // Padrão singleton, a principal não criará o GG pela construtora, mas sim por outra função que chamará a construtora
	public:
		~GerenciadorGrafico();
		static GerenciadorGrafico* getGerenciadorGrafico();
		sf::RenderWindow* getWindow();
		void limpaJanela();
		void desenhaElemento(sf::RectangleShape corpo);
		void mostraElementos();
		void fecharJanela();
		const bool verificaJanelaAberta();
	};
}