#pragma once
#include "Obstaculo.hpp"

namespace Entidade {
    namespace Obstaculo {
        class Plataforma : public Obstaculo {
        public:
            Plataforma(const sf::Vector2f pos, const sf::Vector2f tam = sf::Vector2f(200.0f, 20.0f));
            ~Plataforma();
            void colisao(Entidade* outraEntidade, sf::Vector2f ds) override;
        };
    }
}