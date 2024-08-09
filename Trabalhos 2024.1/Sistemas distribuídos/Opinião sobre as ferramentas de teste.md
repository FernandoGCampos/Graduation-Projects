**Não sei quão fácil seria usar essas ferramentas com o cluster, essas são opiniões sobre o quão fácil elas paracem ser de usar no computador normalmente.**

### Opções de monitoramento

Eu estou com a sensação que a ideia seria usar vária ferramentas, mas tanto faz.
|       | Prós  |Contras|
|-------|-------|-------|
|Dstat|- Não parece precisar de configuração<br/> - Com um comando no terminal ele solta todos os dados em uma tabela| - As tabelas geradas são muito feias <br/> - A gente não vai conseguir interpretar os dados dessas tabelas|
|Osquery| - Parece não precisar de muitas configurações <br/> - Busca dos dados utilizandoo comandos de query SQL| - Não sei quão conveniente é para pegar os dados durante operações <br/> - Não acho que tem tabelas para verificar tudo |
|Ganglia| | - O site para baixar é extremamente suspeito <br/> - Não achei uma documentação|
|Grafana| - A interface é perfeita <br/> - Parece ter como conseguir todos os dados necessários <br/> - A documentação parece ser boa|- Processo de configuração complicado <br/> - São várias ferramentas de verificação (Diferente para cada uma das ferramentas: docker, postgre, spark, kafka)|

### Teste de carga

|       | Prós  |Contras|
|-------|-------|-------|
|Benchmark|- Assumo que não teria que baixar nada | - Não tenho a menor ideia de como fazer isso|
|JMeter| - Funciona tanto para APIs REST quanto para o banco de dados <br/> - Eu achei uma pessoa que usou isso com o Spark, mas não falava nada de kafka nem de postgres | - Olhando a documentação eu não tenho a menor ideia de como usa <br/> - A documentação é bastante confusa|
|Locust| - Pelos exempos deles isso parece ser usado igual o JUnit, a gente define uma operação de APIs REST e ela é repetida várias vezes||
|Httperf| - Parece ser relativamente simples de utilizar| - Ele não tem um site, a documentação está inteiramente no github <br/> - Talvez o processo de instalação cause problemas|