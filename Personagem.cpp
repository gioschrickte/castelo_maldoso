#include "Personagem.hpp"
#define GRAVIDADE 9.80f

Entidades::Personagens::Personagem::Personagem(const sf::Vector2f pos, const sf::Vector2f tam, const float vel, const IDs::IDs id)
	: Entidade::Entidade(pos, tam, id), velFinal(sf::Vector2f(vel, vel)), relogio()
{
	podeAndar = 0;
	paraEsquerda = 0;
	dt = 0;
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

void Entidades::Personagens::Personagem::atualizarPosicao()
{
	dt = relogio.getElapsedTime().asSeconds();
	float dsx = velFinal.x * dt;

	if (paraEsquerda)
	{
		dsx *= -1;
	}
	corpo.move(dsx, 0.0f);
}

void Entidades::Personagens::Personagem::atualizaQueda()
{
	dt = relogio.getElapsedTime().asSeconds();
	float dvy = dt * 9.8f;
	velFinal.y += dvy;
	float dsy = velFinal.y * dt;

	corpo.move(0.0f, dsy);

}