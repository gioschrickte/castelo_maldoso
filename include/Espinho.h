// Espinho.hpp
#pragma once
#include "Obstaculo.h"

namespace Entidades {
    namespace Obstaculos {
        class Espinho : public Obstaculo {
        private:
            int dano = 1; // dano causado ao jogador
        public:
            bool afetaInimigos() const override { return false; } // sÃ³ atrapalha o jogador
            Espinho(const sf::Vector2f pos, const sf::Vector2f tam = sf::Vector2f(40.0f, 40.0f));
            ~Espinho();
            void resolverColisao(Personagens::Personagem* p, sf::Vector2f ds) override;
        };
    }
}
