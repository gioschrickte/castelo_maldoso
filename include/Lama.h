#pragma once
#include "Obstaculo.h"

namespace Entidades {
	namespace Obstaculos {
		class Lama : public Obstaculo {
		private:
			float multiplicadorVelocidade;
			float multiplicadorPulo;
		public:
			bool afetaInimigos() const override { return false; } 

			Lama(const sf::Vector2f pos, const sf::Vector2f tam = sf::Vector2f(100.0f, 30.0f));
			~Lama();
			void obstaculizar(Personagens::Personagem* p, sf::Vector2f ds) override;
			void salvar();
			void salvarDataBuffer();

		};
	}
}
