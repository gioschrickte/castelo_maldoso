#include "Jogador.hpp"

Entidade::Personagem::Jogador::Jogador::Jogador(const sf::Vector2f pos, const sf::Vector2f tam)
	: Personagem(pos, tam, 200.0f,IDs::IDs::jogador)
{
	corpo.setFillColor(sf::Color::Blue);
}

Entidade::Personagem::Jogador::Jogador::~Jogador()
{

}


void Entidade::Personagem::Jogador::Jogador::atualizar()
{
	if (podeAndar)
	{
		atualizarPosicao();
	}

	relogio.restart();
}

void Entidade::Personagem::Jogador::Jogador::colisao(Entidade* outraEntidade, sf::Vector2f ds)
{
	switch (outraEntidade->getID()) {
		case(IDs::IDs::inimigo):
		{

		}
		break;
		case(IDs::IDs::plataforma):
		{
			
		}
	}
}