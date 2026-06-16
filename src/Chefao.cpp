#include "Chefao.h"
#include "Projetil.h"
#include "Jogador.h"
#include <cmath>
#include <cstdlib>
#include <fstream>

#define RAIO_CHEFAO   400.0f
#define COOLDOWN_TIRO 1.5f

Entidades::Personagens::Inimigos::Chefao::Chefao(Jogadores::Jogador* j, const sf::Vector2f pos)
	: Inimigo(j, pos, sf::Vector2f(100.0f, 100.0f), 150.0f),
	forca(5), projetil(nullptr), projetilEstavaAtivo(false), moveAleatorio(0)
{
	corpo.setFillColor(sf::Color::Yellow);
	textura = pGG->carregarTextura("assets/mago.png");
	sprite.setTexture(textura);

	// Ajusta a escala do sprite para cobrir exatamente o corpo (50x50)
	sf::Vector2u tSz = textura.getSize();
	if (tSz.x > 0 && tSz.y > 0)
	{
		sprite.setScale(100.0f / tSz.x, 100.0f / tSz.y);
	}

	sprite.setPosition(pos);
	temSprite = true;

	dano = 3.0f;
	vidaMax = 20.0f;
	vida = vidaMax;
}

Entidades::Personagens::Inimigos::Chefao::~Chefao() {}

void Entidades::Personagens::Inimigos::Chefao::danificar(Jogadores::Jogador* pJog)
{
	if (!podeHitar()) return;
	pJog->tomarDano(dano);
	std::cout << "O chefao encostou no jogador! (dano=" << dano << ")\n";
	std::cout << "Vida do jogador: " << pJog->getVida() << " / " << pJog->getVidaMax() << std::endl;
}


void Entidades::Personagens::Inimigos::Chefao::persegueJogador(sf::Vector2f posJogador, sf::Vector2f posChefao)
{
	if (posJogador.x - posChefao.x > 0.0f) andar(false);
	else                                   andar(true);
}

void Entidades::Personagens::Inimigos::Chefao::movAleatorio()
{
	if (moveAleatorio == 0)      andar(false);
	else if (moveAleatorio == 1) andar(true);
	else                         parar();

	if (relogioAleatorio.getElapsedTime().asSeconds() >= 1.0f)
	{
		moveAleatorio = rand() % 4;
		relogioAleatorio.restart();
	}
}

void Entidades::Personagens::Inimigos::Chefao::executar()
{
	float dt = calcularDt();

	sf::Vector2f posJogador = jogador->getCorpo().getPosition();
	sf::Vector2f posChefao = corpo.getPosition();

	if (fabs(posJogador.x - posChefao.x) <= RAIO_CHEFAO &&
		fabs(posJogador.y - posChefao.y) <= RAIO_CHEFAO)
		persegueJogador(posJogador, posChefao);
	else
		movAleatorio();

	if (podeAndar) atualizarX(dt);
	atualizarY(dt);

	atualizarTiro();
}

void Entidades::Personagens::Inimigos::Chefao::atualizarTiro()
{
	if (!projetil) return;

	bool ativoAgora = projetil->estaAtivo();

	if (!ativoAgora)
	{
		if (projetilEstavaAtivo)
		{
			relogioTiro.restart();
		}
		else if (relogioTiro.getElapsedTime().asSeconds() >= COOLDOWN_TIRO)
		{
			sf::Vector2f centroChefao = corpo.getPosition() + corpo.getSize() / 2.0f;
			sf::Vector2f centroJog = jogador->getCorpo().getPosition()
				+ jogador->getCorpo().getSize() / 2.0f;
			projetil->lancar(centroChefao, centroJog);
		}
	}

	projetilEstavaAtivo = ativoAgora;
}

void Entidades::Personagens::Inimigos::Chefao::salvar()
{
	buffer.str("");
	buffer.clear();
	salvarDataBuffer();
	cout << "[SALVAR] " << buffer.str() << endl;//debug
	ofstream arquivo("save.txt", ios::app);
	
	if (!arquivo.is_open())//debug
    {
        cout << "[ERRO] nao foi possivel abrir o arquivo!" << endl;
        return;
    }

	arquivo << buffer.str() << "\n";
	arquivo.close();
	 
	cout << "[SALVAR] gravado com sucesso!" << endl;//debug
}

void Entidades::Personagens::Inimigos::Chefao::salvarDataBuffer()
{
	Entidades::Personagens::Inimigos::Inimigo::salvarDataBuffer();
	// mais nada pra salvard
}

