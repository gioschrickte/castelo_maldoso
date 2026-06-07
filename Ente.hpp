#pragma once

// Começemos o trabalho da classe "Ente"
// A classe Ente é a classe base para tudo o que é graficamente exibido no jogo, portanto deve conter um corpo e um ID, para que o gerenciador gráfico saiba o que desenhar, e o gerenciador de colisões saiba como tratar as colisões.
// Nessa lógica, todas entidades são derivadas de Ente, assim como a Fase e o Menu, que serão implementados posteriormente

#include "IDs.hpp"
#include "GerenciadorGrafico.hpp"
#include <SFML\Graphics.hpp>

namespace Jogo
{
	class Ente
	{
	protected:
		sf::RectangleShape corpo;
		const IDs::IDs id;
		static Gerenciador::GerenciadorGrafico* pGG; // Ponteiro para o gerenciador gráfico, para que as entidades possam desenhar a si mesmas
		sf::Texture textura;
		sf::Sprite sprite;
		bool temSprite = false;
	public:
		Ente();
		Ente(const sf::Vector2f pos, const sf::Vector2f tam, const IDs::IDs id);
		virtual ~Ente();
		virtual void executar() = 0;
		virtual void desenhar();
		static void setGG(Gerenciador::GerenciadorGrafico* pgg);
	};
}

