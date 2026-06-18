#pragma once
#include "Entidade.h"

namespace Entidades {
	class Projetil : public Entidade {
	private:
		bool ativo;
		int  dano;
		sf::Vector2f velocidade;
		sf::Clock relogio;
	public:
		Projetil(int dano = 5, const sf::Vector2f tam = sf::Vector2f(15.0f, 15.0f));
		~Projetil();

		void executar() override;

		void lancar(sf::Vector2f origem, sf::Vector2f alvo);
		void desativar();
		void atingir();

		bool estaAtivo() const;
		int  getDano()   const;

		// Setters usados ao carregar o projetil do arquivo de save.
		void setVelocidade(sf::Vector2f v) { velocidade = v; }
		void setAtivo(bool a) { ativo = a; }

		void salvar();
		void salvarDataBuffer();
	};
}
