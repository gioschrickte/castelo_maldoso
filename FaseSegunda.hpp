// FaseSegunda.hpp
#pragma once
#include "Fase.hpp"
#include "InimigoFacil.hpp"
#include "InimigoMedio.hpp"
// #include "Chefao.hpp" (a implementar)
#include "Plataforma.hpp"
#include "Lama.hpp"

namespace Jogo {
    namespace Fases {
        class FaseSegunda : public Fase {
        public:
            FaseSegunda(Entidades::Personagens::Jogadores::Jogador* jogador,
                Entidades::Personagens::Jogadores::Jogador* j2 = nullptr);
            ~FaseSegunda();
            void criarInimigos()   override;
            void criarObstaculos() override;
            void criarLama();
			//void criarChefao();
        };
    }
}