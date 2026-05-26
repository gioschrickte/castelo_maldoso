#pragma once

#include "Jogador.hpp"

namespace Entidades {
    namespace Obstaculos {
        class Obstaculo : public Entidade {
        private:
            bool danoso;
        public:
            Obstaculo(const sf::Vector2f pos, const sf::Vector2f tam);
            ~Obstaculo();
            void executar();
            virtual void obstaculizar(Personagens::Jogadores::Jogador* pjog) {}
        };
    }
}