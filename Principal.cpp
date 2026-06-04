#include "Principal.hpp"
#include "GerenciadorColisoes.hpp"
#include "FasePrimeira.hpp"
#include "FaseSegunda.hpp"
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
	delete faseAtual;
	faseAtual = nullptr;

	delete pColisoes;
	pColisoes = nullptr;

	delete pEvento;
	pEvento = nullptr;

	delete pGrafico;
	pGrafico = nullptr;
}


void Principal::executar()
{
	srand(time(NULL));
	Jogo::Ente::setGG(pGrafico);

	Entidades::Personagens::Jogadores::Jogador* jogador1 = new Entidades::Personagens::Jogadores::Jogador(sf::Vector2f(100.0f, 100.0f));	
	
	// Essa parte vai virar menu depois
	faseAtual = new Jogo::Fases::FasePrimeira(jogador1);
	if(!faseAtual){ printf("Erro ao criar fase"); }
	faseAtual->executar();

	// antes de criar a segunda fase, tem q dar delete(faseAtual)
}