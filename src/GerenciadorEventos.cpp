#include "GerenciadorEventos.h"
#include "Fase.h"





Gerenciador::GerenciadorEvento* Gerenciador::GerenciadorEvento::pEvento(nullptr);

Gerenciador::GerenciadorEvento::GerenciadorEvento()
	: pJogador(nullptr), pJogador2(nullptr), pGrafico(Gerenciador::GerenciadorGrafico::getGerenciadorGrafico())
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


void Gerenciador::GerenciadorEvento::setJogador(Entidades::Personagens::Jogadores::Jogador* pJ)
{
	pJogador = pJ;
}

void Gerenciador::GerenciadorEvento::setJogador2(Entidades::Personagens::Jogadores::Jogador* pJ2)
{
	pJogador2 = pJ2;
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
	else if (tecla == sf::Keyboard::Space || tecla == sf::Keyboard::W) {
		pJogador->pular();
	}
	else if (tecla == sf::Keyboard::Z) {
		pJogador->atacar();
	}
	else if (tecla == sf::Keyboard::Enter){
		if(pFase->getPausado())
		{
			pFase->setPausado(false);
		}
		else
		{
			pFase->setPausado(true);
		}
	}
	else if (tecla == sf::Keyboard::M){
		pFase->SalvarTudo();
	}


	//jogador 2
	if (pJogador2) {
        if (tecla == sf::Keyboard::Left)     pJogador2->andar(true);
        else if (tecla == sf::Keyboard::Right) pJogador2->andar(false);
        else if (tecla == sf::Keyboard::Up)    pJogador2->pular();
        else if (tecla == sf::Keyboard::RControl) pJogador2->atacar();

    }

}


void Gerenciador::GerenciadorEvento::verificaTeclaSolta(sf::Keyboard::Key tecla)
{
	if (tecla == sf::Keyboard::A || tecla == sf::Keyboard::D)
	{
		pJogador->parar();
	}

	if (pJogador2 && (tecla == sf::Keyboard::Left || tecla == sf::Keyboard::Right))
	{
		pJogador2->parar();
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
//d