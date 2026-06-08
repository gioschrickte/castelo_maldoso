// InimigoFacil.cpp
#include "InimigoFacil.h"
#include "Jogador.h"

Entidades::Personagens::Inimigos::InimigoFacil::InimigoFacil(
    Jogadores::Jogador* j, const sf::Vector2f pos)
    : Inimigo(j, pos, sf::Vector2f(50.0f, 50.0f), 90.0f), moveAleatorio(0)
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

	vidaMax = 5.0f;
	vida = vidaMax;
	dano = 1.0f;
}

Entidades::Personagens::Inimigos::InimigoFacil::~InimigoFacil() {}


void Entidades::Personagens::Inimigos::InimigoFacil::danificar(
    Jogadores::Jogador* pJog)
{
	if (!podeHitar()) return;
	pJog->tomarDano(dano);
    std::cout << "InimigoFacil causou dano leve! (dano=" << dano << ")\n";
	std::cout << "Vida do jogador: " << pJog->getVida() << " / " << pJog->getVidaMax() << std::endl;
}


void Entidades::Personagens::Inimigos::InimigoFacil::persegueJogador(sf::Vector2f posJogador, sf::Vector2f posInimigo)
{
	if (posJogador.x - posInimigo.x > 0.0f) { andar(false); }
	else
	{
		andar(true);
	}
}

void Entidades::Personagens::Inimigos::InimigoFacil::movAleatorio()
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

void Entidades::Personagens::Inimigos::InimigoFacil::executar()
{
	float dt = calcularDt();

	sf::Vector2f posJogador = jogador->getCorpo().getPosition();
	sf::Vector2f posInimigo = corpo.getPosition();

	if (fabs(posJogador.x - posInimigo.x) <= RAIO_PERSEGUIR && fabs(posJogador.y - posInimigo.y) <= RAIO_PERSEGUIR)
		persegueJogador(posJogador, posInimigo);
	else
		movAleatorio();

	if (podeAndar) atualizarX(dt);
	atualizarY(dt);
}
