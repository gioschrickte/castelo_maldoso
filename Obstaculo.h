#pragma once

#include "Jogador.h"

namespace Entidades {
    namespace Obstaculos {
        class Obstaculo : public Entidade{
        protected:
            bool danoso;        
        public:
			virtual bool afetaInimigos() const { return false; } // Por padrÃ£o, os obstÃ¡culos nÃ£o afetam os inimigos, mas isso pode ser sobrescrito em classes derivadas

            Obstaculo(const sf::Vector2f pos, const sf::Vector2f tam, const IDs::IDs id);
            virtual ~Obstaculo();


            void executar();
			virtual void resolverColisao(Personagens::Personagem* p, sf::Vector2f ds) = 0; // MÃ©todo para resolver a colisÃ£o, que pode ser implementado de forma diferente em cada tipo de obstÃ¡culo
        };
    }
}
