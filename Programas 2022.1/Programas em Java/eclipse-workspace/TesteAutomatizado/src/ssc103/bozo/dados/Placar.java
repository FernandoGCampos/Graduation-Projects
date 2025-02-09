package ssc103.bozo.dados;

import java.util.Arrays;

/**
 * Esta classe representa o placar de um jogo de Boz�. Permite que combina��es
 * de dados sejam alocadas �s posi��es e mant�m o escore de um jogador.
 * @author delamaro
 *
 */
public class Placar {

	private final int POSICOES = 10;
	private int[] placar = new int[POSICOES];
	private boolean[] taken = new boolean[POSICOES];
	
	
	/**
	 * Adiciona uma sequencia de dados em uma determinada posi��o do placar.
	 * Ap�s a chamada, aquela posi��o torna-se ocupada e n�o pode ser usada uma segunda vez.
	 * @param posicao  Posi��o a ser preenchida. As posi��es 1 a 6 correspondem �s quantidas
	 * de uns at� seis, ou seja, as laterais do placar. As outas posi��es s�o: 7 - full hand;
	 * 8 - sequencia; 9 - quadra; e 10 - quina
	 * @param dados um array de inteiros, de tamanho 5. Cada posi��o corresponde a um valor 
	 * de um dado. Sup�es-se que cada dado pode ter valor entre 1 e 6. 
	 * @throws IllegalArgumentException - Se a posi��o estiver ocupada ou se for passado
	 * um valor de posi��o inv�lido, essa exce��o � lan�ada. N�o � feita nenhuma verifica��o
	 * quanto ao tamanho do array nem quanto ao seu conte�do. 
	 */
	public void add(int posicao, int[] dados) throws IllegalArgumentException
	{
		if (posicao < 1 || posicao > POSICOES)
			throw new IllegalArgumentException("Valor da posi��o ilegal");
		if ( taken[posicao-1] )
			throw new IllegalArgumentException("Posi��o ocupada no placar");
		int k = 0;
		switch (posicao)
		{
		case 1: k = conta(1, dados);
				break;
		case 2: k = 2 * conta(2, dados);
				break;
		case 3: k = 3 * conta(3, dados);
				break;
		case 4: k = 4 * conta(4, dados);
				break;
		case 5: k = 5 * conta(5, dados);
				break;
		case 6: k = 6 * conta(6, dados);
				break;
		case 7: // full hand
				if ( checkFull(dados) )
					k = 15;
				break;
		case 8: // sequencia
			if ( checkSeqMaior(dados) )
				k = 20;
			break;
		case 9: // quadra
			if ( checkQuadra(dados) )
				k = 30;
			break;
		case 10: // full hand
			if ( checkQuina(dados) )
				k = 40;
			break;
		}
		placar[posicao-1] = k;
		taken[posicao-1] = true;
	}
	
	/**
	 * Computa a soma dos valores obtidos, considerando apenas as posi��es que j� est�o ocupadas.
	 * @return - O valor da soma.
	 */
	public int getScore()
	{
		int t = 0;
		for (int i = 0; i < POSICOES; i++)
		{
			if (taken[i]) 
				t += placar[i];
		}
		return t;
	}
	
	
	private int conta(int n, int[] vet)
	{
		int cont = 0;
		for (int i: vet)
		{
			if (i == n ) cont++;
		}
		return cont;
	}
	
	private boolean checkFull(int[] dados)
	{
		int[] v = dados.clone();
		Arrays.sort(v);
		return ( v[0] == v[1] && v[1] == v[2] && v[3] == v[4]) ||
               ( v[0] == v[1] && v[2] == v[3] && v[3] == v[4]);
	}
	
	private boolean checkQuadra(int[] dados)
	{
		int[] v = dados.clone();
		Arrays.sort(v);
		return ( v[0] == v[1] && v[1] == v[2] && v[2] == v[3]) ||
               ( v[1] == v[2] && v[2] == v[3] && v[3] == v[4]);
	}
	
	private boolean checkQuina(int[] dados)
	{
		int[] v = dados;
		return ( v[0] == v[1] && v[1] == v[2] && v[2] == v[3] && v[3] == v[4]);
	}

	private boolean checkSeqMaior(int[] dados)
	{
		int[] v = dados.clone();
		Arrays.sort(v);
		return ( v[0]+1 == v[1] && v[1]+1 == v[2] && v[2]+1 <= v[3] && v[3]+1 == v[4]);
	}


	/**
	 * A representa��o na forma de string, mostra o placar completo, indicando quais s�o as
	 * posi��es livres (com seus respectivos n�meros) e o valor obtido nas posi��es j� ocupadas.
	 * Por exemplo: <br>
	 * <pre>
	 * (1)    |   (7)    |   (4) 
	 * --------------------------
	 * (2)    |   20     |   (5) 
	 * --------------------------
	 * (3)    |   30     |   (6) 
     *--------------------------
     *        |   (10)   |
     *        +----------+ 
     *</pre><br>
     *mostra as posi��es 8 (sequencia) e 9 (quadra) ocupadas.
	 */
	@Override
	public String toString() {
		String num;
		String s = "";
		for (int i = 0 ; i < 3; i++) {
			num = taken[i] ? String.format("%-4d", placar[i]) : "(" + (i+1) + ") ";
			s +=   num + "   |   ";
			num = taken[i+6] ? String.format("%-4d", placar[i+6]) : "(" + (i+7) + ") ";
			s +=   num + "   |   ";
			num = taken[i+3] ? String.format("%-4d", placar[i+3]) : "(" + (i+4) + ") ";
			s+= num + "\n--------------------------\n";
		}
		num = taken[9] ? String.format("%-4d", placar[9]) : "(" + 10 + ")";
		s += "       |   " + num + "   |";
		s += "\n       +----------+\n";
		return s;
	}
}