#include "Ork.h"
#include <cmath>
#include "Jogador.h"
#include <fstream>
#define RAIO_PERSEGUIR 400.0f

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

	dano = 2.0f;
	vidaMax = 5.0f * nivelDificuldade;
	vida = vidaMax;
}

void Entidades::Personagens::Inimigos::Ork::danificar(Jogadores::Jogador* pJog)
{
	if (!podeHitar()) return;
	pJog->tomarDano(dano);
	std::cout << "Ork causou dano medio! (dano=" << dano << ")\n";
	std::cout << "Vida do jogador: " << pJog->getVida() << " / " << pJog->getVidaMax() << std::endl;
}

void Entidades::Personagens::Inimigos::Ork::executar()
{
	// O inimigo mÃ©dio vai ficar pulando e perseguindo o jogador, ou seja, a direÃ§Ã£o do pulo Ã© determinada pelo jogador

	sf::Vector2f posJogador = getAlvo()->getPosicao();
	sf::Vector2f posInimigo = getPosicao();
	float distancia = sqrt(pow(posJogador.x - posInimigo.x, 2) + pow(posJogador.y - posInimigo.y, 2));
	if (distancia <= RAIO_PERSEGUIR)
	{
		// Persegue o jogador
		if (posJogador.x < posInimigo.x) { andar(true); } // para esquerda
		else { andar(false); } // para direita
		if (noChao) { pular(); }
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

void Entidades::Personagens::Inimigos::Ork::salvarDataBuffer()
{
	Entidades::Personagens::Inimigos::Inimigo::salvarDataBuffer();
}


