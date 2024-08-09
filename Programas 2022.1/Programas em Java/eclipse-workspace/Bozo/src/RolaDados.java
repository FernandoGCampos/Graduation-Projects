import java.lang.Thread;  

public class RolaDados {
	private int numero_de_dados = 0;
	private Dado[] dados;
	
	public RolaDados(int n) {
		numero_de_dados = n;
		dados = new Dado[n];
		for(int i = 0; i < n; ++i) {
			dados[i] = new Dado();
			try{
				Thread.sleep(1); 
			} catch (Exception expn) {
				
			}
		}
	}
	
	public int[] rolar() {
		int[] valores = new int[numero_de_dados];
		for(int i = 0; i < numero_de_dados; ++i) {
			valores[i] = dados[i].rolar();
		}
		return valores;
	}
	
	public int[] rolar(boolean[] quais) {
		int[] valores = new int[numero_de_dados];
		for(int i = 0; i < numero_de_dados; ++i) {
			if(quais[i])
			{
				dados[i].rolar();
			}
			valores[i] = dados[i].lado;
		}
		return valores;
	}
	
	public int[] rolar(java.lang.String s) {
		boolean[] quais = new boolean[numero_de_dados];
		for(int i = 0; i < numero_de_dados; ++i) {
			quais[i] = false;
		}
		
		int tamanho = (s.length() + 2) / 2;
		String[] trocas = s.split(" ");
		for(int i = 0; i < tamanho; ++i) {
			int dado_escolhido;
			try {
				dado_escolhido = Integer.parseInt(trocas[i]);
			} catch (Exception e) {
				continue;
			}
			if(dado_escolhido - 1 < numero_de_dados && dado_escolhido > 0) {
				quais[dado_escolhido - 1] = true;
			}
		}
		
		int[] valores = new int[numero_de_dados];
		valores = rolar(quais);
		
		return valores;
	}
	
	@Override
	public java.lang.String toString(){
		String[] linha = new String[] {"", "", "", "", "", ""};
		
		linha[0] = "1         2         3         4         5         ";
		linha[1] = "+-----+   +-----+   +-----+   +-----+   +-----+   ";
		linha[5] = "+-----+   +-----+   +-----+   +-----+   +-----+   ";
		
		
		for(int i = 0; i < 5; ++i) {
			
			String[] dado_individual = dados[i].toString().split("\n");
			linha[2] += dado_individual[1];
			linha[3] += dado_individual[2];
			linha[4] += dado_individual[3];
		}

		String impressao = "";
		for(int i = 0; i < 6; ++i) {
			linha[i] += "\n";
			impressao += linha[i];
		}
		
		return impressao;
	}
}