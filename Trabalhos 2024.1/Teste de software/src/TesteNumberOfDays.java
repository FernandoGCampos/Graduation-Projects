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

class TesteNumberOfDays {
	
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
	void testeNoD_Jan1752() {
		assertEquals(31, cal.numberOfDays(5, 1752));
	}
	
	@Test
	void testeNoD_Set1752() {
		assertEquals(19, cal.numberOfDays(9, 1752));
	}
	
	@Test
	void testeNoD_Feb2023() {
		assertEquals(28, cal.numberOfDays(2, 2023));
	}

	@Test
	void testeNoD_Jan2024() {
		assertEquals(31, cal.numberOfDays(1, 2024));
	}
	
	@Test
	void testeNoD_Feb2024() {
		assertEquals(29, cal.numberOfDays(2, 2024));
	}
	
	@Test
	void testeNoD_Mar2024() {
		assertEquals(31, cal.numberOfDays(3, 2024));
	}
	
	@Test
	void testeNoD_Abr2024() {
		assertEquals(30, cal.numberOfDays(4, 2024));
	}

}
