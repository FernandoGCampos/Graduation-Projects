public class SegundoPrograma 
{

	public static void main(String[] args)
	{
		int k = 0;
		int x = 0;
		while(x==0)
		{
			x=1;
			System.out.printf("Digite um inteiro: ");
			try
			{
				k = EntradaTeclado.leInt();
			}
			catch(Exception e)
			{
				System.out.println("O valor que vc digitou n�o � um n�mero inteiro");
				x = 0;
			}
			
		}
		System.out.printf("Numero lido: %d\n", k);

	}

}
