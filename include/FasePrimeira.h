// FasePrimeira.hpp
#pragma once
#include "Fase.h"
#include "InimigoFacil.h"
#include "InimigoMedio.h"
#include "Plataforma.h"
#include "Espinho.h"

namespace Jogo {
    namespace Fases {
        class FasePrimeira : public Fase {
        private:
            int numeroFase = 1; // numero identificador da fase
        public:
            FasePrimeira(Entidades::Personagens::Jogadores::Jogador* jogador,
                Entidades::Personagens::Jogadores::Jogador* j2 = nullptr);
            ~FasePrimeira();
            void criarInimigos()   override;
            void criarObstaculos() override;
            void criarInimigosMedios();
            void criarEspinhos();
        };
    }
}
