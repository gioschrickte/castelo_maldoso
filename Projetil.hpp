#pragma once
#include "Entidade.hpp"

namespace Entidades {
	class Projetil : public Entidade {
	private:
		bool ativo;
		int  dano;
		sf::Vector2f velocidade;
		sf::Clock relogio;
	public:
		Projetil(int dano = 1, const sf::Vector2f tam = sf::Vector2f(15.0f, 15.0f));
		~Projetil();

		void executar() override;

		void lancar(sf::Vector2f origem, sf::Vector2f alvo);
		void desativar();
		void atingir();

		bool estaAtivo() const;
		int  getDano()   const;
	};
}