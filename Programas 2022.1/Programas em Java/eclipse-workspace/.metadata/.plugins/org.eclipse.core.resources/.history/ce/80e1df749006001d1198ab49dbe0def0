import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.plaf.basic.BasicScrollBarUI;

public class CompraGUI extends JDialog implements ActionListener{
	//Constantes
	static Color backGroundColor = new Color(51, 51, 51);
	static Color centerColor = new Color(37, 37, 37);
	static Color textColor = new Color(56, 152, 255);
	static Color textColor2 = new Color(240, 240, 240);
	static Color buttonTextColor = new Color(80, 180, 255);
	
	//Salva o frame que abriu a caixa de diálogo
	private JFrame seletor;
	
	//Salva as informações da sessão
	private Sala sala;
	
	//Salva os assentos desejados
	private int nComprados;
	private int[] comprados;
	
	//Salva se a compra foi efetuada
	public boolean pago = false;
	
	
	public CompraGUI(JFrame _seletor, Sala _sala, int _nComprados, int[] _comprados) {
		super(_seletor, true);
		seletor = _seletor;
		sala = _sala;
		nComprados = _nComprados;
		comprados = _comprados;
		
		//Inicializa o painel
		JPanel jp = (JPanel) getContentPane();
		jp.setLayout(new BorderLayout());
		jp.setBackground(backGroundColor);
		
		//===========================Adiciona as formas de pagamento===========================
		
		//---------Adiciona o título---------
		JLabel instrucoes = new JLabel("CINEUSP");
		instrucoes.setForeground(new Color(30, 130, 255, 200));
		instrucoes.setFont(new Font("Arial", Font.BOLD, 40));
		instrucoes.setHorizontalAlignment(JTextField.CENTER);
		jp.add(instrucoes, BorderLayout.NORTH);
		
		//Possibilita a leitura dos dados caso muitos ingressos sejam selecionados
		JPanel info = new JPanel(new FlowLayout());
		info.setBackground(backGroundColor);
		info.setBorder(BorderFactory.createEmptyBorder(30, 30, 0, 0));
		
		JScrollPane rolar = new JScrollPane(info);
		rolar.setPreferredSize(new Dimension(155, 107));
		rolar.setBorder(null);

		
		//===========================Adiciona os dados dos ingressos===========================
		//---------Inicializa o grid---------
		JPanel dados = new JPanel(new GridLayout(5, 1));
		dados.setBorder(BorderFactory.createEmptyBorder(10, 20, 30, 0));
		dados.setPreferredSize(new Dimension(200, 200));
		dados.setBackground(new Color(255, 255, 255));
		
		int tamFonte = 13;
		JLabel filmeLabel = new JLabel(String.format("Filme: %s", sala.nomeDoFilme));
		filmeLabel.setFont(new Font("Arial", Font.BOLD, tamFonte));
		JLabel salaLabel = new JLabel(String.format("Sala: %d", sala.numeroDaSala));
		salaLabel.setFont(new Font("Arial", Font.BOLD, tamFonte));
		JLabel horarioLabel = new JLabel(String.format("Hor�rio: %s-%s", sala.inicio, sala.fim));
		horarioLabel.setFont(new Font("Arial", Font.BOLD, tamFonte));
		
		dados.add(filmeLabel);
		dados.add(salaLabel);
		dados.add(horarioLabel);
		
		//---------Adiciona os assentos---------
		String ingressos = "Assentos:";
		for(int i = 0; i < nComprados; ++i) {
			ingressos += String.format(" %d%c", (comprados[i]/sala.largura)+1, (char)(65 + (comprados[i]%sala.largura)));
		}
		JLabel ingressosLabel = new JLabel(ingressos);
		ingressosLabel.setFont(new Font("Arial", Font.BOLD, tamFonte));

		dados.add(ingressosLabel);
		
		//---------Adiciona o preco---------
		JLabel precoLabel = new JLabel(String.format("R$%.2f", nComprados * sala.preco));
		precoLabel.setFont(new Font("Arial", Font.BOLD, tamFonte));
		dados.add(precoLabel);
		
		//---------Adiciona os dados no painel---------
		
		info.add(dados);
		jp.add(rolar);
		
		//===========================Adiciona os botões================================
		//Inicializa o painel onde os botões serão colocados
		JPanel botoes = new JPanel(new FlowLayout());
		
		botoes.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
		botoes.setBackground(new Color(43, 43, 43));
		
		//---------Adiciona o botão de retorno---------
		//Inicializa o botão
		JButton botaoRet = new JButton("Retornar");
		botaoRet.addActionListener(this);
		botaoRet.setActionCommand("retorna");
				
		//Altera a aparência
		botaoRet.setFont(new Font("Arial", Font.BOLD, 18));
		botaoRet.setBackground(textColor);
		botaoRet.setForeground(textColor2);
		
		//Adiciona o botão
		dados.add(botaoRet);
	
		//Adiciona o botão
		botoes.add(botaoRet);
		
		//---------Adiciona o botão de compra---------
		//Inicializa o botão
		JButton botaoComprar = new JButton("Comprar");
		botaoComprar.addActionListener(this);
		botaoComprar.setActionCommand("confirma");
		
		//Altera a aparência
		botaoComprar.setFont(new Font("Arial", Font.BOLD, 18));
		botaoComprar.setBackground(textColor);
		botaoComprar.setForeground(textColor2);
	
		//Adiciona o botão
		botoes.add(botaoComprar);

		jp.add(botoes, BorderLayout.SOUTH);
	}
	
	//Executa as ações dos botões e caixas de checagem
	@Override
	public void actionPerformed(ActionEvent e) {
		//Caso seja pressionado o botão "Comprar"
		if("confirma".equals(e.getActionCommand())) {
			//Marca que os ingresso foram pagos
			pago = true;
			this.dispose();
		}
		
		//Caso seja pressionado o botão "Retornar"
		else if("retorna".equals(e.getActionCommand())) {
			//Fecha a janela
			this.dispose();
		}
	}
}
