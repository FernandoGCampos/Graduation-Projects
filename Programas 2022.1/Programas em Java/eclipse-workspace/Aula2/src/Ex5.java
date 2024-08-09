import java.io.IOException;

public class Ex5 {

	public static void main(String[] args) throws IOException {
		int x;
		System.out.println("Digite o número do qual se quer saber o primeiro número primo menor que ele: ");
		x = EntradaTeclado.leInt();
		
		int j;
	    boolean procuraPrimo = true;
		for(j = x - 1; j > 1 && procuraPrimo; --j) {
			int i = 2;
			Double modulo = 1.0;
			for(i = 2; i < j && modulo != 0; ++i) {
				modulo = (double) j % i; 	
			}
			if(modulo != 0.0) {
				System.out.printf("O primeiro número primo menor que o número informado é: %d\n", j);
				procuraPrimo = false;
			}
		}
		if(procuraPrimo) {
			System.out.printf("O número %d não possui primos menores do que ele\n", x);
		}
	}
	
}