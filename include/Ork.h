// Ork.hpp
#pragma once
#include "Inimigo.h"

namespace Entidades {
    namespace Personagens {
        namespace Inimigos {
            class Ork : public Inimigo {
            private:
                short nivelDificuldade = 2; // nivel de dificuldade do inimigo
            public:
                Ork(Jogadores::Jogador* j, const sf::Vector2f pos = sf::Vector2f(0.0f, 0.0f));
                void danificar(Jogadores::Jogador* pJog) override;



                void executar();
                void salvar();
                void salvarDataBuffer();
            };
        }
    }
}
