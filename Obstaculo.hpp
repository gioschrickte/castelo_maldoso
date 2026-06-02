#pragma once

#include "Jogador.hpp"

namespace Entidades {
    namespace Obstaculos {
        class Obstaculo : public Entidade{
        protected:
            bool danoso;        
        public:
			virtual bool afetaInimigos() const { return false; } // Por padrão, os obstáculos não afetam os inimigos, mas isso pode ser sobrescrito em classes derivadas

            Obstaculo(const sf::Vector2f pos, const sf::Vector2f tam, const IDs::IDs id);
            virtual ~Obstaculo();


            void executar();
			virtual void resolverColisao(Personagens::Personagem* p, sf::Vector2f ds) = 0; // Método para resolver a colisão, que pode ser implementado de forma diferente em cada tipo de obstáculo
        };
    }
}