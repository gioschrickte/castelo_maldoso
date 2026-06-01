// FasePrimeira.cpp
#include "FasePrimeira.hpp"

Jogo::Fases::FasePrimeira::FasePrimeira(Entidades::Personagens::Jogadores::Jogador* jogador, Entidades::Personagens::Jogadores::Jogador* j2)
    : Fase(jogador, j2)
{
    criarInimigos();
    criarObstaculos();
}

Jogo::Fases::FasePrimeira::~FasePrimeira() {}

void Jogo::Fases::FasePrimeira::criarInimigos()
{
    using namespace Entidades::Personagens::Inimigos;
    for (int i = 0; i < 3; i++)
        adicionarInimigo(new InimigoFacil(jog1, sf::Vector2f(rand() % 700 + 50.0f, rand() % 500 + 50.0f)));
    for (int i = 0; i < 2; i++)
        adicionarInimigo(new InimigoMedio(jog1, sf::Vector2f(rand() % 700 + 50.0f, rand() % 500 + 50.0f)));
}

void Jogo::Fases::FasePrimeira::criarObstaculos()
{
    using namespace Entidades::Obstaculos;
    for (int i = 0; i < 3; i++)
        adicionarObstaculo(new Plataforma(sf::Vector2f(rand() % 1600 + 100.0f, rand() % 500 + 200.0f)));
    for (int i = 0; i < 3; i++)
        adicionarObstaculo(new Espinho(sf::Vector2f(rand() % 1600 + 100.0f, 858.0f))); // logo acima do chão (y=900)
}