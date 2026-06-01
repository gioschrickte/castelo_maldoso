#include "Personagem.hpp"
#define GRAVIDADE 1500.0f
#define FORCA_PULO 700.0f


Entidades::Personagens::Personagem::Personagem(const sf::Vector2f pos, const sf::Vector2f tam, const float vel, const IDs::IDs id)
	: Entidade::Entidade(pos, tam, id), velFinal(sf::Vector2f(vel, 0.0f)), relogio(), noChao(false)
{
	podeAndar = 0;
	paraEsquerda = 0;
	forcaPulo = FORCA_PULO;
}

Entidades::Personagens::Personagem::~Personagem()
{

}

void Entidades::Personagens::Personagem::andar(const bool paraEsquerda)
{
	podeAndar = true;
	this->paraEsquerda = paraEsquerda;
} 
void Entidades::Personagens::Personagem::parar()
{
	podeAndar = false;
}

float Entidades::Personagens::Personagem::calcularDt() // responsavel pela física dos movimentos
{
	float dt = relogio.getElapsedTime().asSeconds();
	relogio.restart();
	if (dt > 0.05f) dt = 0.05f;
	return dt;
}

void Entidades::Personagens::Personagem::atualizarX(float dt)
{
	float dsx = velFinal.x * dt;
	if (paraEsquerda) dsx *= -1;
	corpo.move(dsx, 0.0f);
}

void Entidades::Personagens::Personagem::atualizarY(float dt)
{
	velFinal.y += GRAVIDADE * dt;
	corpo.move(0.0f, velFinal.y * dt);
	noChao = false;
}

void Entidades::Personagens::Personagem::pular()
{
	if (noChao)
	{
		velFinal.y = -forcaPulo;   // negativo = para cima
		noChao = false;
	}
}

void Entidades::Personagens::Personagem::aterrissar()
{
	velFinal.y = 0.0f;   // sem isto a velocidade continua acumulando no chão
	noChao = true;
}