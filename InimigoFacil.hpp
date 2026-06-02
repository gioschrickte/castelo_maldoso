// InimigoFacil.hpp
#pragma once
#include "Inimigo.hpp"

namespace Entidades {
    namespace Personagens {
        namespace Inimigos {
            class InimigoFacil : public Inimigo {
            private:
                short moveAleatorio;
            public:
                InimigoFacil(Jogadores::Jogador* j,
                    const sf::Vector2f pos = sf::Vector2f(0.0f, 0.0f));
                void danificar(Jogadores::Jogador* pJog) override;
                void persegueJogador(sf::Vector2f posJogador, sf::Vector2f posInimigo);
                void movAleatorio();
                void executar();
            };
        }
    }
}
