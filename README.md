# FreeRTOS Posix Socket

## Tutorial de instalação

1. Baixar o freeRTOS FreeRTOS 202107.00
    - Link: https://www.freertos.org/a00104.html
    - Exatraia o arquivo do freeRTOS em uma pasta que você não irá modificar

2. Execute os comandos:
    - cd
    - echo export FREERTOS_PATH=caminho/nome_da_pasta_do_freeRTOS >> .bashrc
    - echo export FREERTOS_PATH=caminho/nome_da_pasta_do_freeRTOS >> .profile
    - source .bashrc
    - source .profile

3. Baixe este repositório em uma pasta de sua preferência
    - Opção 1: gh repo clone alankc/FreeRTOS_Posix_Socket
    - Opção 2: git clone https://github.com/alankc/FreeRTOS_Posix_Socket

4. Compile o projeto
    - Comando: make

5. Observação sobre o IP da caldeira
    - Se estiver no Linux,  o IP pode ser "localhost"
    - Se estiver usando WSL, abrindo a caldeira no Windows, o IP deve ser o IP do Windows
