#include "Ork.h"
#include <cmath>
#include "Jogador.h"
#include <fstream>
#define RAIO_PERSEGUIR 400.0f
#define FATOR_PULO_ORK 0.5f   // jogador pula com metade da forca
#define DURACAO_PULO_ORK 3.0f // durante 3 segundos

Entidades::Personagens::Inimigos::Ork::Ork(Jogadores::Jogador* j, const sf::Vector2f pos)
    : Inimigo(j, pos, sf::Vector2f(60.0f, 60.0f), 150.0f, IDs::IDs::ork)
{
    corpo.setFillColor(sf::Color::Magenta);
	textura = pGG->carregarTextura("assets/ork.png");
	sprite.setTexture(textura);

	sf::Vector2u tSz = textura.getSize();
	if (tSz.x > 0 && tSz.y > 0)
	{
		sprite.setScale(70.0f / tSz.x, 70.0f / tSz.y);
	}

	sprite.setPosition(pos);
	temSprite = true;
	//Os sprites foram criados com a IA Sprite-AI.
    //link:https://www.sprite-ai.art/

	dano = 2.0f;
	vidaMax = 5.0f * nivelDificuldade;
	vida = vidaMax;
}

void Entidades::Personagens::Inimigos::Ork::danificar(Jogadores::Jogador* pJog)
{
	if (!podeHitar()) return;
	pJog->tomarDano(dano);

	// Algoritmo do Ork: alem do dano, enfraquece o pulo do jogador por alguns segundos
	// (reaproveita o multiplicadorPulo da classe Personagem; a velocidade fica intacta).
	pJog->aplicarLentidaoTemporaria(1.0f, FATOR_PULO_ORK, DURACAO_PULO_ORK);

	std::cout << "Ork enfraqueceu o pulo do jogador! (dano=" << dano << ")\n";
	std::cout << "Vida do jogador: " << pJog->getVida() << " / " << pJog->getVidaMax() << std::endl;
}

void Entidades::Personagens::Inimigos::Ork::executar()
{
	// O inimigo medio vai ficar pulando e perseguindo o jogador, ou seja, a direcao do pulo determinada pelo jogador

	sf::Vector2f posJogador = getAlvo()->getPosicao();
	sf::Vector2f posInimigo = getPosicao();
	float distancia = sqrt(pow(posJogador.x - posInimigo.x, 2) + pow(posJogador.y - posInimigo.y, 2));
	if (distancia <= RAIO_PERSEGUIR)
	{
		persegueJogador(posJogador, posInimigo);
		if(noChao) {pular();}
	}
	else
	{
		// Fica pulando no lugar
		parar();
		if (noChao) { pular(); }
	}

	float dt = calcularDt();
	if(podeAndar) {
		atualizarX(dt);
	}
	atualizarY(dt);
}

void Entidades::Personagens::Inimigos::Ork::salvar()
{
	buffer.str("");
	buffer.clear();
	salvarDataBuffer();
	cout << "[SALVAR] " << buffer.str() << endl;//debug
	ofstream arquivo("ork.txt", ios::app);

	if (!arquivo.is_open())//debug
    {
        cout << "[ERRO] nao foi possivel abrir o arquivo!" << endl;
        return;
    }

	arquivo << buffer.str() << "\n";
	arquivo.close();

	cout << "[SALVAR] gravado com sucesso!" << endl;//debug
}

void Entidades::Personagens::Inimigos::Ork::salvarDataBuffer()
{
	Entidades::Personagens::Inimigos::Inimigo::salvarDataBuffer();
}


