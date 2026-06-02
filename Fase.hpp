// Fase.hpp
#pragma once
#include "ListaEntidade.hpp"
#include "Inimigo.hpp"
#include "Jogador.hpp"
#include "Obstaculo.hpp"
#include "chao.hpp"
#include "GerenciadorEventos.hpp"

namespace Gerenciador { class GerenciadorColisoes; }

namespace Jogo {
    namespace Fases {
        class Fase : public Jogo::Ente {
        protected:
            Entidades::Personagens::Jogadores::Jogador* jog1;
            Entidades::Personagens::Jogadores::Jogador* jog2;
            Lista::ListaEntidade listaEntidade;
            Gerenciador::GerenciadorColisoes* gerColisoes;
            Gerenciador::GerenciadorEvento* gerEventos;
            Entidades::Chao* chao;

            void criarChao();                              // comum a todas as fases
            void criarInimigosFaceis();
            void criarPlataformas();

            // Ajuda pra fazer a aleatoriedade
            static int aleatorio(int minimo, int maximo);
            static sf::Vector2f posicaoAleatoria(float xMin, float xMax, float yMin, float yMax);
            sf::Vector2f posicaoInimigoAleatoria() const;
            sf::Vector2f posicaoPlataformaAleatoria() const;

            void adicionarInimigo(Entidades::Personagens::Inimigos::Inimigo* i);
            void adicionarObstaculo(Entidades::Obstaculos::Obstaculo* o);
        public:
            Fase(Entidades::Personagens::Jogadores::Jogador* jogador,
                Entidades::Personagens::Jogadores::Jogador* j2 = nullptr);
            virtual ~Fase();

            void executar() override;                      // loop comum a todas as fases
            Entidades::Chao* getChao() { return chao; }

            virtual void criarInimigos() = 0;            // cada fase acrescenta os seus
            virtual void criarObstaculos() = 0;
        };
    }
}