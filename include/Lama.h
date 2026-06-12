#pragma once
#include "Obstaculo.h"

namespace Entidades {
	namespace Obstaculos {
		class Lama : public Obstaculo {
		private:
			float multiplicadorVelocidade;
			float multiplicadorPulo;
		public:
			bool afetaInimigos() const override { return false; } // meio q o zumbi atravessa a lama d boa sla

			Lama(const sf::Vector2f pos, const sf::Vector2f tam = sf::Vector2f(100.0f, 30.0f));
			~Lama();
			void resolverColisao(Personagens::Personagem* p, sf::Vector2f ds) override;
			void salvar();
			void salvarDataBuffer();

		};
	}
}
