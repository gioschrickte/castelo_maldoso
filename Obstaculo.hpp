#pragma once
#include "Entidade.hpp"

namespace Entidade {
    namespace Obstaculo {
        class Obstaculo : public Entidade {
        public:
            Obstaculo(const sf::Vector2f pos, const sf::Vector2f tam, IDs::IDs id);
            ~Obstaculo();
            void atualizar() override;
            virtual void colisao(Entidade* outraEntidade, sf::Vector2f ds) override = 0;
        };
    }
}