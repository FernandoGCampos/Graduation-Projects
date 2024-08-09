		.data
		
		.align 2
		
str1:		.asciiz "Digite um número: "
str2:		.asciiz "Digite uma string de 30 caracteres: "
str3:		.asciiz " "
str4:		.asciiz "\n"

		.text
		.globl main


#=================================================================================
main:
		#Aloca memória para a raiz
		li $v0, 9
		li $a0, 4
		syscall
		
		#Cria a raiz da lista
		move $s1, $v0
		
		#Buffer que salva o final do último elemento da lista (onde se deve colocar o ponteiro para o próximo elemento) 
		move $s2, $s1
		
		#Cria o contador (i)
		li $s0, 0 
loop:
		#Verifica se i >= 5
		bge $s0, 5, fim_loop
		
		#Retorna um ponteiro para o novo elemento da lista
		jal add_new
		
		#Salva o ponteiro no último elemento da lista
		sw $v0, 0($s2)
		
		#Altera o buffer para o novo final da lista
		addi $s2, $v0, 8 
		
		#Incrementa o contador
		addi $s0, $s0, 1
		
		#Retorna para o começo do loop
		j loop 
fim_loop:		
		
		#Passa a raiz como parametro para a função de impressão
		lw $a0, 0($s1)
		
		#Imprime todos os elementos da lista
		jal print_all
		
		#Encerra a execução do programa
		li $v0, 10 
		syscall
#====================================Fim main=====================================


#=================================================================================
#Adiciona um elemento à lista e retorna o seu ponteiro
add_new:
		#Salva o endereço de retorno na pilha
		addi $sp, $sp, -4
		sw $ra, 0 ($sp)
		
		#Aloca memória para 3 inteiros (número, endereço da string e ponteiro para o próximo elemento)
		li $v0, 9
		li $a0, 12
		syscall
		move $s3, $v0
		
		#Pede a usuário paara digitar um número
		li $v0, 4
		la $a0, str1
		syscall
		
		#Recebe o número escrito pelo usuário e o coloca no elemento da lista
		li $v0, 5
		syscall
		sw $v0, 0($s3)
		
		#Pede a usuário para digitar uma string de até 30 caracteres
		li $v0, 4
		la $a0, str2
		syscall
		
		#Aloca memória para a string
		li $v0, 9
		li $a0, 31
		syscall
		move $t1, $v0
		
		#Le a string digitada pelo usuário e coloca o endereço da string no elemento da lista
		li $v0, 8
		move $a0, $t1
		li $a1, 31
		syscall
		sw $t1, 4($s3)
		
		#Remove o pulo de linha caso a string seja menor que o tamanho máximo
		move $a0, $t1
		jal remove_new_line
		
		#Testa para ver se precisa imprimir um pulo de linha
		lb $t2, str4 		#Salva o valor de um pulo de linha em um registrador
		beq $t2, $v0, pass_new_line		 #Testa para ver se o último caracter é um pulo de linha
		
		#Imprime um pulo de linha caso a string tenha tamanho máximo	
		li $v0, 4
		la $a0, str4
		syscall

pass_new_line:
		#Retorna o endereço do elemento
		move $v0, $s3
		
		#Retorna para a posição que chamou a função
		lw $ra, 0 ($sp)
		addi $sp, $sp, 4
		jr $ra
#===================================Fim add_new===================================


#=================================================================================
#Remove o pulo de linha caso o tamanho da string seja menor que o tamanho máximo
remove_new_line:
		#Salva o endereço de retorno na pilha
		addi $sp, $sp, -4
		sw $ra, 0 ($sp)
		
		#Salva o endereço da string em um registrador temporário
		move $t1, $a0
		
		#Salva o valor de um pulo de linha em um registrador
		lb $t2, str4
		
		#Cria o contador
		li $t0, 0
loop_remove:
		lb $t3, 0($t1)
		beq $t2, $t3, change_to_null		#Testa para ver se o caracter é um pulo de linha
		addi $t0, $t0, 1			#Incrementa o contador
		addi $t1, $t1, 1			#Incrementa o ponteiro
		beq $t0, 31, fim_loop_remove		#Verifica se chegou no final da string
		b loop_remove

#Substitui o pulo de linha por um valor nulo ('\0')
change_to_null:
		sb $0, 0($t1)
		
fim_loop_remove:		
		
		#Retorna o valor do último caracter lido (para saber se precisa imprimir um pulo de linha)
		move $v0, $t3
		
		#Retorna para a posição que chamou a função
		lw $ra, 0 ($sp)
		addi $sp, $sp, 4
		jr $ra
#===============================Fim remove_new_line===============================
	
			
#=================================================================================
#Imprime todos os elementos da lista
print_all:
		#Salva o endereço de retorno na pilha
		addi $sp, $sp, -4
		sw $ra, 0 ($sp)
		
		#Salva o endereço da raiz em um registrador temporário
		move $t1, $a0
		
		#Cria o contador
		li $t0, 0
loop_print:
		#Verifica se i >= 5
		bge $t0, 5, fim_loop_print
		
		#Imprime o número
		li $v0, 1
		lw $a0, 0 ($t1)
		syscall
		
		#Imprime um espaço
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
		
		#Move o ponteiro para o próximo elemento da lista
		lw $t1, 8($t1)
		
		#Retorna para o começo do loop
		j loop_print
fim_loop_print:		
		
		#Retorna para a posição que chamou a função
		lw $ra, 0 ($sp)
		addi $sp, $sp, 4
		jr $ra
#==================================Fim print_all==================================