# Programação Concorrente - Trabalho 1

## 0 - Como rodar esse programa
Para compilar o programa basta usar o comando `gcc aeroporto.c -o s -pthread`.

### Vídeo da Apresentaç˜ao oral do projeto
https://youtu.be/9GVyqJj8ktY

## 1 - Introdução
Em um dado aeroporto, pilotos disputam o acesso as pistas de pouso e aos portões de estacionamento. Logicamente, um piloto não pode pousar sem que uma pista de pouso esteja liberada. De modo semelhante, um avião não pode decolar nem pousar sem que exista alguma pista disponível para ele.  
Elabore uma solução para esse problema de tal forma que os pilotos consigam se organizar e acessar as pistas corretamente!

## 2 - Formalização do problema proposto
Existe um aeroporto com N pistas de pouso/decolagem, M aviões e K portões. Cada pista pode ser usada por um avião de cada vez, e cada portão pode abrigar até um avião em terra, de modo que se todos os portões estiverem ocupados nenhum avião pode pousar.  
Similarmente, se todas as pistas estiverem ocupadas nenhum avião pode pousar, mas decolagens podem continuar ocorrendo a fim de liberar portões.  

## 3 - Descrição do Algoritmo Desenvolvido para Soluç˜ao do Problema Proposto
O problema foi resolvido com a implementação de variáveis de condição. A solução consiste na criação de uma variável de condição de fim geral, que bloqueia o acesso a pista quando não houver nenhuma pista disponível, e outra de uso específico para bloquear o acesso a pista de aviões em voo quando não houver nenhum portão disponível. Ao verificar primeiro o acesso as pistas e em seguida o acesso aos portões, é possível implementar um sistema de prioridade em que aviões que garante que, quando não houver portões disponíveis, os aviões terão prioridade para decolar, e nos demais casos não existe prioridade.  

## 4 - Conclusão
O problema proposto demonstrou atender aos objetivos enquanto um problema de concorrência. Apesar de a solução implementada ter utilizado variáveis de condição, seria possível resolver esse mesmo problema com outras ferramentas vistas em sala de aula.  
Com base nisso, concluo que o trabalho teve um resultado positivo

## 5 - Referências
Problemas resolvidos em sala de aula



