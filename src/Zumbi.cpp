// Zumbi.cpp
#include <cmath>
#include "Zumbi.h"
#include "Jogador.h"
#include <fstream>

Entidades::Personagens::Inimigos::Zumbi::Zumbi(
    Jogadores::Jogador* j, const sf::Vector2f pos)
    : Inimigo(j, pos, sf::Vector2f(50.0f, 50.0f), 90.0f, IDs::IDs::zumbi), moveAleatorio(0)
{
    corpo.setFillColor(sf::Color::Red);

    textura = pGG->carregarTextura("assets/zombie.png");
    sprite.setTexture(textura);

    // Ajusta a escala do sprite para cobrir exatamente o corpo (50x50)
    sf::Vector2u tSz = textura.getSize();
    if (tSz.x > 0 && tSz.y > 0)
    {
        sprite.setScale(50.0f / tSz.x, 50.0f / tSz.y);
    }

    sprite.setPosition(pos);
    temSprite = true;
	//Os sprites foram criados com a IA Sprite-AI.
    //link:https://www.sprite-ai.art/

	vidaMax = 5.0f;
	vida = vidaMax;
	dano = 1.0f;
}

Entidades::Personagens::Inimigos::Zumbi::~Zumbi() {}


void Entidades::Personagens::Inimigos::Zumbi::danificar(
    Jogadores::Jogador* pJog)
{
	if (!podeHitar()) return;
	pJog->tomarDano(dano);
    std::cout << "Zumbi causou dano leve! (dano=" << dano << ")\n";
	std::cout << "Vida do jogador: " << pJog->getVida() << " / " << pJog->getVidaMax() << std::endl;
}

void Entidades::Personagens::Inimigos::Zumbi::movAleatorio()
{
	if (moveAleatorio == 0)
	{
		andar(false);
	}
	else if (moveAleatorio == 1)
	{
		andar(true);
	}
	else
		parar();

	float dt = relogioAleatorio.getElapsedTime().asSeconds();
	if (dt >= 1.0f)
	{
		moveAleatorio = rand() % 4;
		relogioAleatorio.restart();
	}

}

void Entidades::Personagens::Inimigos::Zumbi::executar()
{
	float dt = calcularDt();

	sf::Vector2f posJogador = getAlvo()->getCorpo().getPosition();
	sf::Vector2f posInimigo = corpo.getPosition();

	if (fabs(posJogador.x - posInimigo.x) <= RAIO_PERSEGUIR && fabs(posJogador.y - posInimigo.y) <= RAIO_PERSEGUIR)
		persegueJogador(posJogador, posInimigo);
	else
		movAleatorio();

	if (podeAndar) atualizarX(dt);
	atualizarY(dt);
}

void Entidades::Personagens::Inimigos::Zumbi::salvar()
{
	buffer.str("");
	buffer.clear();
	salvarDataBuffer();
	cout << "[SALVAR] " << buffer.str() << endl;//debug
	ofstream arquivo("zumbi.txt", ios::app);

	if (!arquivo.is_open())//debug
    {
        cout << "[ERRO] nao foi possivel abrir o arquivo!" << endl;
        return;
    }

	arquivo << buffer.str() << "\n";
	arquivo.close();

	cout << "[SALVAR] gravado com sucesso!" << endl;//debug
}

void Entidades::Personagens::Inimigos::Zumbi::salvarDataBuffer()
{
	Entidades::Personagens::Inimigos::Inimigo::salvarDataBuffer();
}
