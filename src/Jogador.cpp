#include "Jogador.h"
#include "Inimigo.h"

#define DURACAO_ATAQUE  0.15f
#define COOLDOWN_ATAQUE 0.5f

Entidades::Personagens::Jogadores::Jogador::Jogador(const sf::Vector2f pos, const sf::Vector2f tam)
	: Personagem(pos, tam, 200.0f, IDs::IDs::jogador), ataqueAtivo(false), danoAtaque(3.0f)
{
	corpo.setFillColor(sf::Color::Blue);
	vidaMax = 20.0f;
	vida = vidaMax;
}

Entidades::Personagens::Jogadores::Jogador::~Jogador()
{

}


void Entidades::Personagens::Jogadores::Jogador::executar()
{
	float dt = calcularDt();
	if (podeAndar) atualizarX(dt);
	atualizarY(dt);

	if (ataqueAtivo && relogioAtaque.getElapsedTime().asSeconds() >= DURACAO_ATAQUE)
		ataqueAtivo = false;
}

void Entidades::Personagens::Jogadores::Jogador::atacar()
{
	if (relogioAtaque.getElapsedTime().asSeconds() >= COOLDOWN_ATAQUE) {
		relogioAtaque.restart();
		ataqueAtivo = true;
		std::cout << "Jogador atacou!\n";
	}
}

bool Entidades::Personagens::Jogadores::Jogador::estaAtacando() const { return ataqueAtivo; }
float Entidades::Personagens::Jogadores::Jogador::getDanoAtaque() const { return danoAtaque; }

void Entidades::Personagens::Jogadores::Jogador::colidir(Entidades::Personagens::Inimigos::Inimigo* inimigo)
{
	inimigo->danificar(this);
}
