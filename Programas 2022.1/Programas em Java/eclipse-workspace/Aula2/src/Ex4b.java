import java.io.IOException;

public class Ex4b {

	public static void main(String[] args) throws IOException {
		int x;
		System.out.println("Digite o n�mero que se quer saber se ele � primo: ");
		x = EntradaTeclado.leInt();
		
		
		int i = 2;
		Double modulo = 1.0;
		for(i = 2; i < x && modulo != 0; ++i) {
			modulo = (double) x % i; 	
		}
		if(modulo == 0) {
			--i;
			System.out.printf("N�o � primo, pois � divis�vel por: %d\n", i);
		}
		else {
			System.out.printf("� primo\n");
		}
	
	}
	
}
