#include "GerenciadorGrafico.hpp"

Gerenciador::GerenciadorGrafico* Gerenciador::GerenciadorGrafico::pGrafico(nullptr);


Gerenciador::GerenciadorGrafico::GerenciadorGrafico()
	: window(new sf::RenderWindow(sf::VideoMode(800.0f, 800.0f), "Teste"))
{
	if (window == NULL)
	{
		cout << "Falha na criação de janela! Encerrando programa..." << endl;
		exit(1);
	}
}

Gerenciador::GerenciadorGrafico::~GerenciadorGrafico()
{
	if (window)
	{
		delete(window);
		window = nullptr;
	}
}
Gerenciador::GerenciadorGrafico* Gerenciador::GerenciadorGrafico::getGerenciadorGrafico()
{
	if (pGrafico == nullptr)
	{
		pGrafico = new Gerenciador::GerenciadorGrafico(); // criação da instância única de GG
	}
	return pGrafico;
}
sf::RenderWindow* Gerenciador::GerenciadorGrafico::getWindow()
{
	return window;
}
void Gerenciador::GerenciadorGrafico::limpaJanela()
{
	window->clear();
}
void Gerenciador::GerenciadorGrafico::desenhaElemento(sf::RectangleShape corpo)
{
	window->draw(corpo);
}
void Gerenciador::GerenciadorGrafico::mostraElementos()
{
	window->display();
}
void Gerenciador::GerenciadorGrafico::fecharJanela()
{
	window->close();
}
const bool Gerenciador::GerenciadorGrafico::verificaJanelaAberta()
{
	return window->isOpen();
}

sf::Texture Gerenciador::GerenciadorGrafico::carregarTextura(const char* caminhoTextura)
{
	sf::Texture textura;
	if (!textura.loadFromFile(caminhoTextura))
	{
		std::cout << "ERRO, caminho da textura nao encontrado";
		exit(1);
	}
	return textura;
}