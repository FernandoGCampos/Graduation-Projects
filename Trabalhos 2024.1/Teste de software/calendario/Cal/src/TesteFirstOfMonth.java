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
 */

class TesteFirstOfMonth {
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
	void testeFoM_Jan1930() {
		assertEquals(3, cal.firstOfMonth(1, 1930));
	}
	
	@Test
	void testeFoM_Feb2023() {
		assertEquals(3, cal.firstOfMonth(2, 2023));
	}
	
	@Test
	void testeFoM_Mar2023() {
		assertEquals(3, cal.firstOfMonth(3, 2023));
	}
	
	@Test
	void testeFoM_Jan2024() {
		assertEquals(1, cal.firstOfMonth(1, 2024));
	}
	
	@Test
	void testeFoM_Feb2024() {
		assertEquals(4, cal.firstOfMonth(2, 2024));
	}
	
	@Test
	void testeFoM_Mar2024() {
		assertEquals(5, cal.firstOfMonth(3, 2024));
	}

}
