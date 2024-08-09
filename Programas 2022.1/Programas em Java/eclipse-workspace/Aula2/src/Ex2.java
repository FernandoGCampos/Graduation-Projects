public class Ex2 {

	public static void main(String[] args){
		double a, b, c;
		
		while(true)
		{
			System.out.println("Digite o valor de \"a\" para uma equação de segundo grau: ");
			try {
				a = EntradaTeclado.leDouble();
				break;
			}
			catch(Exception e) {
				System.out.println("O valor digitado não é um número, tente novamente\n");
			}
		}
		
		while(true)
		{
			System.out.println("Digite o valor de \"b\" para uma equação de segundo grau: ");
			try {
				b = EntradaTeclado.leDouble();
				break;
			}
			catch(Exception e) {
				System.out.println("O valor digitado não é um número, tente novamente\n");
			}
		}
		while(true)
		{
			System.out.println("Digite o valor de \"c\" para uma equação de segundo grau: ");
			try {
				c = EntradaTeclado.leDouble();
				break;
			}
			catch(Exception e) {
				System.out.println("O valor digitado não é um número, tente novamente\n");
			}
		}
		if(a == 0) {
			if(b == 0) {
				System.out.printf("Isso não é uma equação, apenas um número solto");
			}
			else {
				System.out.printf("A raiz da equação é: %f\n", -c/b);
			}
			
		}
		else {
			double raiz1;
			double raiz2;
			double delta;
			delta = (b * b) - (4 * a * c);
			if(delta < 0) {
				System.out.printf("A equação não possui raizes\n");
			}
			else {
				double delta_raiz;
				double erro = 1;
				if(delta == 2 || delta == -2) {
					delta_raiz = 1.5;
				}
				else {
					delta_raiz = delta / 2;
				}
				while(erro > 0.0000001 || erro < -0.0000001){
					erro = delta_raiz - (delta_raiz + (delta / delta_raiz))/2;
					delta_raiz = (delta_raiz + (delta / delta_raiz))/2;
				}
				
				raiz1 = (-b + delta_raiz) / 2 * a;
				raiz2 = (-b - delta_raiz) / 2 * a;
				System.out.printf("As raizes da equação são: %f e %f\n", raiz1, raiz2);
			}
		}
	}
	
}
