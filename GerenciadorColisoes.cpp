#include "GerenciadorColisoes.hpp"

Gerenciador::GerenciadorColisoes* Gerenciador::GerenciadorColisoes::pGC(nullptr);

Gerenciador::GerenciadorColisoes::GerenciadorColisoes() :
	LIs(), LOs(), pJog1(nullptr)
{
	// Aqui, o gerenciador de colisoes está com a lista de Inimigos e Objetos vazia, e o ponteiro para o jogador é nulo
}

Gerenciador::GerenciadorColisoes::~GerenciadorColisoes()
{
}

Gerenciador::GerenciadorColisoes* Gerenciador::GerenciadorColisoes::getGerenciadorColisoes()
{
	if (pGC == nullptr)
	{
		pGC = new Gerenciador::GerenciadorColisoes();
		return pGC;
	}
	return pGC;
}

void Gerenciador::GerenciadorColisoes::setJogador1(Entidades::Personagens::Jogadores::Jogador* p)
{
	// Será necessária edição depois para incluir um segundo jogador
	pJog1 = p;
}

void Gerenciador::GerenciadorColisoes::incluirInimigo(Entidades::Personagens::Inimigos::Inimigo* pInim)
{
	if (pInim)
	{
		LIs.push_back(pInim);
	}
	else
		printf("Erro, pInim Nulo");
}

void Gerenciador::GerenciadorColisoes::incluirObstaculo(Entidades::Obstaculos::Obstaculo* pObst)
{
	if (pObst)
	{
		LOs.push_back(pObst);
	}
	else
	{
		printf("Erro, pObst nulo");
	}
}

const sf::Vector2f Gerenciador::GerenciadorColisoes::calculaColisao(Entidades::Entidade* ent1, Entidades::Entidade* ent2)
{
	sf::Vector2f pos1 = ent1->getCorpo().getPosition();
	sf::Vector2f pos2 = ent2->getCorpo().getPosition();
	sf::Vector2f tam1 = ent1->getCorpo().getSize();
	sf::Vector2f tam2 = ent2->getCorpo().getSize();

	sf::Vector2f centro1(pos1.x + tam1.x / 2.0f, pos1.y + tam1.y / 2.0f);
	sf::Vector2f centro2(pos2.x + tam2.x / 2.0f, pos2.y + tam2.y / 2.0f);

	float overlapX = (tam1.x / 2.0f + tam2.x / 2.0f) - fabs(centro1.x - centro2.x);
	float overlapY = (tam1.y / 2.0f + tam2.y / 2.0f) - fabs(centro1.y - centro2.y);

	// ambos > 0  =>  há colisão. Valores são as profundidades de penetração.
	return sf::Vector2f(overlapX, overlapY);
}

// Agora considera colisão quando penetração em X e Y for positiva
const bool Gerenciador::GerenciadorColisoes::verificarColisao(Entidades::Entidade* ent1, Entidades::Entidade* ent2)
{
	sf::Vector2f ds = calculaColisao(ent1, ent2);
	if (ds.x > 0.0f && ds.y > 0.0f)
		return true;
	return false;
}

void Gerenciador::GerenciadorColisoes::executar() {
	// Tratar de todas as colisões

	tratarColisoesJogsInimgs();
	tratarColisoesInimgsObstacs();
	tratarColisoesJogsObstacs();

}

void Gerenciador::GerenciadorColisoes::tratarColisoesJogsInimgs()
{
	if (!pJog1)
	{
		printf("Erro, pJog1 nulo");
		return;
	}
	// Checar se o jogador está colidindo com algum inimigo
	for (int i = 0; i < LIs.size(); i++)
	{
		bool col = verificarColisao(static_cast<Entidades::Entidade*>(pJog1), static_cast<Entidades::Entidade*>(LIs[i]));
		if (col) // se colidiu
		{
			pJog1->colidir(LIs[i]); // chama a função de colidir do jogador, passando o inimigo
		}
	}
}

void Gerenciador::GerenciadorColisoes::tratarColisoesJogsObstacs()
{
	if (!pJog1)
	{
		printf("Erro, pJog1 nulo");
		return;
	}

	// Checar se o jogador está colidindo com algum obstáculo
	for (list<Entidades::Obstaculos::Obstaculo*>::iterator it = LOs.begin(); it != LOs.end(); ++it)
	{
		// calcula uma vez e reutiliza
		sf::Vector2f ds = calculaColisao(static_cast<Entidades::Entidade*>(pJog1), static_cast<Entidades::Entidade*>(*it));
		if (ds.x > 0.0f && ds.y > 0.0f) // se colidiu
		{
			// passa a penetração assinada para a rotina de resolução do jogador
			(*it)->resolverColisao(pJog1, ds);
		}
	}
}


void Gerenciador::GerenciadorColisoes::tratarColisoesInimgsObstacs() {
	for (list<Entidades::Obstaculos::Obstaculo*>::iterator itO = LOs.begin(); itO != LOs.end(); ++itO) {
		if ((*itO)->afetaInimigos()) { // se o obstáculo afeta inimigos, ou seja, eles colidem com ele e são empurrados para fora
			for (int i = 0; i < LIs.size(); i++) {
				sf::Vector2f ds = calculaColisao(static_cast<Entidades::Entidade*>(LIs[i]), static_cast<Entidades::Entidade*>(*itO));
				if (ds.x > 0.0f && ds.y > 0.0f) { // se colidiu
					(*itO)->resolverColisao(LIs[i], ds); // passa a penetração assinada para a rotina de resolução do inimigo
				}
			}
		}
	}
}


void Gerenciador::GerenciadorColisoes::limpar()
{
	// Limpa as listas de inimigos e obstáculos, para evitar vazamento de memória. Será chamada no destrutor da fase, para limpar os elementos da fase anterior, caso a fase seja reiniciada.
	for (int i = 0; i < LIs.size(); i++)
	{
		delete LIs[i];
	}
	LIs.clear();
	for (list<Entidades::Obstaculos::Obstaculo*>::iterator it = LOs.begin(); it != LOs.end(); ++it)
	{
		delete* it;
	}
	LOs.clear();
}