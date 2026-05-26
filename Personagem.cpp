#pragma once

#include "Personagem.hpp"

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
	float ds = velFinal.x * dt;
	if (paraEsquerda)
	{
		ds *= -1;
	}
	corpo.move(ds, 0.0f);
}