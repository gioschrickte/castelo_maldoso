#include "Principal.h"
#include "GerenciadorColisoes.h"
#include "FasePrimeira.h"
#include "FaseSegunda.h"
#include <iostream>
#include <fstream>
#include "Menu.h"
using namespace std;

#define MAX_FASES 2   // numero de fases jogaveis em sequencia

Principal::Principal()
	: listaEntidade(), 
	pGrafico(Gerenciador::GerenciadorGrafico::getGerenciadorGrafico()),
	pEvento(Gerenciador::GerenciadorEvento::getGerenciadorEvento()), 
	pColisoes(Gerenciador::GerenciadorColisoes::getGerenciadorColisoes()),
	faseAtual(nullptr),
	jogador1(nullptr),
	jogador2(nullptr),
	numJogadores(1)
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

	// Jogador(es) novo(s) a cada fase (vida cheia e ativos); a fase passa a ser dona deles
	jogador1 = new Entidades::Personagens::Jogadores::Jogador(sf::Vector2f(100.0f, 100.0f));
	jogador2 = (numJogadores == 2)
		? new Entidades::Personagens::Jogadores::Jogador(sf::Vector2f(160.0f, 100.0f))
		: nullptr;

	if (numFase == 1) faseAtual = new Jogo::Fases::FasePrimeira(jogador1, jogador2);
	else if (numFase == 2) faseAtual = new Jogo::Fases::FaseSegunda(jogador1, jogador2);

	if (!faseAtual) printf("Erro ao criar fase %d\n", numFase);
}

void Principal::carregarFase(int numFase)
{
	if (faseAtual)
	{
		delete faseAtual;
		faseAtual = nullptr;
		pColisoes->limpar();
	}

	// Jogador(es) com posicao provisoria; a carga sobrescreve posicao/vida/estado.
	jogador1 = new Entidades::Personagens::Jogadores::Jogador(sf::Vector2f(100.0f, 100.0f));
	jogador2 = (numJogadores == 2)
		? new Entidades::Personagens::Jogadores::Jogador(sf::Vector2f(160.0f, 100.0f))
		: nullptr;

	if (numFase == 1) faseAtual = new Jogo::Fases::FasePrimeira(jogador1, jogador2, true);
	else if (numFase == 2) faseAtual = new Jogo::Fases::FaseSegunda(jogador1, jogador2, true);

	if (!faseAtual) printf("Erro ao carregar fase %d\n", numFase);
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

		int numFase;
		bool carregar = false;

		if (escolha == 1 || escolha == 2)
		{
			numJogadores = menu.getNumJogadores();   // 1 ou 2, para esta partida
			numFase = escolha;
		}
		else if (escolha == 3)   // "Continuar" -> carrega o jogo salvo
		{
			ifstream save("save.txt");
			int numFaseSalva, numJogSalvos;
			if (!save.is_open() || !(save >> numFaseSalva >> numJogSalvos))
			{
				cout << "Nenhum jogo salvo para continuar." << endl;
				continue;                         // volta ao menu
			}
			save.close();
			numFase = numFaseSalva;
			numJogadores = numJogSalvos;
			carregar = true;
		}
		else
		{
			continue;                             // valor inesperado: reexibe o menu
		}

		bool jogando = true;
		while (jogando && pGrafico->verificaJanelaAberta())
		{
			if (carregar)
			{
				carregarFase(numFase);   // primeira fase vem do save
				carregar = false;        // proximas fases sao geradas normalmente
			}
			else
			{
				criarFase(numFase);
			}
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
