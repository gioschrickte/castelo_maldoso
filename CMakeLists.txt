cmake_minimum_required(VERSION 3.10)
project(cassetemaldoso)

# Define a versão do C++
set(CMAKE_CXX_STANDARD 17)

# Informa onde o SFML está instalado no seu computador
# Altere este caminho para a pasta onde você extraiu o SFML
set(SFML_DIR "C:/Users/gssar/Documentos/Estudos/UTFPR/tecprog/SFML-2.6.2/lib/cmake/SFML") 

# Encontra a biblioteca do SFML
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

# Adiciona o seu executável (liste todos os seus arquivos .cpp aqui)
add_executable(app main.cpp
Chefao.cpp
Ente.cpp
Entidade.cpp
Espinho.cpp
Fase.cpp
FasePrimeira.cpp
FaseSegunda.cpp
GerenciadorColisoes.cpp
GerenciadorEventos.cpp
GerenciadorGrafico.cpp
Inimigo.cpp
InimigoFacil.cpp
InimigoMedio.cpp
Jogador.cpp
Lama.cpp
ListaEntidade.cpp
Menu.cpp
Obstaculo.cpp
Personagem.cpp
Plataforma.cpp
Principal.cpp
Projetil.cpp
)

# Linka o SFML ao seu executável
target_link_libraries(app sfml-graphics sfml-window sfml-system)

# Linka a pasta /assets ao executável
add_custom_command(TARGET app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:app>/assets
)