import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.LineBorder;
import javax.swing.plaf.basic.BasicScrollBarUI;

public class FilmeGUI extends JFrame implements ActionListener {
	//Constantes
	static Color backGroundColor = new Color(51, 51, 51);
	static Color centerColor = new Color(37, 37, 37);
	static Color textColor = new Color(56, 152, 255);
	static Color textColor2 = new Color(200, 200, 200);
	static Color buttonTextColor = new Color(80, 180, 255);
	
	int nFilmes;
	Filme[] filmes;
	JButton[][] botoes;
	
	public FilmeGUI(int _nFilmes, Filme[] _filmes) {
		
		super("Filme");
		nFilmes = _nFilmes;
		filmes = _filmes;
		botoes = new JButton[nFilmes][];
		
		//Cria a interface
		JPanel jp = (JPanel) getContentPane();
		jp.setLayout(new BorderLayout());
		
		//Coloca o titulo
		JLabel instrucoes = new JLabel("CINEUSP");
		instrucoes.setForeground(new Color(30, 130, 255, 200));
		instrucoes.setFont(new Font("Arial", Font.BOLD, 40));
		instrucoes.setHorizontalAlignment(JTextField.CENTER);
		jp.add(instrucoes, BorderLayout.NORTH);
		
		//Inicialiaza os paineis onde serão colocados os dados
		JPanel opcoes = new JPanel(new GridLayout(nFilmes, 1));
		JPanel info = new JPanel(new FlowLayout());
		info.setBackground(backGroundColor);
		info.add(opcoes);
		
		//Possibilita a seleção dos filmes caso eles não caibam na tela
		JScrollPane rolar = new JScrollPane(info);
		rolar.setPreferredSize(new Dimension(1538,799));
		rolar.getHorizontalScrollBar().setBackground(backGroundColor);
		rolar.getVerticalScrollBar().setBackground(backGroundColor);
		rolar.getVerticalScrollBar().setUnitIncrement(20);
		rolar.getVerticalScrollBar().setUI(new BasicScrollBarUI() {
		    @Override
		    protected void configureScrollBarColors() {
		    	this.thumbColor = new Color(166, 166, 166);
		    }
		});
		rolar.getHorizontalScrollBar().setUI(new BasicScrollBarUI() {
		    @Override
		    protected void configureScrollBarColors() {
		        this.thumbColor = new Color(166, 166, 166);
		    }
		});
		rolar.setBorder(null);
		jp.add(rolar, BorderLayout.CENTER);
		
		//Adiciona os filmes
		for(int i = 0; i < nFilmes; ++i) {
			//Inicializa o painel do filme alinhado à esquerda
			JPanel opcao = new JPanel();
			opcao.setBorder(BorderFactory.createEmptyBorder(15, 15, 15, 15));
			opcao.setLayout(new BoxLayout(opcao, BoxLayout.X_AXIS));
			opcao.setAlignmentX(LEFT_ALIGNMENT);
			opcao.setBackground(centerColor);
			opcao.setPreferredSize(new Dimension(600, 250));
			
			//Adiciona a imagem
			JLabel imagem = new JLabel();
			imagem.setBorder(BorderFactory.createEmptyBorder(0, 0, 0, 10));
			imagem.setIcon(new ImageIcon(filmes[i].imagem));
			opcao.add(imagem);

			//Adiciona os dados do filme
			JPanel dados = new JPanel(new GridLayout(3, 1));
			dados.setBackground(centerColor);
			
			//Adiciona o nome do filme
			JLabel nome = new JLabel(filmes[i].nomeDoFilme);
			nome.setForeground(textColor);
			nome.setFont(new Font("Arial", Font.BOLD, 20));
			dados.add(nome);
			
			//Adiciona as sessões do filme
			JPanel sessoes = new JPanel(new GridLayout(2, 1));
			sessoes.setBackground(centerColor);

			//Adiciona a sala
			JLabel sala = new JLabel(String.format("Sala %d", filmes[i].numeroDaSala));
			sala.setForeground(textColor2);
			sessoes.add(sala);
			
			//Inicializa o grid para posicionar os botões
			JPanel horarios = new JPanel();
			horarios.setLayout(new GridLayout(1, 3));
			horarios.setBackground(centerColor);
			
			//Adiciona os horários
			botoes[i] = new JButton[3];
			for(int j = 0; j < 3; ++j) {
				if(filmes[i].nSalas <= j) 
				{
					JLabel botaoNull = new JLabel();
					horarios.add(botaoNull);
					continue;
				}
				botoes[i][j] = new JButton(String.format("%s-%s", filmes[i].salas[j].inicio, filmes[i].salas[j].fim));
				horarios.add(botoes[i][j]);
				botoes[i][j].addActionListener(this);
				botoes[i][j].setActionCommand(String.format("%d-%d", i, j));
				botoes[i][j].setBackground(centerColor);
				botoes[i][j].setForeground(buttonTextColor);
				
			}
			sessoes.add(horarios);
			dados.add(sessoes);
			opcao.add(dados);
			opcoes.add(opcao);
		}
	}
	
	//Executa as ações dos botões
	public void actionPerformed(ActionEvent e) {
		for(int i = 0; i < nFilmes; ++i) {
			for(int j = 0; j < filmes[i].nSalas; ++j) {
				String mensagem = String.format("%d-%d", i, j);
				if(mensagem.equals(e.getActionCommand())) {
					SalaGUI frame = new SalaGUI(filmes[i].salas[j]);
					frame.setSize(1550,900);
					frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
					frame.getContentPane().setBackground(new Color(43, 43, 43));
					frame.setExtendedState(JFrame.MAXIMIZED_BOTH);
					frame.setVisible(true);
					break;
				}
			}
		}
	}
	
	public static void main(String[] args) {
		Filme filme1 = new Filme("PosterVingadores.png", "Vingadores");
		Filme filme2 = new Filme("PosterMatrix.png", "Matrix");
		Filme filme3 = new Filme("PosterMiranha.png", "Homem-Aranha");
		Filme filme4 = new Filme("PosterThor.png", "Thor");
		Filme filme5 = new Filme("PosterDoutor.png", "Doutor Estranho");
		Filme filme6 = new Filme("PosterCapitain.png", "Capitain Marvel");
		FilmeGUI frame = new FilmeGUI(6, new Filme[] {filme1, filme2, filme3, filme4, filme5, filme6});
		frame.setSize(1920,1080);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setBackground(new Color(43, 43, 43));
		frame.setExtendedState(JFrame.MAXIMIZED_BOTH);
		frame.setVisible(true);
	}

}
