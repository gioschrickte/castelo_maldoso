#include "Mago.h"
#include "Projetil.h"
#include "Jogador.h"
#include <cmath>
#include <cstdlib>
#include <fstream>

#define RAIO_MAGO   400.0f
#define COOLDOWN_TIRO 1.5f
#define FATOR_VEL_LENTIDAO  0.4f   // jogador anda a 40% da velocidade
#define DURACAO_LENTIDAO    3.0f   // durante 3 segundos

Entidades::Personagens::Inimigos::Mago::Mago(Jogadores::Jogador* j, const sf::Vector2f pos)
	: Inimigo(j, pos, sf::Vector2f(100.0f, 100.0f), 150.0f, IDs::IDs::mago),
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

Entidades::Personagens::Inimigos::Mago::~Mago() {}

void Entidades::Personagens::Inimigos::Mago::danificar(Jogadores::Jogador* pJog)
{
	if (!podeHitar()) return;
	pJog->tomarDano(dano);

	// Algoritmo do Chefao (Mago): alem do dano, lanca um feitico que deixa o jogador LENTO por
	// alguns segundos (reaproveita o multiplicadorVel da classe Personagem; o pulo fica intacto).
	pJog->aplicarLentidaoTemporaria(FATOR_VEL_LENTIDAO, 1.0f, DURACAO_LENTIDAO);

	std::cout << "O mago enfeiticou o jogador (lentidao)! (dano=" << dano << ")\n";
	std::cout << "Vida do jogador: " << pJog->getVida() << " / " << pJog->getVidaMax() << std::endl;
}


void Entidades::Personagens::Inimigos::Mago::persegueJogador(sf::Vector2f posJogador, sf::Vector2f posMago)
{
	if (posJogador.x - posMago.x > 0.0f) andar(false);
	else                                   andar(true);
}

void Entidades::Personagens::Inimigos::Mago::movAleatorio()
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

void Entidades::Personagens::Inimigos::Mago::executar()
{
	float dt = calcularDt();

	sf::Vector2f posJogador = getAlvo()->getCorpo().getPosition();
	sf::Vector2f posMago = corpo.getPosition();

	if (fabs(posJogador.x - posMago.x) <= RAIO_MAGO &&
		fabs(posJogador.y - posMago.y) <= RAIO_MAGO)
		persegueJogador(posJogador, posMago);
	else
		movAleatorio();

	if (podeAndar) atualizarX(dt);
	atualizarY(dt);

	atualizarTiro();
}

void Entidades::Personagens::Inimigos::Mago::atualizarTiro()
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
			sf::Vector2f centroMago = corpo.getPosition() + corpo.getSize() / 2.0f;
			Entidades::Personagens::Jogadores::Jogador* alvo = getAlvo();
			sf::Vector2f centroJog = alvo->getCorpo().getPosition()
				+ alvo->getCorpo().getSize() / 2.0f;
			projetil->lancar(centroMago, centroJog);
		}
	}

	projetilEstavaAtivo = ativoAgora;
}

void Entidades::Personagens::Inimigos::Mago::salvar()
{
	buffer.str("");
	buffer.clear();
	salvarDataBuffer();
	cout << "[SALVAR] " << buffer.str() << endl;//debug
	ofstream arquivo("mago.txt", ios::app);

	if (!arquivo.is_open())//debug
    {
        cout << "[ERRO] nao foi possivel abrir o arquivo!" << endl;
        return;
    }

	arquivo << buffer.str() << "\n";
	arquivo.close();

	cout << "[SALVAR] gravado com sucesso!" << endl;//debug
}

void Entidades::Personagens::Inimigos::Mago::salvarDataBuffer()
{
	Entidades::Personagens::Inimigos::Inimigo::salvarDataBuffer();
	// mais nada pra salvard
}
