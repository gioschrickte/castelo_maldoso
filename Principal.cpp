#include "Principal.hpp"
#include <iostream>
using namespace std;

Principal::Principal()
	: listaEntidade(), 
	pGrafico(Gerenciador::GerenciadorGrafico::getGerenciadorGrafico()),
	pEvento(Gerenciador::GerenciadorEvento::getGerenciadorEvento()), 
	pColisoes(Gerenciador::GerenciadorColisoes::getGerenciadorColisoes())
	
{
	instanciaEntidades();
	executar();
}

Principal::~Principal()
{
	if (pColisoes) {
		delete pColisoes;
		pColisoes = nullptr;
	}
}

void Principal::instanciaEntidades()
{
	// Cria dinamicamente os objetos
	Entidades::Personagens::Jogadores::Jogador* jogador = new Entidades::Personagens::Jogadores::Jogador(sf::Vector2f(50.0f, 50.0f));
	Entidades::Personagens::Inimigos::Inimigo* inimigo1 = new Entidades::Personagens::Inimigos::Inimigo(jogador, sf::Vector2f(100.0f, 100.0f));
	Entidades::Personagens::Inimigos::Inimigo* inimigo2 = new Entidades::Personagens::Inimigos::Inimigo(jogador, sf::Vector2f(150.0f, 150.0f));
	Entidades::Obstaculos::Plataforma* plataforma = new Entidades::Obstaculos::Plataforma(sf::Vector2f(300.0f, 50.0f), sf::Vector2f(200.0f, 20.0f));
		

	// Faz o gerenciador gráfico conhecer as Entidades
	listaEntidade.addEntidade(static_cast<Entidades::Entidade*>(jogador));
	listaEntidade.addEntidade(static_cast<Entidades::Entidade*>(inimigo1));
	listaEntidade.addEntidade(static_cast<Entidades::Entidade*>(inimigo2));
	listaObstaculo.addEntidade(static_cast<Entidades::Entidade*>(plataforma));

	pColisoes->setJogador1(jogador);
	pColisoes->incluirInimigo(inimigo1);
	pColisoes->incluirInimigo(inimigo2);
	pColisoes->incluirObstaculo(plataforma);
	


	// Faz o gerenciador de eventos conhecer o Jogador
	pEvento->setJogador(jogador);

}


void Principal::executar()
{
	while (pGrafico->verificaJanelaAberta()) {
		pEvento->executar();
		pGrafico->limpaJanela();
		pColisoes->executar();

		for (int i = 0; i < listaEntidade.getTam(); i++)
		{
			listaEntidade[i]->executar();
			pGrafico->desenhaElemento(listaEntidade[i]->getCorpo());
		}
		for (int i = 0; i < listaObstaculo.getTam(); i++) {
			listaObstaculo[i]->executar();
			pGrafico->desenhaElemento(listaObstaculo[i]->getCorpo());
		}

		pGrafico->mostraElementos();

	}

	// Limpa os objetos criados em instanciaEntidades()
	listaEntidade.limpaLista();
	listaObstaculo.limpaLista();
}