
					.data
					.align 0
			true_string:	.asciiz "As duas strings digitadas são iguas.\n"
			false_string:	.asciiz "As duas strings digitadas são diferentes.\n"
			ask1:		.asciiz "Digite a primeira string: "
			ask2:		.asciiz "Digite a segunda string: "
			string1:	.space 50
			string2:	.space 50
			
					
					.text
					.globl main
	main:
					# Printa a mensagem pedindo pela primeira string
					li $v0, 4
					la $a0, ask1
					syscall
					
					# Le a primeira string
					li $v0, 8
					la $a0, string1
					li $a1, 50
					syscall
					
					# Move o endereço inicial dela para $s0 o qual é agora equivalente à string1[0]
					move $s0, $a0
					# $t0 agora armazena o valor contido em string1[0]
					lb $t0, 0($s0)
					
					# Contador que vai armazenar o tamanho da string1
					li $t8, 0
			
			count1:
				beqz $t0, fim_count1 # Loop { -----
					
					addi $t8, $t8, 1
					
					addi $s0, $s0, 1
					lb $t0, 0($s0)
					
				j count1 # ----- }
					
			fim_count1:	
					
					# Printa a mensagem pedindo pela segunda string
					li $v0, 4
					la $a0, ask2
					syscall
					
					# Le a segunda string
					li $v0, 8
					la $a0, string2
					li $a1, 50
					syscall
					
					# Move o endereço inicial dela para $s1 o qual é agora equivalente à string2[0]
					move $s1, $a0
					# $t1 agora armazena o valor contido em string2[0]
					lb $t1, 0($s1)
					
					# Contador que vai armazenar o tamanho da string1
					li $t9, 0
					
			count2:
				beqz $t1, fim_count2 # Loop { -----
					
					addi $t9, $t9, 1
					
					addi $s1, $s1, 1
					lb $t1, 0($s1)
					
				j count2 # ----- }
			
			fim_count2: 
					# Se o tamanho das duas strings não são iguais então elas não são iguais
					bne $t8, $t9, fim_programa_false
			
					# Reinicia a posição de $s0 e $s1
					la $s0, string1
					la $s1, string2
					
					# Armazena os valores associados ao começo (Index 0) das strings
					lb $t0, 0($s0)
					lb $t1, 0($s1)
			
			loop_compare:
				# Se o loop chegar até o \0 da string1 (e consequentemente da string2 por terem o mesmo tamanho)
				# as strings são iguais
					
				beqz $t0, fim_programa_true # Loop { -----
					
					#Se os valores não forem iguais as strings são diferentes
					bne $t0, $t1, fim_programa_false
					
					# Incrementa o valor dos indexes de ambas as strings
					addi $s0, $s0, 1
					addi $s1, $s1, 1
					
					# Armazena os valores contidos no novos indexes
					lb $t0, 0($s0)
					lb $t1, 0($s1)
			
				j loop_compare # ----- }
				
				
	fim_programa_false:		# Final do programa se as strings forem diferentes
					li $v0, 4
					la $a0, false_string
					syscall
					
					li $v0, 10
					syscall
					
					
	fim_programa_true:		# Final do programa se as strings from iguais
					
					li $v0, 4
					la $a0, true_string
					syscall
					
					li $v0, 10
					syscall