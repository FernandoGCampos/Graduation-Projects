import java.io.IOException;

public class Ex1 {

	public static void main(String[] args) throws IOException {
		double x;
		System.out.println("Digite o valor do qual se quer a raiz: ");
		x = EntradaTeclado.leDouble();
		double x_raiz;
		System.out.println("Digite o chute inicial: ");
		x_raiz = EntradaTeclado.leDouble();
		double erro = 1;
		int i = 0;
		while(erro > 0.00000001 || erro < -0.00000001){
			erro = x_raiz - (x_raiz + (x / x_raiz))/2;
			x_raiz = (x_raiz + (x / x_raiz))/2;
			++i;
		}
		
		System.out.printf("A raiz de %f �: %f\n", x, x_raiz);
		System.out.printf("O n�mero de itera��es necess�rias foi: %d\n", i);
	}
	
}