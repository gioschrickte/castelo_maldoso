#include "Principal.hpp"
#include <iostream>
using namespace std;

Principal::Principal()
	: listaEntidade(), 
	pGrafico(Gerenciador::GerenciadorGrafico::getGerenciadorGrafico()),
	pEvento(Gerenciador::GerenciadorEvento::getGerenciadorEvento()), 
	pColisoes(new Gerenciador::GerenciadorColisoes(&listaEntidade, &listaObstaculo))
	
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
	Entidade::Personagem::Jogador::Jogador* jogador = new Entidade::Personagem::Jogador::Jogador(sf::Vector2f(50.0f, 50.0f));
	Entidade::Personagem::Inimigo::Inimigo* inimigo1 = new Entidade::Personagem::Inimigo::Inimigo(jogador, sf::Vector2f(100.0f, 100.0f));
	Entidade::Personagem::Inimigo::Inimigo* inimigo2 = new Entidade::Personagem::Inimigo::Inimigo(jogador, sf::Vector2f(150.0f, 150.0f));
	Entidade::Obstaculo::Plataforma* plataforma = new Entidade::Obstaculo::Plataforma(sf::Vector2f(300.0f, 50.0f), sf::Vector2f(200.0f, 20.0f));
		

	// Faz o gerenciador gráfico conhecer as Entidades
	listaEntidade.addEntidade(static_cast<Entidade::Entidade*>(jogador));
	listaEntidade.addEntidade(static_cast<Entidade::Entidade*>(inimigo1));
	listaEntidade.addEntidade(static_cast<Entidade::Entidade*>(inimigo2));
	listaObstaculo.addEntidade(static_cast<Entidade::Entidade*>(plataforma));


	


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
			listaEntidade[i]->atualizar();
			pGrafico->desenhaElemento(listaEntidade[i]->getCorpo());
		}
		for (int i = 0; i < listaObstaculo.getTam(); i++) {
			listaObstaculo[i]->atualizar();
			pGrafico->desenhaElemento(listaObstaculo[i]->getCorpo());
		}

		pGrafico->mostraElementos();

	}

	// Limpa os objetos criados em instanciaEntidades()
	listaEntidade.limpaLista();
	listaObstaculo.limpaLista();
}