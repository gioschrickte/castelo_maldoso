#pragma once
#include "Obstaculo.hpp"

namespace Entidades {
    namespace Obstaculos {
        class Plataforma : public Obstaculos::Obstaculo {
        public:
            Plataforma(const sf::Vector2f pos, const sf::Vector2f tam = sf::Vector2f(200.0f, 20.0f));
            ~Plataforma();
            void colidir(Entidade* outraEntidade, sf::Vector2f ds);
        };
    }
}