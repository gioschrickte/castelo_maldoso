// Fase.cpp
#include "Fase.hpp"
#include "GerenciadorColisoes.hpp"
#include "InimigoFacil.hpp"   // a base agora cria os inimigos fáceis
#include "Plataforma.hpp"     // ... e as plataformas
#include <cstdlib>            // rand()

#define MAX_INIMIGOS_FACEIS 5
#define MAX_PLATAFORMAS 5

Jogo::Fases::Fase::Fase(Entidades::Personagens::Jogadores::Jogador* jogador, Entidades::Personagens::Jogadores::Jogador* j2)
    : Ente(), jog1(jogador), jog2(j2), listaEntidade(),
    gerColisoes(Gerenciador::GerenciadorColisoes::getGerenciadorColisoes()),
    gerEventos(Gerenciador::GerenciadorEvento::getGerenciadorEvento()),
    chao(nullptr)
{
    criarChao();                          // chão é comum -> criado na base

    listaEntidade.addEntidade(jog1);
    if (jog2) listaEntidade.addEntidade(jog2);

    gerColisoes->setFase(this);           // agregação bidirecional (só referência)
    gerColisoes->setJogador1(jog1);
    gerEventos->setJogador(jog1);

    // criarInimigos()/criarObstaculos() são chamados no construtor da DERIVADA,
    // e cada um deles chama os criadores comuns desta base.
}

Jogo::Fases::Fase::~Fase()
{
    for (int i = 0; i < listaEntidade.getTam(); i++)
        delete listaEntidade[i];
    gerColisoes->limpar();
}

void Jogo::Fases::Fase::criarChao()
{
    chao = new Entidades::Chao(sf::Vector2f(0.0f, 900.0f), sf::Vector2f(1920.0f, 20.0f));
    listaEntidade.addEntidade(chao);
}

void Jogo::Fases::Fase::adicionarInimigo(Entidades::Personagens::Inimigos::Inimigo* i)
{
    listaEntidade.addEntidade(i);
    gerColisoes->incluirInimigo(i);
}

void Jogo::Fases::Fase::adicionarObstaculo(Entidades::Obstaculos::Obstaculo* o)
{
    listaEntidade.addEntidade(o);
    gerColisoes->incluirObstaculo(o);
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
    const float chaoTopo = chao->getPosicao().y;   // y real do chão

    const float margem = 50.0f;
    const float xMin = margem;
    const float xMax = largura - margem;
    const float yMin = margem;
    const float yMax = chaoTopo - 100.0f;          // folga acima do chão
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
    int n = aleatorio(0, MAX_PLATAFORMAS);
    for (int i = 0; i < n; i++)
        adicionarObstaculo(new Plataforma(posicaoPlataformaAleatoria()));
}

void Jogo::Fases::Fase::executar()
{
    while (pGG->verificaJanelaAberta()) {
        gerEventos->executar();                                   // 1. entrada
        for (int i = 0; i < listaEntidade.getTam(); i++)
            listaEntidade[i]->executar();                         // 2. física/IA
        gerColisoes->executar();                                  // 3. colisões corrigem
        pGG->limpaJanela();
        for (int i = 0; i < listaEntidade.getTam(); i++)
            listaEntidade[i]->desenhar();                         // 4. desenha já corrigido
        pGG->mostraElementos();
    }
}