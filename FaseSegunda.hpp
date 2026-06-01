// FaseSegunda.hpp
#pragma once
#include "Fase.hpp"
#include "InimigoFacil.hpp"
#include "InimigoMedio.hpp"
// #include "Chefao.hpp" (a implementar)
#include "Plataforma.hpp"
#include "Espinho.hpp"
// #include "ObstaculoDificil.hpp" (a implementar)

namespace Jogo {
    namespace Fases {
        class FaseSegunda : public Fase {
        public:
            FaseSegunda(Entidades::Personagens::Jogadores::Jogador* jogador,
                Entidades::Personagens::Jogadores::Jogador* j2 = nullptr);
            ~FaseSegunda();
            void criarInimigos()   override;
            void criarObstaculos() override;
        };
    }
}