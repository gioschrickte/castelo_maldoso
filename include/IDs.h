#pragma once

namespace IDs {
	enum class IDs {
		vazio = 0,
		jogador,
		inimigo,
		plataforma,
		chao,
		lama,
		espinho,
		// Ids distintos por tipo de inimigo (usados para recriar na carga do save)
		inimigoFacil,
		inimigoMedio,
		chefao
		// Adicione mais IDs conforme necessário
	};
}