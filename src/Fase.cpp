// Fase.cpp
#include "Fase.h"
#include "Entidade.h"
#include "GerenciadorColisoes.h"
#include "GerenciadorGrafico.h"
#include "InimigoFacil.h" 
#include "Plataforma.h" 
#include "Projetil.h"
#include <cstdlib>

#define MAX_INIMIGOS_FACEIS 4
#define MAX_PLATAFORMAS 5

Jogo::Fases::Fase::Fase(Entidades::Personagens::Jogadores::Jogador* jogador, Entidades::Personagens::Jogadores::Jogador* j2)
    : Ente(), jog1(jogador), jog2(j2), listaEntidade(),
    gerColisoes(Gerenciador::GerenciadorColisoes::getGerenciadorColisoes()),
    gerEventos(Gerenciador::GerenciadorEvento::getGerenciadorEvento()),
    chao(nullptr),
    pausado(false),
    resultado(ResultadoFase::JanelaFechada)
{
    criarChao();
   

    listaEntidade.addEntidade(jog1);
    if (jog2) listaEntidade.addEntidade(jog2);

    gerColisoes->setFase(this);
    gerColisoes->setJogador1(jog1);
    gerColisoes->setJogador2(jog2);   // jog2 pode ser nullptr (limpa ponteiro obsoleto)
    gerEventos->setJogador(jog1);
    gerEventos->setJogador2(jog2);     // idem
    gerEventos->setFase(this);
}

Jogo::Fases::Fase::~Fase()
{
    for (int i = 0; i < listaEntidade.getTam(); i++)
        delete listaEntidade[i];
    gerColisoes->limpar();
}

void Jogo::Fases::Fase::criarChao()
{
    chao = new Entidades::Chao(sf::Vector2f(0.0f, 750.0f), sf::Vector2f(pGG->getWindow()->getSize().x, 20.0f));
    listaEntidade.addEntidade(chao);
}

void Jogo::Fases::Fase::adicionarInimigo(Entidades::Personagens::Inimigos::Inimigo* i)
{
    i->setJogador2(jog2);   // segundo alvo para a IA (nullptr em 1 jogador)
    listaEntidade.addEntidade(i);
    gerColisoes->incluirInimigo(i);
}

void Jogo::Fases::Fase::adicionarObstaculo(Entidades::Obstaculos::Obstaculo* o)
{
    listaEntidade.addEntidade(o);
    gerColisoes->incluirObstaculo(o);
}

void Jogo::Fases::Fase::adicionarProjetil(Entidades::Projetil* p)
{
    listaEntidade.addEntidade(p);     // entra no loop de executar()/desenhar()
    gerColisoes->incluirProjetil(p);  // entra no set de projeteis (colisao com o jogador)
}

int Jogo::Fases::Fase::aleatorio(int minimo, int maximo)
{
    if (maximo <= minimo) return minimo;
    return minimo + rand() % (maximo - minimo + 1);
}

sf::Vector2f Jogo::Fases::Fase::posicaoAleatoria(float xMin, float xMax, float yMin, float yMax)
{
    float x = static_cast<float>(aleatorio(static_cast<int>(xMin), static_cast<int>(xMax)));
    float y = static_cast<float>(aleatorio(static_cast<int>(yMin), static_cast<int>(yMax)));
    return sf::Vector2f(x, y);
}

sf::Vector2f Jogo::Fases::Fase::posicaoInimigoAleatoria() const
{
    const float largura = static_cast<float>(pGG->getWindow()->getSize().x);
    const float chaoTopo = chao->getPosicao().y;   // y real do chÃ£o

    const float margem = 50.0f;
    const float xMin = margem;
    const float xMax = largura - margem;
    const float yMin = margem;
    const float yMax = chaoTopo - 100.0f;          // folga acima do chÃ£o
    return posicaoAleatoria(xMin, xMax, yMin, yMax);
}

sf::Vector2f Jogo::Fases::Fase::posicaoPlataformaAleatoria() const
{
    const float largura = static_cast<float>(pGG->getWindow()->getSize().x);
    const float chaoTopo = chao->getPosicao().y;

    const float margem = 100.0f;
    const float xMin = margem;
    const float xMax = largura - margem;

    const float plataformaYMin = 500.0f;
    const float plataformaYMax = chaoTopo - 150.0f;
    return posicaoAleatoria(xMin, xMax, plataformaYMin, plataformaYMax);
}

void Jogo::Fases::Fase::criarInimigosFaceis()
{
    using namespace Entidades::Personagens::Inimigos;
    int n = aleatorio(3, MAX_INIMIGOS_FACEIS);
    for (int i = 0; i < n; i++)
        adicionarInimigo(new InimigoFacil(jog1, posicaoInimigoAleatoria()));
}

void Jogo::Fases::Fase::criarPlataformas()
{
    using namespace Entidades::Obstaculos;

    const sf::Vector2f tam(200.0f, 20.0f);
    const float folga = 40.0f;               // espaÃ§o mÃ­nimo exigido entre plataformas
    const int  MAX_TENTATIVAS = 30;

    const float largura = static_cast<float>(pGG->getWindow()->getSize().x);
    const float chaoTopo = chao->getPosicao().y;
    const float xMin = 0.0f;
    const float xMax = largura - tam.x;
    const float yMin = 250.0f;
    const float yMax = chaoTopo - 150.0f;

    std::vector<sf::FloatRect> colocadas;    // o que jÃ¡ foi posicionado nesta fase

    int n = aleatorio(3, MAX_PLATAFORMAS);
    for (int i = 0; i < n; i++)
    {
        for (int t = 0; t < MAX_TENTATIVAS; t++)
        {
            sf::Vector2f pos = posicaoAleatoria(xMin, xMax, yMin, yMax);

            sf::FloatRect cand(pos.x - folga, pos.y - folga,
                tam.x + 2 * folga, tam.y + 2 * folga);

            bool livre = true;
            for (size_t k = 0; k < colocadas.size(); k++)
                if (cand.intersects(colocadas[k])) { livre = false; break; }

            if (livre)
            {
                colocadas.push_back(sf::FloatRect(pos.x, pos.y, tam.x, tam.y));
                adicionarObstaculo(new Plataforma(pos, tam));
                break;
            }
        }
        // se esgotar as tentativas sem achar lugar, simplesmente pula esta plataforma
    }
}

void Jogo::Fases::Fase::executar()
{

    cout << "LOOP DE EXECUTAR" << endl;
    while (pGG->verificaJanelaAberta()) {
        gerEventos->executar();                                   // 1. entrada
        
        
        if(!pausado)
        {
            for (int i = 0; i < listaEntidade.getTam(); i++)
            {
                if (!listaEntidade[i]->getAtiva()) continue; // nao executa IA/movimento de mortos
                cout << "Executando entidade: " << i << endl;
                listaEntidade[i]->executar();
            }
                      
        }                                  
        
        gerColisoes->executar();                                  // 3. colisÃµes corrigem / atualiza vida dos personagens
        pGG->limpaJanela();


        pGG->desenhaSprite(spriteFundo); 
        for (int i = 0; i < listaEntidade.getTam(); i++)
        {
            if(listaEntidade[i]->getAtiva())
                listaEntidade[i]->desenhar();                          // 4. desenha tudo
        }
        pGG->mostraElementos();

        // Fim de fase: a Principal le getResultado() para decidir o proximo passo.
        if (!haJogadorVivo())
        {
            resultado = ResultadoFase::JogadorMorreu;   // ambos mortos -> menu
            return;
        }
        if (!gerColisoes->haInimigosVivos())
        {
            resultado = ResultadoFase::FaseConcluida;    // fase limpa -> proxima fase
            return;
        }
    }
    resultado = ResultadoFase::JanelaFechada;            // saiu pelo fechamento da janela
}

void Jogo::Fases::Fase::SalvarTudo()
{
    //salvar o numero da fase
    
    listaEntidade.salvarEntidades();
}
