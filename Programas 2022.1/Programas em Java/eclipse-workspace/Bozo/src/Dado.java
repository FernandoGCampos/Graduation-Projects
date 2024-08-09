public class Dado {
	
	private int numero_de_lados;
	public int lado;
	private Random r = new Random();
	
	public Dado() {
		numero_de_lados = 6;
	}
	
	public Dado(int tamanho) {
		numero_de_lados = tamanho;
	}
	
	public int rolar() {
		lado = r.getIntRand(numero_de_lados) + 1;
		return lado;
	}
	
	public int getLado() {
		return lado;
	}

	@Override
	public java.lang.String toString(){
	
		String[] linha = new String[5];
		linha[0] = "+-----+   \n";
		linha[4] = "+-----+   \n";
		switch(lado) {
			case 1:{
				linha[1] = "|     |   \n";
				linha[2] = "|  *  |   \n";
				linha[3] = "|     |   \n";
			}
			break;
			
			case 2:{
				linha[1] = "|*    |   \n";
				linha[2] = "|     |   \n";
				linha[3] = "|    *|   \n";
			}
			break;
			
			case 3:{
				linha[1] = "|*    |   \n";
				linha[2] = "|  *  |   \n";
				linha[3] = "|    *|   \n";
			}
			break;
			
			case 4:{
				linha[1] = "|*   *|   \n";
				linha[2] = "|     |   \n";
				linha[3] = "|*   *|   \n";
			}
			break;
			
			case 5:{
				linha[1] = "|*   *|   \n";
				linha[2] = "|  *  |   \n";
				linha[3] = "|*   *|   \n";
			}
			break;
			
			case 6:{
				linha[1] = "|* * *|   \n";
				linha[2] = "|     |   \n";
				linha[3] = "|* * *|   \n";
			}
			break;
			
			default:{
				linha[1] = "|     |   \n";
				linha[2] = "|ERROR|   \n";
				linha[3] = "|     |   \n";
			}
		}
		
		String impressao = linha[0] + linha[1] + linha[2] + linha[3] + linha[4];
		return impressao;
	}
}