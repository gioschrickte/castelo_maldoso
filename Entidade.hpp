#pragma once

#include "IDs.hpp"
#include "Ente.hpp"
#include <SFML\Graphics.hpp>
#include <iostream>
using namespace std;



namespace Entidades {
	
	class Entidade : public Jogo::Ente {
	protected:
	public:
		Entidade();
		Entidade(const sf::Vector2f pos, const sf::Vector2f tam, const IDs::IDs id);
		~Entidade();
		const sf::RectangleShape getCorpo() const;
		const IDs::IDs getId() const;
		const sf::Vector2f getPosicao() const;
		const sf::Vector2f getTamanho() const;
		virtual void executar() = 0;
		void mover(sf::Vector2f ds);
	};
}