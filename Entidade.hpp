#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
using namespace std;

namespace Entidades {
	
	class Entidade{
	protected:
		sf::RectangleShape corpo;
	public:
		Entidade();
		Entidade(const sf::Vector2f pos, const sf::Vector2f tam);
		~Entidade();
		const sf::RectangleShape getCorpo() const;
		virtual void executar() = 0;
		void mover(sf::Vector2f ds);
	};
}