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
    criarInimigosMedios();
}



void Jogo::Fases::FasePrimeira::criarInimigosMedios()
{
	using namespace Entidades::Personagens::Inimigos;
	int nMedios = aleatorio(3, MAX_INIMIGOS_MEDIOS);
	for (int i = 0; i < nMedios; i++)
		adicionarInimigo(new InimigoMedio(jog1, posicaoInimigoAleatoria()));
}

void Jogo::Fases::FasePrimeira::criarObstaculos()
{
    criarPlataformas();      // COMUM -> definido na base (Fase)
    criarEspinhos();   
}

void Jogo::Fases::FasePrimeira::criarEspinhos()
{
    using namespace Entidades::Obstaculos;
    // Específico da fase 1: espinhos rente ao chão.
    const float largura = static_cast<float>(pGG->getWindow()->getSize().x);
    const float chaoTopo = chao->getPosicao().y;
    const float margem = 100.0f;
    const float espinhoY = chaoTopo - 42.0f;   // mesmo encaixe do original (858 p/ chao em 900)

    int nEspinhos = aleatorio(3, MAX_ESPINHOS);
    for (int i = 0; i < nEspinhos; i++)
    {
        float x = static_cast<float>(aleatorio(static_cast<int>(margem), static_cast<int>(largura - margem)));
        adicionarObstaculo(new Espinho(sf::Vector2f(x, espinhoY)));
    }
}