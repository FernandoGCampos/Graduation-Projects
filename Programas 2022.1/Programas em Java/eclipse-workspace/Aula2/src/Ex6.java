import java.io.IOException;

public class Ex6 {

	public static void main(String[] args) throws IOException {
		double x = EntradaTeclado.leDouble();
		double menor = x;
		double maior = x;
		
		while(x != 0) {
			x = EntradaTeclado.leDouble();
			if(x != 0) {
				if(x < menor) {
					menor = x;
				}
				if(x > maior) {
					maior = x;
				}
			}
		}
		System.out.printf("O menor n�mero �: %f\n", menor);
		System.out.printf("O maior n�mero �: %f\n", maior);
	}	
}