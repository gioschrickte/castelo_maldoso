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

void Entidades::Personagens::Jogadores::Jogador::colidir(Entidades::Personagens::Inimigos::Inimigo* inimigo)
{
	// Aqui você pode implementar a lógica de dano ao jogador, como reduzir a vida ou reiniciar o jogo
	std::cout << "O jogador colidiu com um inimigo!" << std::endl;
	inimigo->danificar(this);
}