import java.io.IOException; 

public class Bozo {
	
	public static void main(java.lang.String[] args) throws IOException {
		Placar placar = new Placar();
		int[] dados_rolados = new int[5];
		RolaDados dados = new RolaDados(5);
		
		for(int i = 0; i < 10; ++i) {
			System.out.printf("****** Rodada %d\n", i);
			System.out.printf("Pressione ENTER para lan�ar os dados\n");
			EntradaTeclado.leString();
			
			
			
			dados.rolar();
			System.out.println(dados.toString());
			for(int j = 0; j < 2; ++j) {
				System.out.printf("Digite os n�meros dos dados que quiser TROCAR. Separados por espa�o.\n");
				String trocas = EntradaTeclado.leString();
				dados_rolados = dados.rolar(trocas);
				System.out.println(dados.toString());
			}
			
			System.out.println(placar.toString());
			System.out.printf("Escolha a posi��o que quer ocupar com essa jogada ===> ");
			int posicao;
			
			//Le a entrada e repete caso o valor digitado n�o seja um inteiro
			while(true) {
				try {
					posicao = EntradaTeclado.leInt();
				} catch (Exception e){
					System.out.printf("O valor digitado n�o � um n�mero inteiro, tente novamente ===> ");
					continue;
				}
				break;
			}
			
			placar.add(posicao, dados_rolados);
			System.out.println(placar.toString());
		}
		System.out.printf("***********************************\n***\n");
		System.out.printf("*** Seu escore final foi: %d\n", placar.pontuacao_total);
		System.out.printf("***\n***********************************\n");
	}
	
}
