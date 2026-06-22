#pragma once

#include "Jogador.h"

namespace Entidades {
    namespace Obstaculos {
        class Obstaculo : public Entidade{
        protected:
            bool danoso;        
        public:
			virtual bool afetaInimigos() const { return false; } 

            Obstaculo(const sf::Vector2f pos, const sf::Vector2f tam, const IDs::IDs id);
            virtual ~Obstaculo();


            void executar();
			virtual void obstaculizar(Personagens::Personagem* p, sf::Vector2f ds) = 0; 
            virtual void salvar() = 0;
            virtual void salvarDataBuffer();
        };
    }
}
