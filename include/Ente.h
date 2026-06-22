#pragma once



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
		static Gerenciador::GerenciadorGrafico* pGG; 
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

