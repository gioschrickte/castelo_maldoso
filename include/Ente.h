#pragma once

// ComeÃ§emos o trabalho da classe "Ente"
// A classe Ente Ã© a classe base para tudo o que Ã© graficamente exibido no jogo, portanto deve conter um corpo e um ID, para que o gerenciador grÃ¡fico saiba o que desenhar, e o gerenciador de colisÃµes saiba como tratar as colisÃµes.
// Nessa lÃ³gica, todas entidades sÃ£o derivadas de Ente, assim como a Fase e o Menu, que serÃ£o implementados posteriormente

#include "IDs.h"
#include "GerenciadorGrafico.h"
#include <SFML/Graphics.hpp>

namespace Jogo
{
	class Ente
	{
	protected:
		sf::RectangleShape corpo;
		const IDs::IDs id;
		static Gerenciador::GerenciadorGrafico* pGG; // Ponteiro para o gerenciador grÃ¡fico, para que as entidades possam desenhar a si mesmas
		sf::Texture textura;
		sf::Sprite sprite;
		bool temSprite = false;
	public:
		Ente();
		Ente(const sf::Vector2f pos, const sf::Vector2f tam, const IDs::IDs id);
		virtual ~Ente();
		virtual void executar() = 0;
		virtual void desenhar();
		const sf::RectangleShape getCorpo() const;
		const sf::Vector2f getPosicao() const;
		const sf::Vector2f getTamanho() const;
		static void setGG(Gerenciador::GerenciadorGrafico* pgg);
	};
}

