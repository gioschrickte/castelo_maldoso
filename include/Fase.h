// Fase.hpp
#pragma once
#include "ListaEntidade.h"
#include "Inimigo.h"
#include "Jogador.h"
#include "Obstaculo.h"
#include "chao.h"
#include "GerenciadorEventos.h"


namespace Gerenciador {class GerenciadorColisoes;}
namespace Entidades { class Projetil; } // forward declare

namespace Jogo {
    namespace Fases {
        // Como a fase terminou, lido pela Principal para decidir o proximo passo
        enum class ResultadoFase {
            JanelaFechada,   // o jogador fechou a janela
            JogadorMorreu,   // nao ha jogador vivo  -> volta ao menu
            FaseConcluida    // nao ha inimigo vivo  -> proxima fase (ou menu, se for a ultima)
        };

        class Fase : public Jogo::Ente {
        protected:
            Entidades::Personagens::Jogadores::Jogador* jog1;
            Entidades::Personagens::Jogadores::Jogador* jog2;
            Lista::ListaEntidade listaEntidade;
            Gerenciador::GerenciadorColisoes* gerColisoes;
            Gerenciador::GerenciadorEvento* gerEventos;
            Entidades::Chao* chao;

            int numFase;

            void inicializar();                            // setup comum as construtoras (chao + jogadores + gerenciadores)

            // Carga do save: um metodo por tipo (cada um le o seu proprio .txt), sem switch.
            void carregarEntidades();                      // orquestra: chama os carregarXxx() abaixo
            void carregarJogadores();
            void carregarZumbis();
            void carregarOrks();
            void carregarMagos();
            void carregarProjeteis();                      // recria os projeteis e os associa aos magos
            void carregarPlataformas();
            void carregarEspinhos();
            void carregarLamas();
            void limparArquivosEntidades();                // trunca os .txt de cada tipo (usado ao salvar)

            void criarChao();                              // comum a todas as fases
            void criarInimigosFaceis();
            void criarPlataformas();

            // Ajuda pra fazer a aleatoriedade
            static int aleatorio(int minimo, int maximo);
            static sf::Vector2f posicaoAleatoria(float xMin, float xMax, float yMin, float yMax);
            sf::Vector2f posicaoInimigoAleatoria() const;
            sf::Vector2f posicaoPlataformaAleatoria() const;

            // true se ao menos um jogador continua vivo (co-op: game over so com os dois mortos)
            bool haJogadorVivo() const { return jog1->getAtiva() || (jog2 && jog2->getAtiva()); }

            void adicionarInimigo(Entidades::Personagens::Inimigos::Inimigo* i);
            void adicionarObstaculo(Entidades::Obstaculos::Obstaculo* o);
            void adicionarProjetil(Entidades::Projetil* p); // na lista de entidades + no gerenciador

            sf::Texture texturaFundo;
            sf::Sprite  spriteFundo;

            bool pausado;
            ResultadoFase resultado;   // preenchido por executar(), lido pela Principal
        public:
            Fase(Entidades::Personagens::Jogadores::Jogador* jogador,
                Entidades::Personagens::Jogadores::Jogador* j2 = nullptr);
            // Construtora usada ao CARREGAR um jogo salvo: faz o setup comum mas
            // nao gera inimigos/obstaculos aleatorios (eles vem do arquivo).
            Fase(Entidades::Personagens::Jogadores::Jogador* jogador,
                Entidades::Personagens::Jogadores::Jogador* j2, bool carregando);
            virtual ~Fase();

            void executar() override;                      // loop comum a todas as fases
            ResultadoFase getResultado() const { return resultado; }
            Entidades::Chao* getChao() { return chao; }

            virtual void criarInimigos() = 0;            // cada fase acrescenta os seus
            virtual void criarObstaculos() = 0;
            void SalvarTudo();
            void setPausado(bool p)
            {
                pausado = p;
            }
            bool getPausado()
            {
                return pausado;
            }
        };
    }
}
