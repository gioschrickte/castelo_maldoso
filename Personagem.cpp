#include "Personagem.hpp"
#define GRAVIDADE 1500.0f
#define FORCA_PULO 1000.0f


Entidades::Personagens::Personagem::Personagem(const sf::Vector2f pos, const sf::Vector2f tam, const float vel, const IDs::IDs id)
	: Entidade::Entidade(pos, tam, id), velFinal(sf::Vector2f(vel, 0.0f)), relogio(), noChao(false)
{
	podeAndar = 0;
	paraEsquerda = 0;
	forcaPulo = FORCA_PULO;
	multiplicadorVel = 1.0f;
	multiplicadorPulo = 1.0f;
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
	// multiplicadorVel < 1 deixa o personagem mais lento (ex.: dentro da lama)
	float dsx = velFinal.x * dt * multiplicadorVel;
	if (paraEsquerda) dsx *= -1;

	float xAtual = getPosicao().x;
	float novoX = xAtual + dsx;

	float limiteDireito = static_cast<float>(pGG->getWindow()->getSize().x) - getTamanho().x;

	// Prende a posição dentro dos limites da tela
	if (novoX < 0.0f)            novoX = 0.0f;
	if (novoX > limiteDireito)   novoX = limiteDireito;

	// Move apenas o deslocamento que de fato cabe na tela
	corpo.move(novoX - xAtual, 0.0f);
}

void Entidades::Personagens::Personagem::atualizarY(float dt)
{
	velFinal.y += GRAVIDADE * dt;
	corpo.move(0.0f, velFinal.y * dt);
	noChao = false;

	// A cada frame, os multiplicadores de velocidade e pulo voltam ao normal

	multiplicadorVel = 1.0f;
	multiplicadorPulo = 1.0f;
}

void Entidades::Personagens::Personagem::pular()
{
	if (noChao)
	{
		velFinal.y = -forcaPulo * multiplicadorPulo;   // negativo = para cima
		noChao = false;
	}
}

void Entidades::Personagens::Personagem::aterrissar()
{
	velFinal.y = 0.0f;   // sem isto a velocidade continua acumulando no chão
	noChao = true;
}

void Entidades::Personagens::Personagem::baterCabeca()
{
	velFinal.y = 0.0f;   // sem isto a velocidade continua acumulando no teto
}

void Entidades::Personagens::Personagem::aplicarLentidao(float fatorVel, float fatorPulo)
{
	multiplicadorVel = fatorVel;
	multiplicadorPulo = fatorPulo;
}