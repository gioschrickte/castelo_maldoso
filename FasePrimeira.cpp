// FasePrimeira.cpp
#include "FasePrimeira.hpp"
#include <cstdlib>   // rand()

namespace {
    // Limites ESPECÍFICOS da fase 1 (os comuns ficam na base, em Fase.cpp).
    const int MAX_INIMIGOS_MEDIOS = 3;
    const int MAX_ESPINHOS = 5;
}

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

    criarInimigosFaceis();   // COMUM -> definido na base (Fase)

    // Específico da fase 1: inimigos médios.
    int nMedios = aleatorio(0, MAX_INIMIGOS_MEDIOS);
    for (int i = 0; i < nMedios; i++)
        adicionarInimigo(new InimigoMedio(jog1, posicaoInimigoAleatoria()));
}

void Jogo::Fases::FasePrimeira::criarObstaculos()
{
    using namespace Entidades::Obstaculos;

    criarPlataformas();      // COMUM -> definido na base (Fase)

    // Específico da fase 1: espinhos rente ao chão.
    const float largura = static_cast<float>(pGG->getWindow()->getSize().x);
    const float chaoTopo = chao->getPosicao().y;
    const float margem = 100.0f;
    const float espinhoY = chaoTopo - 42.0f;   // mesmo encaixe do original (858 p/ chao em 900)

    int nEspinhos = aleatorio(0, MAX_ESPINHOS);
    for (int i = 0; i < nEspinhos; i++)
    {
        float x = static_cast<float>(aleatorio(static_cast<int>(margem), static_cast<int>(largura - margem)));
        adicionarObstaculo(new Espinho(sf::Vector2f(x, espinhoY)));
    }
}