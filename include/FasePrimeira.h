// FasePrimeira.hpp
#pragma once
#include "Fase.h"
#include "Zumbi.h"
#include "Ork.h"
#include "Plataforma.h"
#include "Espinho.h"

namespace Jogo {
    namespace Fases {
        class FasePrimeira : public Fase {
        private:
            int numeroFase = 1; // numero identificador da fase
            const int maxInimigosMedios;
            const int maxEspinhos;
        protected:
           
        public:
            FasePrimeira(Entidades::Personagens::Jogadores::Jogador* jogador,
                Entidades::Personagens::Jogadores::Jogador* j2 = nullptr);
            // Construtora de carga: recria a fase a partir do arquivo de save.
            FasePrimeira(Entidades::Personagens::Jogadores::Jogador* jogador,
                Entidades::Personagens::Jogadores::Jogador* j2, bool carregando);
            ~FasePrimeira();
            void criarInimigos()   override;
            void criarObstaculos() override;
            void criarInimigosMedios();
            void criarEspinhos();
        };
    }
}
