#include "Principal.h"
#include "GerenciadorColisoes.h"
#include "FasePrimeira.h"
#include "FaseSegunda.h"
#include <iostream>
#include "Menu.h"
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

void Principal::criarFase(int numFase)
{
	if (faseAtual)
	{
		delete faseAtual;
		faseAtual = nullptr;
		pColisoes->limpar();   // limpa listas do gerenciador antes de recriar a fase
	}

	if (numFase == 1) faseAtual = new Jogo::Fases::FasePrimeira(jogador1);
	else if (numFase == 2) faseAtual = new Jogo::Fases::FaseSegunda(jogador1);

	if (!faseAtual) printf("Erro ao criar fase %d\n", numFase);
}


void Principal::executar()
{
	srand(time(NULL));
	Jogo::Ente::setGG(pGrafico);

	jogador1 = new Entidades::Personagens::Jogadores::Jogador(sf::Vector2f(100.0f, 100.0f));	
	
	Jogo::Menu menu;
	int escolha = menu.rodar();   // exibe o menu e aguarda o clique

	if (escolha == -1) return;    // jogador fechou a janela no menu

	criarFase(escolha);
	faseAtual->executar();
	// antes de criar a segunda fase, tem q dar delete(faseAtual)
}
