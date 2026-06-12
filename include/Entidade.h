#pragma once

#include "IDs.h"
#include "Ente.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include <sstream>
using namespace std;



namespace Entidades {
	
	class Entidade : public Jogo::Ente {
	protected:
		bool ativa = true; // indica se a entidade esta ativa no jogo
		stringstream buffer;
	public:
		Entidade();
		Entidade(const sf::Vector2f pos, const sf::Vector2f tam, const IDs::IDs id);
		virtual ~Entidade();
		const sf::RectangleShape getCorpo() const;
		const IDs::IDs getId() const;
		const sf::Vector2f getPosicao() const;
		const sf::Vector2f getTamanho() const;
		virtual void executar() = 0;
		void mover(sf::Vector2f ds);
		virtual void salvarDataBuffer();
		virtual void salvar() = 0;
	};
}
