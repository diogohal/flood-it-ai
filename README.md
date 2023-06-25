Autores:
Diogo Henriquel de Almeida GRR20210577
Natael Pontarolo Gomes GRR20211786

Para a resolução do problema, duas estratégias descritas logo abaixo foram utilizadas em diferentes estados do tabuleiro em uma máquina de Busca de Melhor Caminho, ou seja, uma máquina que usa apenas uma heurística para definir o peso da escolha e, posteriormente, definir o melhor caminho naquele dado momento.

Contagem de novas áreas acessadas. Essa é a heurística principal do programa, em que é contado novas áreas de acesso da área pintada para cada opção de cor. Á área acessada são os blocos pintados OU blocos que estão na margem da área pintada. Para definir esse peso, são realizadas duas contagens: antes e após pintar com a nova cor, de forma que a subtração é a quantidade de novas áreas acessadas. Em seguida, a opção de maior peso é escolhida.

Contagem de novos blocos pintados. Essa é a heurística secundária, utilizada quando o número de áreas sem acesso é inferior a 10. Por meio de testes empíricos, percebeu-se uma melhora ao utilizar essa outra heurística no final da execução do programa, obtendo um menor número de passos. Para definir esse peso, são realizadas duas contagens: antes e após pintar com a nova cor, de forma que a subtração é a quantidade de novos blocos pintados. Em seguida, a opção de maior peso é escolhida.

Nos arquivos nós disponiblizamos um script que permite testes de diversos mapas do jogo. Para rodá-lo, basta digitar ./script. Uma saída do ./geramapa com valores aleatórios para linhas, colunas e cores é gerada e, em seguida, jogada no arquivo mapa.txt. Essa instância é resolvida pela maquina de busca e a solução é armazenada no arquivo solution.txt. Por fim, o script usa o ./anima para ilustrar a execução da solução. Também é possível rodar vários testes sequencialmente, para isso só é preciso usar o comando watch -n 1 ./script.
