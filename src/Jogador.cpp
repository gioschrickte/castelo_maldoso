#include "Jogador.h"
#include "Inimigo.h"
#include "fstream"


//d
#define DURACAO_ATAQUE  0.05f
#define COOLDOWN_ATAQUE 0.5f
#define VIDA_JOGADOR

Entidades::Personagens::Jogadores::Jogador::Jogador(const sf::Vector2f pos, const sf::Vector2f tam)
	: Personagem(pos, tam, 200.0f, IDs::IDs::jogador), ataqueAtivo(false), danoAtaque(3.0f)
{
	corpo.setFillColor(sf::Color::Blue);
	
	textura = pGG->carregarTextura("assets/cavaleiro.png");
	sprite.setTexture(textura);

	sf::Vector2u tSz = textura.getSize();
	if (tSz.x > 0 && tSz.y > 0)
	{
		sprite.setScale(tam.x / tSz.x, tam.y / tSz.y);
	}

	sprite.setPosition(pos);
	temSprite = true;
	
	vidaMax = 100.0f;
	vida = vidaMax;
	barraVida.setFillColor(sf::Color::Red);
}

Entidades::Personagens::Jogadores::Jogador::~Jogador()
{

}


void Entidades::Personagens::Jogadores::Jogador::executar()
{
	float dt = calcularDt();
	if (podeAndar) atualizarX(dt);
	atualizarY(dt);

	if (ataqueAtivo && relogioAtaque.getElapsedTime().asSeconds() >= DURACAO_ATAQUE)
		ataqueAtivo = false;
}

void Entidades::Personagens::Jogadores::Jogador::atacar()
{
	if (relogioAtaque.getElapsedTime().asSeconds() >= COOLDOWN_ATAQUE) {
		relogioAtaque.restart();
		ataqueAtivo = true;
		std::cout << "Jogador atacou!\n";
	}
}

bool Entidades::Personagens::Jogadores::Jogador::estaAtacando() const { return ataqueAtivo; }
float Entidades::Personagens::Jogadores::Jogador::getDanoAtaque() const { return danoAtaque; }

void Entidades::Personagens::Jogadores::Jogador::colidir(Entidades::Personagens::Inimigos::Inimigo* inimigo)
{
	inimigo->danificar(this);
}

void Entidades::Personagens::Jogadores::Jogador::salvar()
{
	buffer.str("");
	buffer.clear();
	salvarDataBuffer();
	cout << "[SALVAR] " << buffer.str() << endl;//debug
	ofstream arquivo("save.txt", ios::app);
	
	if (!arquivo.is_open())//debug
    {
        cout << "[ERRO] nao foi possivel abrir o arquivo!" << endl;
        return;
    }

	arquivo << buffer.str() << "\n";
	arquivo.close();
	 
	cout << "[SALVAR] gravado com sucesso!" << endl;//debug
}

void Entidades::Personagens::Jogadores::Jogador::salvarDataBuffer()
{
	Entidades::Personagens::Personagem::salvarDataBuffer();

}
