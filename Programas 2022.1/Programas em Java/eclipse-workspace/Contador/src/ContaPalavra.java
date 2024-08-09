import java.util.TreeMap;  
import java.util.Iterator;
import java.util.HashMap;
import java.io.File;
import java.util.Scanner;

public class ContaPalavra{
	
	private String[] palavras = new String[0];
	private int numeroPalavras = 0;
	private HashMap<String, Integer> mapa = new HashMap<String, Integer>();
	
	public ContaPalavra(String nomeArquivo) throws Exception{
		//Le o arquivo
		File myObj = new File(nomeArquivo);
		Scanner arquivo = new Scanner(myObj);
		while(arquivo.hasNextLine()){
			//Le uma linha
		    String linha = arquivo.nextLine();
		    
		    //Separa as palavras da linha
		    String[] palavrasLidas = linha.split(" |,|\\.|\\(|\\)|\\[|\\]|\\{|\\}|\\\"");
		    
		    //Adiciona as palavras ao vetor de strings
		    for(String palavra : palavrasLidas) {
		    	if(palavra != null && palavra != "") {
		    		String[] novasPalavras = new String[numeroPalavras+1];
		    		for(int i = 0; i < numeroPalavras; ++i) {
		    			novasPalavras[i] = palavras[i];
		    		}
		    		palavras = novasPalavras;
		    		palavras[numeroPalavras] = palavra.toLowerCase();
		    		++numeroPalavras;
		    	}
		    }
		}
		arquivo.close();
		
	}
	
	public void criaMapa() throws Exception{
		for(String palavra : palavras){
			//Conta o n�mero de vezes que a palavra j� apareceu
			int quantidade = 0;
			if(mapa.containsKey(palavra)){
				quantidade = mapa.get(palavra);
			}
			mapa.put(palavra, quantidade + 1);
		}
	}
	
	public void mostraMapa() throws Exception{
		//Forma de mapeamento que � ordenado
		TreeMap<String,Integer> ordenado = new  TreeMap<String,Integer> (mapa);
		
		//Imprime todos os elementos do mapa ordenado sequencialmente
		Iterator<String> iterador = ordenado.keySet().iterator();               
		while(iterador.hasNext()){    
			String palavra = iterador.next();  
			System.out.println("Palavra: "+palavra+"   Quantidade: " + ordenado.get(palavra));
		}
	}
}