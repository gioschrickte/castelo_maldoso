#pragma once

#include "Personagem.hpp"

Entidade::Personagem::Personagem::Personagem(const sf::Vector2f pos, const sf::Vector2f tam, const float vel)
	: Entidade::Entidade(pos, tam), velFinal(sf::Vector2f(vel, vel)), relogio()
{
	podeAndar = 0;
	paraEsquerda = 0;
	dt = 0;
}

Entidade::Personagem::Personagem::~Personagem()
{

}

void Entidade::Personagem::Personagem::andar(const bool paraEsquerda)
{
	podeAndar = true;
	this->paraEsquerda = paraEsquerda;
}
void Entidade::Personagem::Personagem::parar()
{
	podeAndar = false;
}

void Entidade::Personagem::Personagem::atualizarPosicao()
{
	dt = relogio.getElapsedTime().asSeconds();
	float ds = velFinal.x * dt;
	if (paraEsquerda)
	{
		ds *= -1;
	}
	corpo.move(ds, 0.0f);
}