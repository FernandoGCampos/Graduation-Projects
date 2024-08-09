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

class TesteCal {

	static Cal cal;
	@BeforeAll
	static void setUpBeforeClass() throws Exception {
		cal = new Cal();
	}

	@AfterAll
	static void tearDownAfterClass() throws Exception {
		cal = null;
	}
	

	@Test
	void testeCal_ddsQa_n19() {
		assertEquals("       1  2 14 15 16\n17 18 19 20 21 22 23\n24 25 26 27 28 29 30", cal.cal(3, 19));
	}
	
	@Test
	void testeCal_ddsSe_n30() {
		assertEquals("    1  2  3  4  5  6\n 7  8  9 10 11 12 13\n14 15 16 17 18 19 20\n21 22 23 24 25 26 27\n28 29 30 ", cal.cal(1, 30));
	}

}
