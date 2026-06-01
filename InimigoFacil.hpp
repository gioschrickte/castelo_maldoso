// InimigoFacil.hpp
#pragma once
#include "Inimigo.hpp"

namespace Entidades {
    namespace Personagens {
        namespace Inimigos {
            class InimigoFacil : public Inimigo {
            public:
                InimigoFacil(Jogadores::Jogador* j, const sf::Vector2f pos = sf::Vector2f(0.0f, 0.0f))
                    : Inimigo(j, pos, sf::Vector2f(50.0f, 50.0f), 90.0f)  // mais lento e menor
                {
                    corpo.setFillColor(sf::Color::Red);
                }
                void danificar(Jogadores::Jogador* pJog) override
                {
                    std::cout << "InimigoFacil causou dano leve!\n";
                    // quando houver vida: pJog->receberDano(1);
                }
            };
        }
    }
}