import java.io.IOException;

public class Ex4 {

	public static void main(String[] args) throws IOException {
		int x;
		System.out.println("Digite o tamanho da árvore: ");
		x = EntradaTeclado.leInt();
		
		for(int i = 0; i < x; ++i) {
			for(int k = x-i; k < x; ++k) {
				System.out.printf(" ");
			}
			for(int j = x-i; j > 0; --j) {
				System.out.printf("*");
			}
			System.out.printf("\n");	
		}
	
	}
	
}
