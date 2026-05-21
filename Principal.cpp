#include "Principal.hpp"
#include <iostream>
using namespace std;

Principal::Principal()
	: listaEntidade(), pGrafico(Gerenciador::GerenciadorGrafico::getGerenciadorGrafico()), pEvento(Gerenciador::GerenciadorEvento::getGerenciadorEvento())
{
	instanciaEntidades();
	executar();
}

Principal::~Principal()
{

}

void Principal::instanciaEntidades()
{
	// Cria dinamicamente os objetos
	Entidade::Personagem::Jogador::Jogador* jogador = new Entidade::Personagem::Jogador::Jogador(sf::Vector2f(50.0f, 50.0f));
	Entidade::Personagem::Inimigo::Inimigo* inimigo1 = new Entidade::Personagem::Inimigo::Inimigo(jogador, sf::Vector2f(100.0f, 100.0f));
	Entidade::Personagem::Inimigo::Inimigo* inimigo2 = new Entidade::Personagem::Inimigo::Inimigo(jogador, sf::Vector2f(150.0f, 150.0f));

	// Faz o gerenciador gráfico conhecer as Entidades
	listaEntidade.addEntidade(static_cast<Entidade::Entidade*>(jogador));
	listaEntidade.addEntidade(static_cast<Entidade::Entidade*>(inimigo1));
	listaEntidade.addEntidade(static_cast<Entidade::Entidade*>(inimigo2));

	// Faz o gerenciador de eventos conhecer o Jogador
	pEvento->setJogador(jogador);

}


void Principal::executar()
{
	while (pGrafico->verificaJanelaAberta()) {
		pEvento->executar();
		pGrafico->limpaJanela();
		for (int i = 0; i < listaEntidade.getTam(); i++)
		{
			listaEntidade[i]->atualizar();
			pGrafico->desenhaElemento(listaEntidade[i]->getCorpo());
		}

		pGrafico->mostraElementos();
	}

	// Limpa os objetos criados em instanciaEntidades()
	listaEntidade.limpaLista();
}