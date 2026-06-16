#include "Principal.h"
#include "GerenciadorColisoes.h"
#include "FasePrimeira.h"
#include "FaseSegunda.h"
#include <iostream>
#include "Menu.h"
using namespace std;

#define MAX_FASES 2   // numero de fases jogaveis em sequencia

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
		delete faseAtual;      // o destrutor da fase deleta o jogador (esta na lista de entidades)
		faseAtual = nullptr;
		pColisoes->limpar();   // limpa listas do gerenciador antes de recriar a fase
	}

	// Jogador novo a cada fase (vida cheia e ativo); a fase passa a ser dona dele
	jogador1 = new Entidades::Personagens::Jogadores::Jogador(sf::Vector2f(100.0f, 100.0f));

	if (numFase == 1) faseAtual = new Jogo::Fases::FasePrimeira(jogador1);
	else if (numFase == 2) faseAtual = new Jogo::Fases::FaseSegunda(jogador1);

	if (!faseAtual) printf("Erro ao criar fase %d\n", numFase);
}


void Principal::executar()
{
	srand(time(NULL));
	Jogo::Ente::setGG(pGrafico);

	// Laco principal: menu -> fase(s) sequenciais -> menu de novo
	while (pGrafico->verificaJanelaAberta())
	{
		Jogo::Menu menu;
		int escolha = menu.rodar();   // exibe o menu e aguarda o clique

		if (escolha == -1) break;             // fechou a janela no menu
		if (escolha != 1 && escolha != 2)     // "Continuar" ainda nao implementado
			continue;                         // reexibe o menu

		int numFase = escolha;
		bool jogando = true;
		while (jogando && pGrafico->verificaJanelaAberta())
		{
			criarFase(numFase);
			if (!faseAtual) break;
			faseAtual->executar();

			switch (faseAtual->getResultado())
			{
			case Jogo::Fases::ResultadoFase::FaseConcluida:
				if (numFase < MAX_FASES) numFase++;   // avanca para a proxima fase
				else jogando = false;                 // zerou o jogo -> volta ao menu
				break;
			default:                                  // JogadorMorreu ou JanelaFechada
				jogando = false;                      // volta ao menu (ou encerra, se a janela fechou)
				break;
			}
		}
	}
}
