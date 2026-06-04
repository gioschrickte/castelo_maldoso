#include "Projetil.hpp"
#include <cmath>
	
#define VEL_PROJETIL 400.0f
#define FORA_DA_TELA -1000.0f

Entidades::Projetil::Projetil(int dano, const sf::Vector2f tam)
	: Entidade(sf::Vector2f(FORA_DA_TELA, FORA_DA_TELA), tam, IDs::IDs::vazio),
	ativo(false), dano(dano), velocidade(0.0f, 0.0f), relogio()
{
	corpo.setFillColor(sf::Color(255, 180, 40)); 
	
	
	textura = pGG->carregarTextura("assets/fireball.png");
	sprite.setTexture(textura);

	// Ajusta a escala do sprite para cobrir exatamente o corpo (50x50)
	sf::Vector2u tSz = textura.getSize();
	if (tSz.x > 0 && tSz.y > 0)
	{
		sprite.setScale(50.0f / tSz.x, 50.0f / tSz.y);
	}

	sprite.setPosition(this->getPosicao());
	temSprite = true;
}

Entidades::Projetil::~Projetil() {}

void Entidades::Projetil::lancar(sf::Vector2f origem, sf::Vector2f alvo)
{
	corpo.setPosition(origem - corpo.getSize() / 2.0f);

	sf::Vector2f dir = alvo - origem;
	float comprimento = std::sqrt(dir.x * dir.x + dir.y * dir.y);
	if (comprimento > 0.0f) dir /= comprimento;
	else                    dir = sf::Vector2f(1.0f, 0.0f);

	velocidade = dir * VEL_PROJETIL;
	ativo = true;
	relogio.restart();
}

void Entidades::Projetil::executar()
{
	if (!ativo) return;

	float dt = relogio.getElapsedTime().asSeconds();
	relogio.restart();
	if (dt > 0.05f) dt = 0.05f;

	corpo.move(velocidade * dt);

	const sf::Vector2f p = corpo.getPosition();
	const sf::Vector2f t = corpo.getSize();
	const float W = static_cast<float>(pGG->getWindow()->getSize().x);
	const float H = static_cast<float>(pGG->getWindow()->getSize().y);
	if (p.x + t.x < 0.0f || p.x > W || p.y + t.y < 0.0f || p.y > H)
		desativar();
}

void Entidades::Projetil::desativar()
{
	ativo = false;
	corpo.setPosition(FORA_DA_TELA, FORA_DA_TELA);
}

void Entidades::Projetil::atingir()
{
	std::cout << "O projetil atingiu o jogador! (dano = " << dano << ")\n";
	desativar();
}

bool Entidades::Projetil::estaAtivo() const { return ativo; }
int  Entidades::Projetil::getDano()   const { return dano; }