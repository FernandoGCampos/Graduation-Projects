import static org.junit.jupiter.api.Assertions.*;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

/*
 * A data usada para a atualização do calendário é válida para a Inglaterra e as suas colônias.
 * Para o Brasil a data correta seria outubro de 1582
 * https://pt.wikipedia.org/wiki/1582#:~:text=4%20de%20outubro%20%E2%80%94%20%C3%9Altimo,entre%20todos%20os%20pa%C3%ADses.
 */


class TesteMain {
	
	@ParameterizedTest
	@ValueSource(strings = {"a", "0", "10000"})
	void testeMainMesAno_MesErro(String mes) {
		ByteArrayOutputStream outContent = new ByteArrayOutputStream();
	    System.setErr(new PrintStream(outContent));
	    
		String[] argv = new String[] {mes, "1"};
		String expectedError = String.format("Cal: %s: mes invalido.\n", argv[0]);
		Cal.main(argv);
		
		assertEquals(expectedError, outContent.toString());
	}
	
	@ParameterizedTest
	@ValueSource(strings = {"a", "0", "10000"})
	void testeMainMesAno_AnoErro(String ano) {
		ByteArrayOutputStream outContent = new ByteArrayOutputStream();
	    System.setErr(new PrintStream(outContent));
	    
		String[] argv = new String[] {"1", ano};
		String expectedError = String.format("Cal: %s: ano invalido.\n", argv[1]);
		Cal.main(argv);
		
		assertEquals(expectedError, outContent.toString());
	}
	
	@ParameterizedTest
	@ValueSource(strings = {"a", "0", "10000"})
	void testeMainAnoErro(String ano) {
		ByteArrayOutputStream outContent = new ByteArrayOutputStream();
	    System.setErr(new PrintStream(outContent));
	    
		String[] argv = new String[] {ano};
		String expectedError = String.format("Cal: %s: ano invalido.\n", argv[0]);
		Cal.main(argv);
		
		assertEquals(expectedError, outContent.toString());
	}
	
	@Test
	void testeMesAno() {
		ByteArrayOutputStream outContent = new ByteArrayOutputStream();
	    System.setOut(new PrintStream(outContent));
	    
		String[] argv = new String[] {"4", "2024"};
		Cal.main(argv);
	
		assertEquals("   Abril 2024\n"
				+ "Do Se Te Qa Qi Se Sa\n"
				+ "    1  2  3  4  5  6\n"
				+ " 7  8  9 10 11 12 13\n"
				+ "14 15 16 17 18 19 20\n"
				+ "21 22 23 24 25 26 27\n"
				+ "28 29 30 \r\n",
				outContent.toString());
	}
	
	@Test
	void testeAno() {
		ByteArrayOutputStream outContent = new ByteArrayOutputStream();
	    System.setOut(new PrintStream(outContent));
	    
		String[] argv = new String[] {"2024"};
		Cal.main(argv);
	
		assertEquals("   Janeiro 2024\n"
				+ "Do Se Te Qa Qi Se Sa\n"
				+ "    1  2  3  4  5  6\n"
				+ " 7  8  9 10 11 12 13\n"
				+ "14 15 16 17 18 19 20\n"
				+ "21 22 23 24 25 26 27\n"
				+ "28 29 30 31 \r\n"
				+ "\r\n"
				+ "   Fevereiro 2024\n"
				+ "Do Se Te Qa Qi Se Sa\n"
				+ "             1  2  3\n"
				+ " 4  5  6  7  8  9 10\n"
				+ "11 12 13 14 15 16 17\n"
				+ "18 19 20 21 22 23 24\n"
				+ "25 26 27 28 29 \r\n"
				+ "\r\n"
				+ "   Março 2024\n"
				+ "Do Se Te Qa Qi Se Sa\n"
				+ "                1  2\n"
				+ " 3  4  5  6  7  8  9\n"
				+ "10 11 12 13 14 15 16\n"
				+ "17 18 19 20 21 22 23\n"
				+ "24 25 26 27 28 29 30\n"
				+ "31 \r\n"
				+ "\r\n"
				+ "   Abril 2024\n"
				+ "Do Se Te Qa Qi Se Sa\n"
				+ "    1  2  3  4  5  6\n"
				+ " 7  8  9 10 11 12 13\n"
				+ "14 15 16 17 18 19 20\n"
				+ "21 22 23 24 25 26 27\n"
				+ "28 29 30 \r\n"
				+ "\r\n"
				+ "   Maio 2024\n"
				+ "Do Se Te Qa Qi Se Sa\n"
				+ "          1  2  3  4\n"
				+ " 5  6  7  8  9 10 11\n"
				+ "12 13 14 15 16 17 18\n"
				+ "19 20 21 22 23 24 25\n"
				+ "26 27 28 29 30 31 \r\n"
				+ "\r\n"
				+ "   Junho 2024\n"
				+ "Do Se Te Qa Qi Se Sa\n"
				+ "                   1\n"
				+ " 2  3  4  5  6  7  8\n"
				+ " 9 10 11 12 13 14 15\n"
				+ "16 17 18 19 20 21 22\n"
				+ "23 24 25 26 27 28 29\n"
				+ "30 \r\n"
				+ "\r\n"
				+ "   Julho 2024\n"
				+ "Do Se Te Qa Qi Se Sa\n"
				+ "    1  2  3  4  5  6\n"
				+ " 7  8  9 10 11 12 13\n"
				+ "14 15 16 17 18 19 20\n"
				+ "21 22 23 24 25 26 27\n"
				+ "28 29 30 31 \r\n"
				+ "\r\n"
				+ "   Agosto 2024\n"
				+ "Do Se Te Qa Qi Se Sa\n"
				+ "             1  2  3\n"
				+ " 4  5  6  7  8  9 10\n"
				+ "11 12 13 14 15 16 17\n"
				+ "18 19 20 21 22 23 24\n"
				+ "25 26 27 28 29 30 31\n"
				+ "\r\n"
				+ "\r\n"
				+ "   Setembro 2024\n"
				+ "Do Se Te Qa Qi Se Sa\n"
				+ " 1  2  3  4  5  6  7\n"
				+ " 8  9 10 11 12 13 14\n"
				+ "15 16 17 18 19 20 21\n"
				+ "22 23 24 25 26 27 28\n"
				+ "29 30 \r\n"
				+ "\r\n"
				+ "   Outubro 2024\n"
				+ "Do Se Te Qa Qi Se Sa\n"
				+ "       1  2  3  4  5\n"
				+ " 6  7  8  9 10 11 12\n"
				+ "13 14 15 16 17 18 19\n"
				+ "20 21 22 23 24 25 26\n"
				+ "27 28 29 30 31 \r\n"
				+ "\r\n"
				+ "   Novembro 2024\n"
				+ "Do Se Te Qa Qi Se Sa\n"
				+ "                1  2\n"
				+ " 3  4  5  6  7  8  9\n"
				+ "10 11 12 13 14 15 16\n"
				+ "17 18 19 20 21 22 23\n"
				+ "24 25 26 27 28 29 30\n"
				+ "\r\n"
				+ "\r\n"
				+ "   Dezembro 2024\n"
				+ "Do Se Te Qa Qi Se Sa\n"
				+ " 1  2  3  4  5  6  7\n"
				+ " 8  9 10 11 12 13 14\n"
				+ "15 16 17 18 19 20 21\n"
				+ "22 23 24 25 26 27 28\n"
				+ "29 30 31 \r\n"
				+ "\r\n", 
				outContent.toString());
	}
	
	@Test
    void emptyMainTest() {
		ByteArrayOutputStream outContent = new ByteArrayOutputStream();
	    System.setOut(new PrintStream(outContent));
	    
		String[] argv = new String[] {};
		Cal.main(argv);
		
        assertEquals("   Maio 2024\n"
			+ "Do Se Te Qa Qi Se Sa\n"
			+ "          1  2  3  4\n"
			+ " 5  6  7  8  9 10 11\n"
			+ "12 13 14 15 16 17 18\n"
			+ "19 20 21 22 23 24 25\n"
			+ "26 27 28 29 30 31 \r\n",
            outContent.toString()
        );
    }
}
