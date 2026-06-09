// FaseSegunda.cpp
#include "FaseSegunda.h"
#include "Chefao.h"
#include "Projetil.h"
#define MAX_LAMA 5

Jogo::Fases::FaseSegunda::FaseSegunda(Entidades::Personagens::Jogadores::Jogador* jogador, Entidades::Personagens::Jogadores::Jogador* j2)
    : Fase(jogador, j2)
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
}

Jogo::Fases::FaseSegunda::~FaseSegunda() {}

void Jogo::Fases::FaseSegunda::criarInimigos()
{
    criarInimigosFaceis();   // COMUM -> definido na base (Fase)
    criarChefao();
}

void Jogo::Fases::FaseSegunda::criarObstaculos()
{
    criarPlataformas(); 
    criarLama();
}

void Jogo::Fases::FaseSegunda::criarLama()
{
	using namespace Entidades::Obstaculos;
	// EspecÃ­fico da fase 2: lama rente ao chÃ£o.
	const float largura = static_cast<float>(pGG->getWindow()->getSize().x);
	const float chaoTopo = chao->getPosicao().y;
	const float margem = 100.0f;
	const float lamaY = chaoTopo - 30.0f;
	int nLamas = aleatorio(3, MAX_LAMA);
	for (int i = 0; i < nLamas; i++)
	{
		float x = static_cast<float>(aleatorio(static_cast<int>(margem), static_cast<int>(largura - margem)));
		adicionarObstaculo(new Lama(sf::Vector2f(x, lamaY)));
	}
}

void Jogo::Fases::FaseSegunda::criarChefao()
{
	Entidades::Personagens::Inimigos::Chefao* chefao = new Entidades::Personagens::Inimigos::Chefao(jog1, posicaoInimigoAleatoria());
	Entidades::Projetil* projetil = new Entidades::Projetil();
	chefao->setProjetil(projetil);
	adicionarInimigo(chefao);
	adicionarProjetil(projetil);
}
