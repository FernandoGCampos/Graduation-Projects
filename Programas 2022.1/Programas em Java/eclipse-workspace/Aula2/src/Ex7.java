import java.io.IOException;

public class Ex7 {

	public static void main(String[] args) throws IOException {
		boolean achouResultado = false;
		while(!achouResultado){
			System.out.printf("Determine uma extremidade do intervalo\n");
			double x1 = EntradaTeclado.leDouble();
			System.out.printf("Determine a outra extremidade do intervalo\n");
			double x2 = EntradaTeclado.leDouble();
			
			double result1 = (x1 * x1 * x1) - (x1 * x1) - (13 * x1) + 8;
			double result2 = (x2 * x2 * x2) - (x2 * x2) - (13 * x2) + 8;
			if(result1 == 0 || result2 == 0) {
				achouResultado = true;
				if(result1 == 0) {
					System.out.printf("%f é uma raíz da equação!\n", x1);
				}
				if(result2 == 0) {
					System.out.printf("%f é uma raíz da equação!\n", x2);
				}
			}
			else if(result1 * result2 > 0) {
				System.out.printf("Os extremos do intervalo não possuem sinais contrários! Tente novamente.\n\n", x1);
			}
			else {
				achouResultado = true;
				double positivo;
				double negativo;
				if(result1 > 0) {
					positivo = x1;
					negativo = x2;
				}
				else {
					positivo = x2;
					negativo = x1;
				}
				double novoX = 10; 
				int iteracoes = 0;
				double novoXResult = 10;
				while(novoXResult > 0.0000001 || novoXResult < -0.0000001) {
					++iteracoes;
					novoX = (positivo + negativo)/2;
					novoXResult = (novoX * novoX * novoX) - (novoX * novoX) - (13 * novoX) + 8;
					if(novoXResult > 0) {
						positivo = novoX;
					}
					else {
						negativo = novoX;
					}
				}
				System.out.printf("%f é uma raíz da equação!\n", novoX);
				System.out.printf("O número de iterações foi: %d\n", iteracoes);
			}
		}	
	}
}