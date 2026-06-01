// Espinho.hpp
#pragma once
#include "Obstaculo.hpp"

namespace Entidades {
    namespace Obstaculos {
        class Espinho : public Obstaculo {
        public:
            bool afetaInimigos() const override { return false; } // só atrapalha o jogador
            Espinho(const sf::Vector2f pos, const sf::Vector2f tam = sf::Vector2f(40.0f, 40.0f));
            ~Espinho();
            void resolverColisao(Personagens::Personagem* p, sf::Vector2f ds) override;
        };
    }
}