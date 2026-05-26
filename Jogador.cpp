#include "Jogador.hpp"
#include "Inimigo.hpp"

Entidades::Personagens::Jogadores::Jogador::Jogador(const sf::Vector2f pos, const sf::Vector2f tam)
	: Personagem(pos, tam, 200.0f, IDs::IDs::jogador)
{
	corpo.setFillColor(sf::Color::Blue);
}

Entidades::Personagens::Jogadores::Jogador::~Jogador()
{

}


void Entidades::Personagens::Jogadores::Jogador::executar()
{
	if (podeAndar)
	{
		atualizarPosicao();
	}

	relogio.restart();
}

void Entidades::Personagens::Jogadores::Jogador::colidir(Entidades::Entidade* outraEntidade, sf::Vector2f ds)
{
	if (outraEntidade->getId() == IDs::IDs::inimigo)
	{
		// Colisão com inimigo: o jogador é "danificado" (pode ser implementado como perder vida, por exemplo)
		colidir(static_cast<Entidades::Personagens::Inimigos::Inimigo*>(outraEntidade));
	}
	else if (outraEntidade->getId() == IDs::IDs::plataforma)
	{
		// Colisão com plataforma: o jogador para de cair e pode andar novamente
		outraEntidade->colidir(this, ds);
	}
}

void Entidades::Personagens::Jogadores::Jogador::colidir(Entidades::Personagens::Inimigos::Inimigo* inimigo)
{
	// Aqui você pode implementar a lógica de dano ao jogador, como reduzir a vida ou reiniciar o jogo
	std::cout << "O jogador colidiu com um inimigo!" << std::endl;
	inimigo->danificar(this);
}