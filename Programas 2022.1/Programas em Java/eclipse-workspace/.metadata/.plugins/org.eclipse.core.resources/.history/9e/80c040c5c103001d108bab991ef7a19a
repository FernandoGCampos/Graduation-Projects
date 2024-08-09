import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.plaf.basic.BasicScrollBarUI;

public class SalaGUI extends JFrame implements ActionListener, ItemListener{
	//Salva os assentos selecionados
	private JCheckBox[][] opcoes;
	private JLabel valor = new JLabel("R$0.00");
	
	//Lista de assentos desejados pelo usuário
	private int nComprados = 0;
	private int[] comprados;
	
	//Salva os valores da sala
	private Sala sala;
	
	//Inicializa o frame
	public SalaGUI(Sala _sala) {
		super("Sala do cinema");
		sala = _sala;
		comprados = new int[sala.largura * sala.profundidade];
		
		//Cria a interface
		JPanel jp = (JPanel) getContentPane();
		jp.setLayout(new BorderLayout());
		JPanel janela = new JPanel();
		janela.setBackground(new Color(43, 43, 43));
		
		//Instrui o usuário a como utilizar o programa
		JLabel instrucoes = new JLabel("Selecione os assentos que deseja comprar");
		instrucoes.setForeground(new Color(169, 183, 198));
		instrucoes.setFont(new Font("Arial", Font.BOLD, 16));
		jp.add(instrucoes, BorderLayout.NORTH);
		
		//Cria barras de rolagem, caso a sala seja maior do que cabe no frame
		JScrollPane rolar = new JScrollPane(janela);
		rolar.setPreferredSize(new Dimension(1538,798));
		rolar.getHorizontalScrollBar().setBackground(new Color(43, 43, 43));
		rolar.getVerticalScrollBar().setBackground(new Color(43, 43, 43));
		rolar.getVerticalScrollBar().setUI(new BasicScrollBarUI() {
		    @Override
		    protected void configureScrollBarColors() {
		    	this.thumbColor = new Color(166, 166, 166);
		    }
		});
		rolar.getVerticalScrollBar().setUI(new BasicScrollBarUI() {
		    @Override
		    protected void configureScrollBarColors() {
		        this.thumbColor = new Color(166, 166, 166);
		    }
		});
		rolar.setBorder(null);
		rolar.setBorder(null);
		jp.add(rolar, BorderLayout.CENTER);
		
		//===========================Adiciona os assentos================================
		//---------Inicializa o grid onde serão colocados os assentos---------
		
		JPanel assentos = new JPanel();
		assentos.setLayout(new GridLayout(sala.profundidade + 1, sala.largura + 1 + sala.nCorredores));
		assentos.setBackground(new Color(43, 43, 43));
		
		//---------Adiciona a linha de coordenadas superior---------
		assentos.add(new JLabel(" "));
		
		//Passa por todas sequências de assentos
		int contador = 0;
		for(int i = 0; i < sala.nCorredores; ++i) {
			//Passa por todos os assentos de uma sequência de assentos
			for(int j = 0; j < sala.corredores[i]; ++j) {
				//Adiciona as letras das coordenadas dos assentos
				JLabel letra = new JLabel(String.format("%5c", (char)(65 + contador)));
				letra.setForeground(new Color(169, 183, 198));
				assentos.add(letra);
				++contador;
			}
			
			//Adiciona um corredor entre todas série de assentos
			if(i < sala.nCorredores - 1) {
				JLabel espaco = new JLabel("");
				assentos.add(espaco);
			}
		}
		assentos.add(new JLabel(" "));
		
		//---------Adiciona as check boxes no formato de assentos---------
		//Inicializa a matriz de check boxes
		opcoes = new JCheckBox[sala.profundidade][sala.largura];
		
		//Percorre todas as linhas
		for(int i = sala.profundidade; i > 0; --i) {
			//Adiciona os números das coordenadas dos assentos
			JLabel numE = new JLabel(String.format("%9d", i));
			numE.setForeground(new Color(169, 183, 198));
			assentos.add(numE);
			
			//Passa por todas sequências de assentos
			contador = 0;
			for(int j = 0; j < sala.nCorredores; ++j) {
				
				//Passa por todos os assentos de uma sequência de assentos
				for(int k = 0; k < sala.corredores[j]; ++k) {
					
					//Inicializa a check box
					JCheckBox botao = new JCheckBox("");
					
					//Altera a aparência
					botao.setIcon(new ImageIcon("Desocupado.png"));
					botao.setSelectedIcon(new ImageIcon("Selecionado.png"));
					botao.setRolloverIcon(new ImageIcon("Cima.png"));
					botao.setRolloverSelectedIcon(new ImageIcon("CimaSelecionado.png"));
					botao.setPressedIcon(new ImageIcon("CimaSelecionado.png"));
					botao.setDisabledIcon(new ImageIcon("Ocupado.png"));
					botao.setBorder(BorderFactory.createEmptyBorder());
					
					//Determina se o assento já foi comprado anteriormente
					if(sala.ocupados[i-1][contador]) {
						botao.setEnabled(false);
					}
					else {
						botao.addItemListener(this);
					}
					
					//Adiciona os assento ao frame
					assentos.add(botao);
					opcoes[i-1][contador] = botao;
					
					//Incrementa o contador de assentos na linha
					++contador;
				}
				
				//Adiciona um corredor entre todas série de assentos
				if(j < sala.nCorredores - 1) {
					JLabel espaco = new JLabel("");
					assentos.add(espaco);
				}
			}
			
			//Adiciona os números das coordenadas dos assentos
			JLabel numD = new JLabel(String.format(" %d", i));
			numD.setForeground(new Color(169, 183, 198));
			assentos.add(numD);
		}
		
		//---------Adiciona os assentos no frame---------
		janela.add(assentos);
		
		
		//===========================Adiciona o preço dos ingressos===========================
		JPanel dados = new JPanel(new GridLayout(2,1));
		dados.add(valor);
		
		//===========================Adiciona os botões================================
		//Inicializa o painel onde os botões serão colocados
		JPanel botoes = new JPanel(new GridLayout(1,2));
		
		//---------Adiciona o botão de retorno---------
		//Inicializa o botão
		JButton botaoRet = new JButton("Retornar");
		botaoRet.addActionListener(this);
		botaoRet.setActionCommand("retorna");
				
		//Altera a aparência
		botaoRet.setFont(new Font("Arial", Font.BOLD, 18));
		botaoRet.setBorder(null); 
		botaoRet.setBackground(new Color(43, 43 ,43));
		botaoRet.setForeground(new Color(169, 183, 198));
		
		//Adiciona o botão
		botoes.add(botaoRet);
		
		//---------Adiciona o botão de compra---------
		//Inicializa o botão
		JButton botaoComprar = new JButton("Comprar");
		botaoComprar.addActionListener(this);
		botaoComprar.setActionCommand("confirma");
		
		//Altera a aparência
		botaoComprar.setFont(new Font("Arial", Font.BOLD, 18));
		botaoComprar.setBorder(null); 
		botaoComprar.setBackground(new Color(43, 43 ,43));
		botaoComprar.setForeground(new Color(169, 183, 198));
		
		//Adiciona o botão
		botoes.add(botaoComprar);
		
		//---------Adiciona os botões no frame---------
		dados.add(botoes);
		janela.add(dados);
	}
	
	//Executa as ações das caixas de checagem
	@Override
	public void itemStateChanged(ItemEvent e) {
		nComprados = 0;
		for(int i = 0; i < sala.profundidade; ++i) {
			
			//Percorre todos os assentos de uma fileira
			for(int j = 0; j < sala.largura; ++j) {
				
				//Caso o assento tenha sido selecionado
				if(opcoes[i][j].isSelected()) {
					
					//Adiciona o botão à lista de compras
					comprados[nComprados] = (i * sala.largura) + j;
					++nComprados;
				}
			}
		}
		valor.setText(String.format("R$%.2f", nComprados * sala.preco));
	}
	
	//Executa as ações dos botões
	@Override
 	public void actionPerformed(ActionEvent e) {
		//Caso seja pressionado o botão "Comprar"
		if("confirma".equals(e.getActionCommand())) {
			
			//Caso o número de assentos desejados seja maior que 0
			if(nComprados > 0) {
				//Inicializa a aba de pagamento
				CompraGUI pagamento = new CompraGUI(this, sala, nComprados, comprados);
				pagamento.getContentPane().setBackground(new Color(43, 43, 43));
				pagamento.setSize(750, 500);
				pagamento.setVisible(true);
				pagamento.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
				
				//Atualiza os dados da sala, caso seja neceessário
				if(pagamento.pago) {
					for(int i = 0; i < nComprados; ++i) {
						int linha = comprados[i]/sala.largura;
						int fileira = comprados[i]%sala.largura;
						
						//Desabilita a caixa de checagem
						opcoes[linha][fileira].removeItemListener(this);
						opcoes[linha][fileira].setSelected(false);
						opcoes[linha][fileira].setEnabled(false);
						sala.ocupados[linha][fileira] = true;
					}
				}
				
				//Atualiza o número de assentos a serem comprados
				if(pagamento.pago) {
					nComprados = 0;
					valor.setText("R$0.00");
					this.dispose();
				}
			}
		}
		
		//Caso seja pressionado o botão "Retornar"
		else if("retorna".equals(e.getActionCommand())) {
			//Fecha a janela
			this.dispose();
		}
	}

	//Função de teste
	public static void main(String[] args) {
		Sala sala = new Sala();
		sala.criaCorredores(3, new int[] {6, 6, 6});
		SalaGUI frame = new SalaGUI(sala);
		frame.setSize(1550,830);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setBackground(new Color(43, 43, 43));
		frame.setVisible(true);
	}

}