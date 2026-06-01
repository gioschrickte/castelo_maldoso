// FaseSegunda.cpp
#include "FaseSegunda.hpp"

Jogo::Fases::FaseSegunda::FaseSegunda(Entidades::Personagens::Jogadores::Jogador* jogador, Entidades::Personagens::Jogadores::Jogador* j2)
    : Fase(jogador, j2)
{
    criarInimigos();
    criarObstaculos();
}

Jogo::Fases::FaseSegunda::~FaseSegunda() {}

void Jogo::Fases::FaseSegunda::criarInimigos()
{
    using namespace Entidades::Personagens::Inimigos;
    // "alterna entre um desses": aqui troco InimigoMedio e (futuro) Chefao
    for (int i = 0; i < 6; i++) {
        sf::Vector2f pos(rand() % 700 + 50.0f, rand() % 500 + 50.0f);
        if (i % 2 == 0) adicionarInimigo(new InimigoMedio(jog1, pos));
        else            adicionarInimigo(new InimigoFacil(jog1, pos)); // troque por new Chefao(jog1, pos)
    }
}

void Jogo::Fases::FaseSegunda::criarObstaculos()
{
    using namespace Entidades::Obstaculos;
    for (int i = 0; i < 6; i++) {
        if (i % 2 == 0) adicionarObstaculo(new Espinho(sf::Vector2f(rand() % 1600 + 100.0f, 858.0f)));
        else            adicionarObstaculo(new Plataforma(sf::Vector2f(rand() % 1600 + 100.0f, rand() % 500 + 200.0f)));
    }
}