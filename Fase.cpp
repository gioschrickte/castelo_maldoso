// Fase.cpp
#include "Fase.hpp"
#include "GerenciadorColisoes.hpp"

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