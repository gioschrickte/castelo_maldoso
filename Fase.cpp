#include "Fase.hpp"

Jogo::Fases::Fase::Fase(Entidades::Personagens::Jogadores::Jogador* jogador, Entidades::Personagens::Jogadores::Jogador* j2)
	: Ente(), listaEntidade(), GerenciadorColisoes(Gerenciador::GerenciadorColisoes::getGerenciadorColisoes()), GerenciadorEventos(Gerenciador::GerenciadorEvento::getGerenciadorEvento()), jog1(jogador), jog2(j2)
{
	criarCenario();
	listaEntidade.addEntidade(static_cast<Entidades::Entidade*>(jog1));
	if (jog2) {
		listaEntidade.addEntidade(static_cast<Entidades::Entidade*>(jog2));
	}

	GerenciadorEventos->setJogador(jog1);
	GerenciadorColisoes->setJogador1(jog1);
	// falta GerenciadorEventos->setJogador(jog2); depois de implementar o segundo jogador
}

Jogo::Fases::Fase::~Fase()
{
	// Como quem está criando as entidades é a fase, ela é responsável por destruí-las, para evitar vazamento de memória
	for (int i = 0; i < listaEntidade.getTam(); i++)
	{
		delete listaEntidade[i];
	}

	GerenciadorColisoes->limpar();
}

void Jogo::Fases::Fase::criarCenario()
{
	// Cria o cenário da fase, ou seja, os obstáculos e inimigos. Será chamada no construtor da fase, e depois poderá ser chamada para criar um novo cenário, caso a fase seja reiniciada
	criarInimigosFaceis();
	criarPlataformas();

	// Perceba que está apenas criando os elementos básicos, mas não os desenha, isso será tratado no loop executar() da fase que será chamado na Principal.
}

void Jogo::Fases::Fase::criarInimigosFaceis()
{
	// Cria em posições aleatórias inimigos
	for (int i = 0; i < 5; i++)
	{
		Entidades::Personagens::Inimigos::Inimigo* inimigo = new Entidades::Personagens::Inimigos::Inimigo(jog1, sf::Vector2f(rand() % 700 + 50.0f, rand() % 700 + 50.0f));
		listaEntidade.addEntidade(static_cast<Entidades::Entidade*>(inimigo));
		GerenciadorColisoes->incluirInimigo(inimigo);
	}
}

void Jogo::Fases::Fase::criarPlataformas()
{
	// Cria em posições aleatórias plataformas
	for (int i = 0; i < 5; i++)
	{
		Entidades::Obstaculos::Plataforma* plataforma = new Entidades::Obstaculos::Plataforma(sf::Vector2f(rand() % 700 + 50.0f, rand() % 700 + 50.0f), sf::Vector2f(200.0f, 20.0f));
		listaEntidade.addEntidade(static_cast<Entidades::Entidade*>(plataforma));
		GerenciadorColisoes->incluirObstaculo(plataforma);
	}
}

void Jogo::Fases::Fase::executar()
{
	// Código que era antes da principal, mas agora está na fase, para que cada fase possa ter um cenário diferente, e o loop de jogo seja tratado pela fase, e não pela principal

	while (pGG->verificaJanelaAberta()) {
		GerenciadorEventos->executar();
		pGG->limpaJanela();
		GerenciadorColisoes->executar();

		// Novamente, esse trabalho será da classe Fase, que chamará o método executar de cada entidade, e depois pedirá para o gerenciador gráfico desenhá-las

		// A principal, então, seria responsável apenas por executar as fases

		for (int i = 0; i < listaEntidade.getTam(); i++)
		{
			listaEntidade[i]->executar();
			listaEntidade[i]->desenhar();
		}

		pGG->mostraElementos();
	}
}