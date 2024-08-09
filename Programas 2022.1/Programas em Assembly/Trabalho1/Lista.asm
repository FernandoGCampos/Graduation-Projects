		.data
		
		.align 2
		
str1:		.asciiz "Digite um n�mero: "
str2:		.asciiz "Digite uma string de 30 caracteres: "
str3:		.asciiz " "
str4:		.asciiz "\n"

		.text
		.globl main


#=================================================================================
main:
		#Aloca mem�ria para a raiz
		li $v0, 9
		li $a0, 4
		syscall
		
		#Cria a raiz da lista
		move $s1, $v0
		
		#Buffer que salva o final do �ltimo elemento da lista (onde se deve colocar o ponteiro para o pr�ximo elemento) 
		move $s2, $s1
		
		#Cria o contador (i)
		li $s0, 0 
loop:
		#Verifica se i >= 5
		bge $s0, 5, fim_loop
		
		#Retorna um ponteiro para o novo elemento da lista
		jal add_new
		
		#Salva o ponteiro no �ltimo elemento da lista
		sw $v0, 0($s2)
		
		#Altera o buffer para o novo final da lista
		addi $s2, $v0, 8 
		
		#Incrementa o contador
		addi $s0, $s0, 1
		
		#Retorna para o come�o do loop
		j loop 
fim_loop:		
		
		#Passa a raiz como parametro para a fun��o de impress�o
		lw $a0, 0($s1)
		
		#Imprime todos os elementos da lista
		jal print_all
		
		#Encerra a execu��o do programa
		li $v0, 10 
		syscall
#====================================Fim main=====================================


#=================================================================================
#Adiciona um elemento � lista e retorna o seu ponteiro
add_new:
		#Salva o endere�o de retorno na pilha
		addi $sp, $sp, -4
		sw $ra, 0 ($sp)
		
		#Aloca mem�ria para 3 inteiros (n�mero, endere�o da string e ponteiro para o pr�ximo elemento)
		li $v0, 9
		li $a0, 12
		syscall
		move $s3, $v0
		
		#Pede a usu�rio paara digitar um n�mero
		li $v0, 4
		la $a0, str1
		syscall
		
		#Recebe o n�mero escrito pelo usu�rio e o coloca no elemento da lista
		li $v0, 5
		syscall
		sw $v0, 0($s3)
		
		#Pede a usu�rio para digitar uma string de at� 30 caracteres
		li $v0, 4
		la $a0, str2
		syscall
		
		#Aloca mem�ria para a string
		li $v0, 9
		li $a0, 31
		syscall
		move $t1, $v0
		
		#Le a string digitada pelo usu�rio e coloca o endere�o da string no elemento da lista
		li $v0, 8
		move $a0, $t1
		li $a1, 31
		syscall
		sw $t1, 4($s3)
		
		#Remove o pulo de linha caso a string seja menor que o tamanho m�ximo
		move $a0, $t1
		jal remove_new_line
		
		#Testa para ver se precisa imprimir um pulo de linha
		lb $t2, str4 		#Salva o valor de um pulo de linha em um registrador
		beq $t2, $v0, pass_new_line		 #Testa para ver se o �ltimo caracter � um pulo de linha
		
		#Imprime um pulo de linha caso a string tenha tamanho m�ximo	
		li $v0, 4
		la $a0, str4
		syscall

pass_new_line:
		#Retorna o endere�o do elemento
		move $v0, $s3
		
		#Retorna para a posi��o que chamou a fun��o
		lw $ra, 0 ($sp)
		addi $sp, $sp, 4
		jr $ra
#===================================Fim add_new===================================


#=================================================================================
#Remove o pulo de linha caso o tamanho da string seja menor que o tamanho m�ximo
remove_new_line:
		#Salva o endere�o de retorno na pilha
		addi $sp, $sp, -4
		sw $ra, 0 ($sp)
		
		#Salva o endere�o da string em um registrador tempor�rio
		move $t1, $a0
		
		#Salva o valor de um pulo de linha em um registrador
		lb $t2, str4
		
		#Cria o contador
		li $t0, 0
loop_remove:
		lb $t3, 0($t1)
		beq $t2, $t3, change_to_null		#Testa para ver se o caracter � um pulo de linha
		addi $t0, $t0, 1			#Incrementa o contador
		addi $t1, $t1, 1			#Incrementa o ponteiro
		beq $t0, 31, fim_loop_remove		#Verifica se chegou no final da string
		b loop_remove

#Substitui o pulo de linha por um valor nulo ('\0')
change_to_null:
		sb $0, 0($t1)
		
fim_loop_remove:		
		
		#Retorna o valor do �ltimo caracter lido (para saber se precisa imprimir um pulo de linha)
		move $v0, $t3
		
		#Retorna para a posi��o que chamou a fun��o
		lw $ra, 0 ($sp)
		addi $sp, $sp, 4
		jr $ra
#===============================Fim remove_new_line===============================
	
			
#=================================================================================
#Imprime todos os elementos da lista
print_all:
		#Salva o endere�o de retorno na pilha
		addi $sp, $sp, -4
		sw $ra, 0 ($sp)
		
		#Salva o endere�o da raiz em um registrador tempor�rio
		move $t1, $a0
		
		#Cria o contador
		li $t0, 0
loop_print:
		#Verifica se i >= 5
		bge $t0, 5, fim_loop_print
		
		#Imprime o n�mero
		li $v0, 1
		lw $a0, 0 ($t1)
		syscall
		
		#Imprime um espa�o
		li $v0, 4
		la $a0, str3
		syscall
		
		#Imprime a string
		li $v0, 4
		lw $a0, 4($t1)
		syscall
		
		#Imprime um pulo de linha
		li $v0, 4
		la $a0, str4
		syscall
		
		#Incrementa o contador
		addi $t0, $t0, 1
		
		#Move o ponteiro para o pr�ximo elemento da lista
		lw $t1, 8($t1)
		
		#Retorna para o come�o do loop
		j loop_print
fim_loop_print:		
		
		#Retorna para a posi��o que chamou a fun��o
		lw $ra, 0 ($sp)
		addi $sp, $sp, 4
		jr $ra
#==================================Fim print_all==================================