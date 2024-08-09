package ssc103.bozo.dados;

import static org.junit.Assert.*;
import org.junit.Test;

public class PlacarTest {
	
	@Test (expected = IllegalArgumentException.class)
	public void testInvalidAdd0() {
		Placar placarTeste = new Placar();
		placarTeste.add(0, null);
	}

	@Test (expected = IllegalArgumentException.class)
	public void testInvalidAdd11() {
		Placar placarTeste = new Placar();
		placarTeste.add(11, null);
	}
	
	@Test (expected = IllegalArgumentException.class)
	public void testInvaidAddRepeat() {
		Placar placarTeste = new Placar();
		placarTeste.add(1, new int[] {1, 1, 2, 1, 4});
		placarTeste.add(1, new int[] {1, 2, 3, 4, 5});
	}
	
	@Test
	public void testGetScorePerfect() {
		Placar placarTeste = new Placar();
		placarTeste.add(1, new int[] {1, 1, 1, 1, 1});
		placarTeste.add(2, new int[] {2, 2, 2, 2, 2});
		placarTeste.add(3, new int[] {3, 3, 3, 3, 3});
		placarTeste.add(4, new int[] {4, 4, 4, 4, 4});
		placarTeste.add(5, new int[] {5, 5, 5, 5, 5});
		placarTeste.add(6, new int[] {6, 6, 6, 6, 6});
		placarTeste.add(7, new int[] {1, 1, 2, 1, 2});
		placarTeste.add(8, new int[] {1, 5, 4, 2, 3});
		placarTeste.add(9, new int[] {3, 6, 3, 3, 3});
		placarTeste.add(10, new int[] {6, 6, 6, 6, 6});
		
		assertEquals(210, placarTeste.getScore());
	}
	
	@Test
	public void testGetScoreHalf() {
		Placar placarTeste = new Placar();
		placarTeste.add(1, new int[] {2, 2, 2, 2, 2});
		placarTeste.add(2, new int[] {1, 1, 1, 1, 1});
		placarTeste.add(3, new int[] {4, 4, 4, 4, 4});
		placarTeste.add(4, new int[] {3, 3, 3, 3, 3});
		placarTeste.add(7, new int[] {1, 1, 2, 2, 2});
		placarTeste.add(9, new int[] {6, 6, 3, 6, 6});
		placarTeste.add(10, new int[] {1, 1, 1, 1, 1});
		
		assertEquals(85, placarTeste.getScore());
	}

	@Test
	public void testGetScoreVar1() {
		Placar placarTeste = new Placar();
		placarTeste.add(7, new int[] {1, 1, 1, 2, 3});
		placarTeste.add(8, new int[] {1, 2, 3, 4, 4});
		placarTeste.add(9, new int[] {1, 2, 3, 3, 3});
		placarTeste.add(10, new int[] {2, 2, 1, 1, 1});
		
		assertEquals(0, placarTeste.getScore());
	}
	
	@Test
	public void testGetScoreVar2() {
		Placar placarTeste = new Placar();
		placarTeste.add(7, new int[] {1, 2, 2, 2, 2});
		placarTeste.add(8, new int[] {1, 2, 3, 3, 3});
		placarTeste.add(9, new int[] {1, 2, 2, 3, 3});
		placarTeste.add(10, new int[] {3, 3, 3, 2, 2});
		
		assertEquals(0, placarTeste.getScore());
	}
	
	@Test
	public void testGetScoreVar3() {
		Placar placarTeste = new Placar();
		placarTeste.add(8, new int[] {1, 2, 2, 2, 2});
		placarTeste.add(9, new int[] {1, 2, 2, 2, 3});
		placarTeste.add(10, new int[] {4, 4, 4, 4, 3});
		
		assertEquals(0, placarTeste.getScore());
	}
	
	@Test
	public void testGetScoreVar4() {
		Placar placarTeste = new Placar();
		placarTeste.add(8, new int[] {1, 2, 3, 4, 6});
		placarTeste.add(9, new int[] {1, 1, 2, 2, 3});
		placarTeste.add(10, new int[] {2, 3, 2, 2, 2});
		
		assertEquals(0, placarTeste.getScore());
	}
	
	@Test
	public void testGetScoreZero() {
		Placar placarTeste = new Placar();
		placarTeste.add(1, new int[] {2, 2, 2, 2, 2});
		placarTeste.add(2, new int[] {1, 1, 1, 1, 1});
		placarTeste.add(3, new int[] {4, 4, 4, 4, 4});
		placarTeste.add(4, new int[] {3, 3, 3, 3, 3});
		placarTeste.add(5, new int[] {6, 6, 6, 6, 6});
		placarTeste.add(6, new int[] {5, 5, 5, 5, 5});
		placarTeste.add(7, new int[] {5, 1, 2, 1, 2});
		placarTeste.add(8, new int[] {1, 1, 1, 1, 1});
		placarTeste.add(9, new int[] {3, 6, 3, 6, 3});
		placarTeste.add(10, new int[] {5, 5, 5, 5, 6});
		
		assertEquals(0, placarTeste.getScore());
	}
	
	@Test
	public void testToStringEmpty() {
		Placar placarTeste = new Placar();
		String base = "(1)    |   (7)    |   (4) \n"
				    + "--------------------------\n"
				    + "(2)    |   (8)    |   (5) \n"
				    + "--------------------------\n"
				    + "(3)    |   (9)    |   (6) \n"
				    + "--------------------------\n"
				    + "       |   (10)   |\n"
				    + "       +----------+\n";
		
		assertEquals(base, placarTeste.toString());
	}
	
	@Test
	public void testToStringHalfEmpty() {
		Placar placarTeste = new Placar();
		String base = "5      |   (7)    |   (4) \n"
				    + "--------------------------\n"
				    + "(2)    |   0      |   (5) \n"
				    + "--------------------------\n"
				    + "6      |   (9)    |   0   \n"
				    + "--------------------------\n"
				    + "       |   40     |\n"
				    + "       +----------+\n";
		
		placarTeste.add(1, new int[] {1, 1, 1, 1, 1});
		placarTeste.add(3, new int[] {3, 2, 1, 3, 6});
		placarTeste.add(6, new int[] {5, 5, 5, 5, 5});
		placarTeste.add(8, new int[] {1, 6, 4, 2, 3});
		placarTeste.add(10, new int[] {6, 6, 6, 6, 6});
		
		assertEquals(base, placarTeste.toString());
	}

}