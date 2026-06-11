#include "Lama.h"
#include <fstream>



Entidades::Obstaculos::Lama::Lama(const sf::Vector2f pos, const sf::Vector2f tam)
	: Entidades::Obstaculos::Obstaculo(pos, tam, IDs::IDs::lama)
{
	corpo.setFillColor(sf::Color(100, 70, 30)); // marrom
	multiplicadorVelocidade = 0.4f; // anda a 40% da velocidade normal
	multiplicadorPulo = 0.5f; // pula com metade da forca
	danoso = false; 
}

Entidades::Obstaculos::Lama::~Lama() {}

void Entidades::Obstaculos::Lama::resolverColisao(Personagens::Personagem* p, sf::Vector2f ds)
{
	p->aplicarLentidao(multiplicadorVelocidade, multiplicadorPulo);

	// poderia ter algum efeito visual 
}

void Entidades::Obstaculos::Lama::salvar()
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

void Entidades::Obstaculos::Lama::salvarDataBuffer()
{
	Entidades::Obstaculos::Obstaculo::salvarDataBuffer();
	//mais nada pra salvar, so posiçao e Id
}

