#include "Principal.hpp"
#include "GerenciadorColisoes.hpp"
#include <iostream>
using namespace std;

Principal::Principal()
	: listaEntidade(), 
	pGrafico(Gerenciador::GerenciadorGrafico::getGerenciadorGrafico()),
	pEvento(Gerenciador::GerenciadorEvento::getGerenciadorEvento()), 
	pColisoes(Gerenciador::GerenciadorColisoes::getGerenciadorColisoes()),
	faseAtual(nullptr),
	jogador1(nullptr)
	
{
	executar();
}

Principal::~Principal()
{
	if (pColisoes) {
		delete pColisoes;
		pColisoes = nullptr;
	}
}


void Principal::executar()
{
	srand(time(NULL));

	Jogo::Ente::setGG(pGrafico); // Passa o ponteiro do gerenciador gráfico para as entidades, para que elas possam desenhar a si mesmas

	Entidades::Personagens::Jogadores::Jogador* jogador1 = new Entidades::Personagens::Jogadores::Jogador(sf::Vector2f(100.0f, 100.0f));	

	if (jogador1)
	{
		faseAtual = new Jogo::Fases::Fase(jogador1);
	}
	{
		printf("Erro ao criar jogador 1");
	}
	
	if (faseAtual)
	{
		faseAtual->executar();
	}
	else
	{
		printf("Erro ao criar fase");
	}
}