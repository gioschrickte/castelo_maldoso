// Zumbi.hpp
#pragma once
#include "Inimigo.h"

namespace Entidades {
    namespace Personagens {
        namespace Inimigos {
            class Zumbi : public Inimigo {
            private:
                short moveAleatorio;
            public:
                Zumbi(Jogadores::Jogador* j,
                    const sf::Vector2f pos = sf::Vector2f(0.0f, 0.0f));
                ~Zumbi();
                void danificar(Jogadores::Jogador* pJog) override;
                void persegueJogador(sf::Vector2f posJogador, sf::Vector2f posInimigo);
                void movAleatorio();
                void executar();
                void salvar();
                void salvarDataBuffer();
            };
        }
    }
}
