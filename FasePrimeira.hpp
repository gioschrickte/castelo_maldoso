// FasePrimeira.hpp
#pragma once
#include "Fase.hpp"
#include "InimigoFacil.hpp"
#include "InimigoMedio.hpp"
#include "Plataforma.hpp"
#include "Espinho.hpp"

namespace Jogo {
    namespace Fases {
        class FasePrimeira : public Fase {
        public:
            FasePrimeira(Entidades::Personagens::Jogadores::Jogador* jogador,
                Entidades::Personagens::Jogadores::Jogador* j2 = nullptr);
            ~FasePrimeira();
            void criarInimigos()   override;
            void criarObstaculos() override;
        };
    }
}