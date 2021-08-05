# FreeRTOS Posix Socket
Universidade Federal de Santa Catarina

Disciplina: (DAS5306) Programação Concorrente e Sistemas de Tempo Real - Semestre 2021/1

Link para a página do professor: http://www.romulosilvadeoliveira.eng.br/discipli/cad-pcstr/cad-pcstr.html

Este repositório contém os arquivos para os alunos iniciarem o terceiro trabalho da disciplina.

## Pré-requisitos
Você irá precisar do compilador GCC e algumas bibliotecas.

    Se você estiver no Ubunto: sudo apt install build-essential
    Se você estiver no Fedora (abaixo do 23): yum install make automake gcc kernel-devel
    Se você estiver no Fedora (acima do 23): dnf install @development-tools
       
## Tutorial de Instalação
Os passos a seguir são válidos tanto para Linux puramente como Linux por WSL.

Caso você estiver usando WSL, os passos devem ser executados dentro do ambiente WSL.

1. Baixar o FreeRTOS 202107.00
    - Link: https://www.freertos.org/a00104.html
    - Extraia o arquivo do FreeRTOS em uma pasta que você não irá modificar
        - Abra o Ubunto WSL e você poderá acessar as pastas do Ubunto pelo explorer no caminho: \\\\wsl$

2. Abra o terminal e execute os comandos: 
    - cd
    - echo export FREERTOS_PATH=caminho_ate_FreeRTOS/nome_da_pasta_do_FreeRTOS >> .profile
        - Se o FreeRTOS estiver na pasta home: echo export FREERTOS_PATH=~/FreeRTOSv202107.00 >> .profile
    - source .profile

3. Baixe este repositório em uma pasta de sua preferência
    - Opção 1: gh repo clone alankc/FreeRTOS_Posix_Socket
    - Opção 2: git clone https://github.com/alankc/FreeRTOS_Posix_Socket

4. Com o terminal aberto na pasta deste repositório, compile e execute o projeto
    - Compilar: make
    - Executar: ./build/Posix_Socket

5. Observação sobre o IP da caldeira
    - Se você estiver usando Linux, o IP pode ser "localhost"
    - Se o pograma estiver rodando no WSL e a caldeira no Windows, o IP informado deve ser o IP do Windows
