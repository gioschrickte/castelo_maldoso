#pragma once
#include "Obstaculo.h"

namespace Entidades {
    namespace Obstaculos {
        class Plataforma : public Obstaculos::Obstaculo {
        public:
			bool afetaInimigos() const override { return true; } // Plataformas afetam inimigos, ou seja, eles tambÃ©m colidem com elas e sÃ£o empurrados para fora
            Plataforma(const sf::Vector2f pos, const sf::Vector2f tam = sf::Vector2f(200.0f, 20.0f));
            ~Plataforma();
			void resolverColisao(Personagens::Personagem* p, sf::Vector2f ds) override;
        };
    }
}
