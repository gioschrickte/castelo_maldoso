#include "GerenciadorColisoes.hpp"

Gerenciador::GerenciadorColisoes* Gerenciador::GerenciadorColisoes::pGC(nullptr);

Gerenciador::GerenciadorColisoes::GerenciadorColisoes() :
	LIs(), LOs(), pJog1(nullptr)
{
	// Aqui, o gerenciador de colisoes está com a lista de Inimigos e Objetos vazia, e o ponteiro para o jogador é nulo
}

Gerenciador::GerenciadorColisoes::~GerenciadorColisoes()
{
	vector<Entidades::Personagens::Inimigos::Inimigo*>::iterator it;
	it = LIs.begin();
	while (it != LIs.end())
	{
		delete* it;
		*it = nullptr;
		it = LIs.erase(it);
	}

	list<Entidades::Obstaculos::Obstaculo*>::iterator itO;
	itO = LOs.begin();
	while (itO != LOs.end())
	{
		delete* itO;
		*itO = nullptr;
		itO = LOs.erase(itO);
		it = LIs.erase(it);
	}
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

// Retorna penetração assinada:
// - componente > 0 = quantidade de sobreposição (penetration depth)
// - sinal indica direção (positivo: ent1 está à direita/abaixo de ent2)
const sf::Vector2f Gerenciador::GerenciadorColisoes::calculaColisao(Entidades::Entidade* ent1, Entidades::Entidade* ent2)
{
	sf::Vector2f pos1 = ent1->getCorpo().getPosition();
	sf::Vector2f pos2 = ent2->getCorpo().getPosition();

	sf::Vector2f tam1 = ent1->getCorpo().getSize();
	sf::Vector2f tam2 = ent2->getCorpo().getSize();

	sf::Vector2f centro1(pos1.x + tam1.x / 2.0f, pos1.y + tam1.y / 2.0f);
	sf::Vector2f centro2(pos2.x + tam2.x / 2.0f, pos2.y + tam2.y / 2.0f);

	sf::Vector2f delta(centro1.x - centro2.x, centro1.y - centro2.y);
	sf::Vector2f somaMeias(tam1.x / 2.0f + tam2.x / 2.0f, tam1.y / 2.0f + tam2.y / 2.0f);

	// overlap = somaMeias - |delta|  (positivo = sobreposição)
	float overlapX = somaMeias.x - fabs(delta.x);
	float overlapY = somaMeias.y - fabs(delta.y);

	// Assinar pela direção de delta: se delta >= 0 ent1 está à direita/abaixo, senão à esquerda/acima
	sf::Vector2f signedOverlap(
		(delta.x >= 0.0f) ? overlapX : -overlapX,
		(delta.y >= 0.0f) ? overlapY : -overlapY
	);

	return signedOverlap;
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
	// tratarColisoesEntsObstacs();
	tratarColisoesJogsObstacs();

}

void Gerenciador::GerenciadorColisoes::tratarColisoesJogsInimgs()
{
	// Checar se o jogador está colidindo com algum inimigo
	for (int i = 0; i < LIs.size(); i++)
	{
		bool col = verificarColisao(static_cast<Entidades::Entidade*>(pJog1), static_cast<Entidades::Entidade*>(LIs[i]));
		if (col) // se colidiu
		{
			LIs[i]->danificar(pJog1); // chama a função de danificar do inimigo, passando o jogador
		}
	}
}

void Gerenciador::GerenciadorColisoes::tratarColisoesJogsObstacs()
{// Checar se o jogador está colidindo com algum obstáculo
	for (list<Entidades::Obstaculos::Obstaculo*>::iterator it = LOs.begin(); it != LOs.end(); ++it)
	{
		// calcula uma vez e reutiliza
		sf::Vector2f ds = calculaColisao(static_cast<Entidades::Entidade*>(pJog1), static_cast<Entidades::Entidade*>(*it));
		if (ds.x > 0.0f && ds.y > 0.0f) // se colidiu
		{
			// passa a penetração assinada para a rotina de resolução do jogador
			(*it)->obstaculizar(pJog1);
		}
	}
}

/*void Gerenciador::GerenciadorColisoes::tratarColisoesInimgsObstacs()
{
	// Checar se algum inimigo está colidindo com algum obstáculo
	for (int i = 0; i < LIs.size(); i++)
	{
		for (list<Entidade::Obstaculo::Obstaculo*>::iterator it = LOs.begin(); it != LOs.end(); ++it)
		{
			bool col = verificarColisao(static_cast<Entidade::Entidade*>(LIs[i]), static_cast<Entidade::Entidade*>(*it));
			if (col) // se colidiu
			{
				(*it)->obstaculizar(LIs[i]); // chama a função de obstaculizar do obstáculo, passando o inimigo
			}
		}
	}
}
*/