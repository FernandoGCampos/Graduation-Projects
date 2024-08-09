public class Placar {
	private class Posicao{
		private int pontuacao;
		private boolean usado;
		
		private Posicao() {
			usado = false;
		}
	}
	private Posicao[] posicoes = new Posicao[10];
	public int pontuacao_total;
	
	public Placar(){
		pontuacao_total = 0;
		for(int i = 0; i < 10; ++i) {
			posicoes[i] = new Posicao();
		}
	}
	
	public void add(int posicao, int[] dados) {
		int[] repeticoes = new int[] {0, 0, 0, 0, 0, 0};
		for(int i = 0; i < 5; ++i) {
			repeticoes[dados[i] - 1] += 1;
		}
		
		//Assegura que a posição escolhida é válida
		int posicao_escolhida = posicao;
		while(posicao_escolhida < 1 || posicao_escolhida > 10 || posicoes[posicao_escolhida-1].usado) {
			System.out.printf("A posição escolhida já foi usada ou não é válida, escolha outra ===> ");
			
			//Le a entrada e repete caso o valor digitado não seja um inteiro
			while(true) {
				try {
					posicao_escolhida = EntradaTeclado.leInt();
				} catch (Exception e){
					System.out.printf("O valor digitado não é um número inteiro, tente novamente ===> ");
					continue;
				}
				break;
			}
		}
		System.out.printf("\n");
		
		//Contabiliza os pontos na posição escolhida
		switch(posicao_escolhida) {
		
			case 1:{
				posicoes[0].usado = true;
				posicoes[0].pontuacao = repeticoes[0];
				pontuacao_total += posicoes[0].pontuacao;
			}
			break;
			
			case 2:{
				posicoes[1].usado = true;
				posicoes[1].pontuacao = 2 * repeticoes[1];
				pontuacao_total += posicoes[1].pontuacao;
			}
			break;
			
			case 3:{
				posicoes[2].usado = true;
				posicoes[2].pontuacao = 3 * repeticoes[2];
				pontuacao_total += posicoes[2].pontuacao;
			}
			break;
			
			case 4:{
				posicoes[3].usado = true;
				posicoes[3].pontuacao = 4 * repeticoes[3];
				pontuacao_total += posicoes[3].pontuacao;
			}
			break;
			
			case 5:{
				posicoes[4].usado = true;
				posicoes[4].pontuacao = 5 * repeticoes[4];
				pontuacao_total += posicoes[4].pontuacao;
			}
			break;
			
			case 6:{
				posicoes[5].usado = true;
				posicoes[5].pontuacao = 6 * repeticoes[5];
				pontuacao_total += posicoes[5].pontuacao;
			}
			break;
			
			case 7:{
				posicoes[6].usado = true;
				boolean par = false;
				boolean trio = false;
				for(int i = 0; i < 6; ++i) {
					if(repeticoes[i] == 2) {
						par = true;
					}
					if(repeticoes[i] == 3) {
						trio = true;
					}
					if(repeticoes[i] == 5) {
						par = true;
						trio = true;
					}
				}
				if(par && trio) {
					posicoes[6].pontuacao = 15;
				}
				else {
					posicoes[6].pontuacao = 0;
				}
				pontuacao_total += posicoes[6].pontuacao;
			}
			break;
			
			case 8:{
				posicoes[7].usado = true;
				int sequencia1 = repeticoes[0];
				int sequencia2 = repeticoes[5];
				for(int i = 1; i < 5; ++i) {
					sequencia1 *= repeticoes[i];
					sequencia2 *= repeticoes[i];
				}
				
				if(sequencia1 == 1 || sequencia2 == 1) {
					posicoes[7].pontuacao = 20;
				}
				else {
					posicoes[7].pontuacao = 0;
				}
				pontuacao_total += posicoes[7].pontuacao;
			}
			break;
			
			case 9:{
				posicoes[8].usado = true;
				if(repeticoes[0] == 4 ||
				   repeticoes[1] == 4 ||
				   repeticoes[2] == 4 ||
				   repeticoes[3] == 4 ||
				   repeticoes[4] == 4 ||
				   repeticoes[5] == 4  ) {
					
					posicoes[8].pontuacao = 30;
				}
				else {
					posicoes[8].pontuacao = 0;
				}
				pontuacao_total += posicoes[8].pontuacao;
			}
			break;
			
			case 10:{
				posicoes[9].usado = true;
				if(repeticoes[0] == 5 ||
				   repeticoes[1] == 5 ||
				   repeticoes[2] == 5 ||
				   repeticoes[3] == 5 ||
				   repeticoes[4] == 5 ||
				   repeticoes[5] == 5  ) {
					
					posicoes[9].pontuacao = 40;
				}
				else {
					posicoes[9].pontuacao = 0;
				}
				pontuacao_total += posicoes[9].pontuacao;
			}
		}
	}
	
	public int getScore() {
		return pontuacao_total;
	}
	
	@Override
	public java.lang.String toString(){
		String impressao = "";
		
		//Imprime a primeira posição
		if(posicoes[0].usado) {
			impressao += String.format("%-3d", posicoes[0].pontuacao);
			
		}
		else {
			impressao += "(1)"; 
		}
		impressao += "    |   ";
		
		//Imprime a sétima posição
		if(posicoes[6].usado) {
			impressao += String.format("%-3d", posicoes[6].pontuacao);
			
		}
		else {
			impressao += "(7)";
		}
		impressao += "    |   ";
				
		//Imprime a quarta posição
		if(posicoes[3].usado) {
			impressao += String.format("%-3d", posicoes[3].pontuacao);
			
		}
		else {
			impressao += "(4)";
		}
		impressao += " \n--------------------------\n";
		
		//Imprime a segunda posição
		if(posicoes[1].usado) {
			impressao += String.format("%-3d", posicoes[1].pontuacao);
			
		}
		else {
			impressao += "(2)";
		}
		impressao += "    |   ";
		
		//Imprime a oitava posição
		if(posicoes[7].usado) {
			impressao += String.format("%-3d", posicoes[7].pontuacao);
			
		}
		else {
			impressao += "(8)";
		}
		impressao += "    |   ";
				
		//Imprime a quinta posição
		if(posicoes[4].usado) {
			impressao += String.format("%-3d", posicoes[4].pontuacao);
			
		}
		else {
			impressao += "(5)";
		}
		impressao += " \n--------------------------\n";
		
		//Imprime a terceira posição
		if(posicoes[2].usado) {
			impressao += String.format("%-3d", posicoes[2].pontuacao);
			
		}
		else {
			impressao += "(3)";
		}
		impressao += "    |   ";
		
		//Imprime a nona posição
		if(posicoes[8].usado) {
			impressao += String.format("%-3d", posicoes[8].pontuacao);
			
		}
		else {
			impressao += "(9)";
		}
		impressao += "    |   ";
				
		//Imprime a sexta posição
		if(posicoes[5].usado) {
			impressao += String.format("%-3d", posicoes[5].pontuacao);
			
		}
		else {
			impressao += "(6)";
		}
		impressao += " \n--------------------------\n";
		impressao += "       |   ";
		
		//Imprime a décima posição
		if(posicoes[9].usado) {
			impressao += String.format("%-4d", posicoes[9].pontuacao);
			
		}
		else {
			impressao += "(10)";
		}
		impressao += "   |\n       +----------+\n";
		
		return impressao;
	}
}