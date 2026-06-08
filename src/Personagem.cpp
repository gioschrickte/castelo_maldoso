#include "Personagem.h"
#define GRAVIDADE 1500.0f
#define FORCA_PULO 800.0f


Entidades::Personagens::Personagem::Personagem(const sf::Vector2f pos, const sf::Vector2f tam, const float vel, const IDs::IDs id)
	: Entidade::Entidade(pos, tam, id), velFinal(sf::Vector2f(vel, 0.0f)), relogio(), noChao(false), barraVida()
{
	podeAndar = 0;
	paraEsquerda = 0;
	forcaPulo = FORCA_PULO;
	multiplicadorVel = 1.0f;
	multiplicadorPulo = 1.0f;

	vidaMax = 10.0f;
	vida = vidaMax;

	barraVida.setSize(sf::Vector2f(tam.x, 5.0f));
	barraVida.setFillColor(sf::Color::Green);
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

float Entidades::Personagens::Personagem::calcularDt() // responsavel pela fÃ­sica dos movimentos
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

	// Prende a posiÃ§Ã£o dentro dos limites da tela
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
	velFinal.y = 0.0f;   // sem isto a velocidade continua acumulando no chÃ£o
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

float Entidades::Personagens::Personagem::getVida() const
{
	return vida;
}

float Entidades::Personagens::Personagem::getVidaMax() const
{
	return vidaMax;
}

void Entidades::Personagens::Personagem::atualizaVida()
{
	if (vida < 0.0f)      vida = 0.0f;
	if (vida > vidaMax)   vida = vidaMax;

	// largura proporcional Ã  vida atual
	const sf::Vector2f tam = getTamanho();
	const float proporcao = vida / vidaMax;
	barraVida.setSize(sf::Vector2f(tam.x * proporcao, barraVida.getSize().y));

	// posiciona acima da cabeÃ§a (top do personagem - altura da barra - folga)
	const sf::Vector2f pos = getPosicao();
	const float folga = 4.0f;
	barraVida.setPosition(pos.x, pos.y - barraVida.getSize().y - folga);

	// cor em funÃ§Ã£o da proporÃ§Ã£o (nÃ£o do valor absoluto)
	if (proporcao > 0.6f)      barraVida.setFillColor(sf::Color::Green);
	else if (proporcao > 0.3f) barraVida.setFillColor(sf::Color::Yellow);
	else                       barraVida.setFillColor(sf::Color::Red);
}

void Entidades::Personagens::Personagem::desenhar()
{
	atualizaVida();              // sincroniza antes de desenhar
	Jogo::Ente::desenhar();      // desenha o corpo (ou sprite)
	pGG->desenhaElemento(barraVida);
}

void Entidades::Personagens::Personagem::tomarDano(float dano)
{
	vida -= dano;
	if (vida < 0.0f) vida = 0.0f;
}
