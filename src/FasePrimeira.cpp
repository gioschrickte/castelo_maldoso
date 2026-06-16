// FasePrimeira.cpp
#include "FasePrimeira.h"
#include <cstdlib>   // rand()

#define MAX_INIMIGOS_MEDIOS 3
#define MAX_EXPINHOS 5


Jogo::Fases::FasePrimeira::FasePrimeira(Entidades::Personagens::Jogadores::Jogador* jogador, Entidades::Personagens::Jogadores::Jogador* j2)
    : Fase(jogador, j2),
    maxInimigosMedios(MAX_INIMIGOS_MEDIOS),
    maxEspinhos(MAX_EXPINHOS)
{
    criarInimigos();
    criarObstaculos();
    
    texturaFundo = pGG->carregarTextura("assets/fundo.png");
    spriteFundo.setTexture(texturaFundo);
    sf::Vector2u tamJanela = pGG->getWindow()->getSize();
    sf::Vector2u tamTextura = texturaFundo.getSize();
    spriteFundo.setScale(
    (float)tamJanela.x / tamTextura.x,
    (float)tamJanela.y / tamTextura.y
    );

    numFase = 1;
}

Jogo::Fases::FasePrimeira::FasePrimeira(Entidades::Personagens::Jogadores::Jogador* jogador, Entidades::Personagens::Jogadores::Jogador* j2, bool carregando)
    : Fase(jogador, j2, carregando),
    maxInimigosMedios(MAX_INIMIGOS_MEDIOS),
    maxEspinhos(MAX_EXPINHOS)
{
    texturaFundo = pGG->carregarTextura("assets/fundo.png");
    spriteFundo.setTexture(texturaFundo);
    sf::Vector2u tamJanela = pGG->getWindow()->getSize();
    sf::Vector2u tamTextura = texturaFundo.getSize();
    spriteFundo.setScale(
    (float)tamJanela.x / tamTextura.x,
    (float)tamJanela.y / tamTextura.y
    );

    numFase = 1;

    carregarEntidades("save.txt");   // recria inimigos/obstaculos a partir do arquivo
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
	int nMedios = aleatorio(3, maxInimigosMedios);
	for (int i = 0; i < nMedios; i++)
		adicionarInimigo(new Ork(jog1, posicaoInimigoAleatoria()));
}

void Jogo::Fases::FasePrimeira::criarObstaculos()
{
    criarPlataformas();      // COMUM -> definido na base (Fase)
    criarEspinhos();   
}

void Jogo::Fases::FasePrimeira::criarEspinhos()
{
    using namespace Entidades::Obstaculos;
    // EspecÃ­fico da fase 1: espinhos rente ao chÃ£o.
    const float largura = static_cast<float>(pGG->getWindow()->getSize().x);
    const float chaoTopo = chao->getPosicao().y;
    const float margem = 100.0f;
    const float espinhoY = chaoTopo - 35.0f; 

    int nEspinhos = aleatorio(3, maxEspinhos);
    for (int i = 0; i < nEspinhos; i++)
    {
        float x = static_cast<float>(aleatorio(static_cast<int>(margem), static_cast<int>(largura - margem)));
        adicionarObstaculo(new Espinho(sf::Vector2f(x, espinhoY)));
    }
}
