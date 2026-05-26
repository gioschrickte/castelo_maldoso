#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include "IDs.hpp"
using namespace std;

namespace Entidade {
	
	class Entidade{
	protected:
		sf::RectangleShape corpo;
		const IDs::IDs id;
	public:
		Entidade();
		Entidade(const sf::Vector2f pos, const sf::Vector2f tam, IDs::IDs id);
		~Entidade();
		const sf::RectangleShape getCorpo() const;
		virtual void atualizar() = 0;
		IDs::IDs getID() const { return id;}
		virtual void colisao(Entidade* outraEntidade, sf::Vector2f ds) = 0;
		void mover(sf::Vector2f ds);
	};
}