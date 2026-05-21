#include "GerenciadorEventos.hpp"

Gerenciador::GerenciadorEvento* Gerenciador::GerenciadorEvento::pEvento(nullptr);

Gerenciador::GerenciadorEvento::GerenciadorEvento()
	: pJogador(nullptr), pGrafico(Gerenciador::GerenciadorGrafico::getGerenciadorGrafico())
{

}


Gerenciador::GerenciadorEvento::~GerenciadorEvento()
{
	pEvento = nullptr;
}


Gerenciador::GerenciadorEvento* Gerenciador::GerenciadorEvento::getGerenciadorEvento()
{
	if (pEvento == nullptr)	{
		pEvento = new Gerenciador::GerenciadorEvento();
	}
	return pEvento;
}


void Gerenciador::GerenciadorEvento::setJogador(Entidade::Personagem::Jogador::Jogador* pJ)
{
	pJogador = pJ;
}


void Gerenciador::GerenciadorEvento::verificaTeclaPressionada(sf::Keyboard::Key tecla)
{
	if (tecla == sf::Keyboard::A) {
		pJogador->andar(true);
	}
	else if (tecla == sf::Keyboard::D) {
		pJogador->andar(false);
	}
	else if (tecla == sf::Keyboard::Escape)
	{
		pGrafico->fecharJanela();
	}
}


void Gerenciador::GerenciadorEvento::verificaTeclaSolta(sf::Keyboard::Key tecla)
{
	if (tecla == sf::Keyboard::A || tecla == sf::Keyboard::D)
	{
		pJogador->parar();
	}
}


void Gerenciador::GerenciadorEvento::executar()
{
	sf::Event evento;
	while (pGrafico->getWindow()->pollEvent(evento))
	{
		if (evento.type == sf::Event::KeyPressed) {
			verificaTeclaPressionada(evento.key.code);
		}
		else if (evento.type == sf::Event::KeyReleased) {
			verificaTeclaSolta(evento.key.code);
		}
		else if (evento.type == sf::Event::Closed) {
			pGrafico->fecharJanela();
		}
	}
}