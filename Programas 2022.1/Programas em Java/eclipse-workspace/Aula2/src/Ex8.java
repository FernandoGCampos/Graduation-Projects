import java.io.IOException;

public class Ex8 {

	public static void main(String[] args) throws IOException {
		System.out.printf("Determine o chute inicial\n");
		double x = EntradaTeclado.leDouble();
		double result = (x * x * x) - (x * x) - (13 * x) + 8;
		double derivadaResult = (3 * x * x) - (2 * x) - 13;
		
		int iteracoes = 0;
		while(result > 0.0000001 || result < -0.0000001) {
			++iteracoes;
			x -= result / derivadaResult;
			result = (x * x * x) - (x * x) - (13 * x) + 8;
			derivadaResult = (3 * x * x) - (2 * x) - 13;
		}
		System.out.printf("%f é uma raíz da equação!\n", x);
		System.out.printf("O número de iterações foi: %d\n", iteracoes);
	}
}