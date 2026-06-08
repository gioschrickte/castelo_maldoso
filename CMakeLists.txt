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
add_executable(app
    src/main.cpp
    src/Chefao.cpp
    src/Ente.cpp
    src/Entidade.cpp
    src/Espinho.cpp
    src/Fase.cpp
    src/FasePrimeira.cpp
    src/FaseSegunda.cpp
    src/GerenciadorColisoes.cpp
    src/GerenciadorEventos.cpp
    src/GerenciadorGrafico.cpp
    src/Inimigo.cpp
    src/InimigoFacil.cpp
    src/InimigoMedio.cpp
    src/Jogador.cpp
    src/Lama.cpp
    src/ListaEntidade.cpp
    src/Menu.cpp
    src/Obstaculo.cpp
    src/Personagem.cpp
    src/Plataforma.cpp
    src/Principal.cpp
    src/Projetil.cpp
)

# Expõe a pasta include/ para todos os fontes
target_include_directories(app PRIVATE include)

# Linka o SFML ao seu executável
target_link_libraries(app sfml-graphics sfml-window sfml-system)

# Linka a pasta /assets ao executável
add_custom_command(TARGET app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:app>/assets
)