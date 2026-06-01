// InimigoMedio.hpp
#pragma once
#include "Inimigo.hpp"

namespace Entidades {
    namespace Personagens {
        namespace Inimigos {
            class InimigoMedio : public Inimigo {
            public:
                InimigoMedio(Jogadores::Jogador* j, const sf::Vector2f pos = sf::Vector2f(0.0f, 0.0f))
                    : Inimigo(j, pos, sf::Vector2f(60.0f, 60.0f), 150.0f)  // maior e mais rápido
                {
                    corpo.setFillColor(sf::Color::Magenta);
                }
                void danificar(Jogadores::Jogador* pJog) override
                {
                    std::cout << "InimigoMedio causou dano alto!\n";
                    // quando houver vida: pJog->receberDano(2);
                }
            };
        }
    }
}
