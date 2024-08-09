import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

/*
 * A data usada para a atualização do calendário é válida para a Inglaterra e as suas colônias.
 * Para o Brasil a data correta seria outubro de 1582
 * https://pt.wikipedia.org/wiki/1582#:~:text=4%20de%20outubro%20%E2%80%94%20%C3%9Altimo,entre%20todos%20os%20pa%C3%ADses.
 * */

class TesteJan1 {
	static Cal cal;
	@BeforeAll
	static void setUpBeforeClass() throws Exception {
		cal = new Cal();
	}

	@AfterAll
	static void tearDownAfterClass() throws Exception {
		cal = null;
	}

	//Não sei de anos antes de 1930
	
	@Test
	void testeJan1_1930() {
		assertEquals(3, cal.jan1(1930));
	}
	
	@Test
	void testeJan1_2023() {
		assertEquals(0, cal.jan1(2023));
	}
	
	@Test
	void testeJan1_2024() {
		assertEquals(1, cal.jan1(2024));
	}

}
