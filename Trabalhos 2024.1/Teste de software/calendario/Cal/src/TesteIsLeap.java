import static org.junit.jupiter.api.Assertions.*;

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

class TesteIsLeap {

	static Cal cal;
	@BeforeAll
	static void setUpBeforeClass() throws Exception {
		cal = new Cal();
	}

	@AfterAll
	static void tearDownAfterClass() throws Exception {
		cal = null;
	}

	@ParameterizedTest
	@ValueSource(ints = {1100, 2000, 2024})
	void testeTrue(int ano) {
		assertEquals(true, cal.isLeap(ano));
	}
	
	@ParameterizedTest
	@ValueSource(ints = {1101, 2100, 2023})
	void testeFalse(int ano) {
		assertEquals(false, cal.isLeap(ano));
	}
}
