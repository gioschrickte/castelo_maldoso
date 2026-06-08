// FaseSegunda.hpp
#pragma once
#include "Fase.h"
#include "InimigoFacil.h"
#include "InimigoMedio.h"
// #include "Chefao.h" (a implementar)
#include "Plataforma.h"
#include "Lama.h"

namespace Jogo {
    namespace Fases {
        class FaseSegunda : public Fase {
        private:
            int numeroFase = 2; // numero identificador da fase
        public:
            FaseSegunda(Entidades::Personagens::Jogadores::Jogador* jogador,
                Entidades::Personagens::Jogadores::Jogador* j2 = nullptr);
            ~FaseSegunda();
            void criarInimigos()   override;
            void criarObstaculos() override;
            void criarLama();
            void criarChefao();
			//void criarChefao();
        };
    }
}
