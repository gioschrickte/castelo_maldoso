#include "Entidade.h"

Entidades::Entidade::Entidade()
	: Jogo::Ente(), buffer()
{

}

Entidades::Entidade::Entidade(const sf::Vector2f pos, const sf::Vector2f tam, const IDs::IDs id)
	: Jogo::Ente(pos, tam, id)
{
}

Entidades::Entidade::~Entidade()
{

}

const IDs::IDs Entidades::Entidade::getId() const
{
	return id;
}

const sf::Vector2f Entidades::Entidade::getPosicao() const
{
	return corpo.getPosition();
}

const sf::Vector2f Entidades::Entidade::getTamanho() const
{
	return corpo.getSize();
}

const sf::RectangleShape Entidades::Entidade::getCorpo() const
{
	return corpo;
}

void Entidades::Entidade::mover(sf::Vector2f ds)
{
	corpo.move(ds);
}

void Entidades::Entidade::salvarDataBuffer()
{
	// Grava apenas "id x y " (com espaco final). Os campos velocidade/ativa/vida
	// sao acrescentados pelos ramos (Personagem/Obstaculo) para manter o schema
	// uniforme: id x y velX velY ativa vida
	buffer << static_cast<int>(getId()) << " "
		   << getPosicao().x            << " "
		   << getPosicao().y			<< " ";
}//d



