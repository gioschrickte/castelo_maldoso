// InimigoMedio.hpp
#pragma once
#include "Inimigo.h"

namespace Entidades {
    namespace Personagens {
        namespace Inimigos {
            class InimigoMedio : public Inimigo {
            public:
                InimigoMedio(Jogadores::Jogador* j, const sf::Vector2f pos = sf::Vector2f(0.0f, 0.0f));
                void danificar(Jogadores::Jogador* pJog) override;

                void executar();
            };
        }
    }
}
