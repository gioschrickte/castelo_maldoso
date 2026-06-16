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
		zumbi,
		ork,
		mago
		// Adicione mais IDs conforme necessário
	};
}