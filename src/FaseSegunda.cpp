// FaseSegunda.cpp
#include "FaseSegunda.h"
#include "Mago.h"
#include "Projetil.h"
#define MAX_LAMA 5
#define MAX_MAGOS 5

Jogo::Fases::FaseSegunda::FaseSegunda(Entidades::Personagens::Jogadores::Jogador* jogador, Entidades::Personagens::Jogadores::Jogador* j2)
    : Fase(jogador, j2), maxLama(MAX_LAMA), maxMagos(MAX_MAGOS)
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

	numFase = 2;
}

Jogo::Fases::FaseSegunda::FaseSegunda(Entidades::Personagens::Jogadores::Jogador* jogador, Entidades::Personagens::Jogadores::Jogador* j2, bool carregando)
    : Fase(jogador, j2, carregando), maxLama(MAX_LAMA), maxMagos(MAX_MAGOS)
{
    texturaFundo = pGG->carregarTextura("assets/fundo.png");
    spriteFundo.setTexture(texturaFundo);
    sf::Vector2u tamJanela = pGG->getWindow()->getSize();
    sf::Vector2u tamTextura = texturaFundo.getSize();
    spriteFundo.setScale(
    (float)tamJanela.x / tamTextura.x,
    (float)tamJanela.y / tamTextura.y
    );

    numFase = 2;

    carregarEntidades();   // recria inimigos/obstaculos a partir dos .txt de cada tipo
}

Jogo::Fases::FaseSegunda::~FaseSegunda() {}

void Jogo::Fases::FaseSegunda::criarInimigos()
{
    criarInimigosFaceis();   // COMUM -> definido na base (Fase)
    criarMago();
}

void Jogo::Fases::FaseSegunda::criarObstaculos()
{
    criarPlataformas(); 
    criarLama();
}

void Jogo::Fases::FaseSegunda::criarLama()
{
	using namespace Entidades::Obstaculos;
	
	const float largura = static_cast<float>(pGG->getWindow()->getSize().x);
	const float chaoTopo = chao->getPosicao().y;
	const float margem = 100.0f;
	const float lamaY = chaoTopo - 30.0f;
	int nLamas = aleatorio(3, maxLama);
	for (int i = 0; i < nLamas; i++)
	{
		float x = static_cast<float>(aleatorio(static_cast<int>(margem), static_cast<int>(largura - margem)));
		adicionarObstaculo(new Lama(sf::Vector2f(x, lamaY)));
	}
}

void Jogo::Fases::FaseSegunda::criarMago()
{
    int nMagos = aleatorio(3, maxMagos);
    for(int i = 0; i < nMagos; i++)
    {
        Entidades::Personagens::Inimigos::Mago* mago = new Entidades::Personagens::Inimigos::Mago(jog1, posicaoInimigoAleatoria());
        Entidades::Projetil* projetil = new Entidades::Projetil();
        mago->setProjetil(projetil);
        adicionarInimigo(mago);
        adicionarProjetil(projetil);
    }
}
