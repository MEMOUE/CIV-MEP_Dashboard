package src;


import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

/**
 * Energie page component for the MMPE Dashboard
 */
public class EnergiePage extends JPanel {
	// Constantes de couleurs pour un design cohérent
	private static final Color BACKGROUND_COLOR = new Color(90, 150, 210);
	private static final Color PANEL_BACKGROUND = Color.WHITE;
	private static final Color SELECTED_BACKGROUND = new Color(200, 220, 240);
	private static final Color TEXT_COLOR = Color.BLACK;
	private static final Color BORDER_COLOR = new Color(180, 180, 180);
	private static final Color HEADER_COLOR = Color.ORANGE;

	// Constantes pour la taille des éléments
	private static final int BUTTON_HEIGHT = 25;
	private static final int INDICATEUR_HEIGHT = 25;
	private static final int INDICATEUR_WIDTH = 400; // Largeur réduite pour les indicateurs

	// Composants principaux
	private JPanel indicateursPanel;
	private JScrollPane indicateursScroll;
	private Map<String, java.util.List<String>> groupeIndicateurs;
	private JPanel evolCompPanel;
	private JPanel evolAnnPanel;
	private String currentGroupe = "Composantes du PIB Nominal";

	// Options d'affichage
	private JCheckBox optionBAU;
	private JCheckBox optionBAUPI;
	private JCheckBox optionBAUPIPlus;

	public EnergiePage() {
		initData();
		initComponents();
	}

	private void initData() {
		// Structure de données pour les groupes et leurs indicateurs (inchangée)
		groupeIndicateurs = new LinkedHashMap<>(); // LinkedHashMap pour conserver l'ordre d'insertion

		// Composantes du PIB Nominal (premier dans l'image)
//		java.util.List<String> pibNominalList = new ArrayList<>();
//		pibNominalList.add("Exportations Nominales Agrégées totexp");
//		pibNominalList.add("Importations Nominales Agrégées totimp");
//		groupeIndicateurs.put("Composantes du PIB Nominal", pibNominalList);

		// Composantes du PIB Réel (deuxième dans l'image)
//		java.util.List<String> pibReelList = new ArrayList<>();
//		pibReelList.add("Consommation Privée Réelle : xfd (h-hhld)");
//		pibReelList.add("Consommation Publique Réelle : xfd (g-govt)");
//		pibReelList.add("Exportations Réelles Agrégées : rtotexp");
//		pibReelList.add("Importations Réelles Agrégées rtotimp");
//		pibReelList.add("Investissement Privé Réel : xfd (i-invt)");
//		pibReelList.add("Investissement Public Réel : xfd (i-ginv)");
//		groupeIndicateurs.put("Composantes du PIB réel", pibReelList);

		// Contributions au PIB (troisième dans l'image)
//		java.util.List<String> contributionsList = new ArrayList<>();
//		contributionsList.add("Part Secteur Agricole sectshr(aagr,t)");
//		contributionsList.add("Part Secteur Énergie sectshr(aagr,t)");
//		contributionsList.add("Part Secteur Énergie (Hydrocarbures) sectshr(aagr,t)");
//		contributionsList.add("Part Secteur Manutention (Manufacturier) sectshr(aagr,t)");
//		contributionsList.add("Part Secteur Mines sectshr(aagr,t)");
//		contributionsList.add("Part Secteur Services sectshr(aagr,t)");
//		groupeIndicateurs.put("Contributions au PIB", contributionsList);


		// Vue d'Ensemble du Secteur des Mines
		java.util.List<String> vueEnsembleMinesList = new ArrayList<>();
		vueEnsembleMinesList.add("Exportations du Secteur Énergie pwe(i,t) * xe(i,t)");
//		vueEnsembleMinesList.add("Exportations du Secteur Énergie (Hydrocarbures) pwe(i,t) * xe(i,t)");
//		vueEnsembleMinesList.add("Exportations du Secteur Mines pwe(i,t) * xe(i,t)");
//		vueEnsembleMinesList.add("Importations du Secteur Énergie (Hydrocarbures) pwm(i,t) * (xm(i,t) + mdelst(i,t))");
		vueEnsembleMinesList.add("Importations pwm(i,t) * (xm(i,t) + mdelst(i,t))");
		groupeIndicateurs.put("Vue d'Ensemble", vueEnsembleMinesList);


		// Facteurs de production (quatrième dans l'image)
		java.util.List<String> facteursList = new ArrayList<>();
		facteursList.add("Masse Salariale d'Emploi Non-Qualifié Swage(a,l,t)");
//		facteursList.add("Secteur Mines Swage(a,l,t)");
//		facteursList.add("Secteur Énergie (Hydrocarbures) Swage(a,l,t)");
//		facteursList.add("Énergie Swage(a,l,t)");
		facteursList.add("Masse Salariale d'Emploi Qualifié Swage(a,l,t)");
//		facteursList.add("Secteur Mines Swage(a,l,t)");
//		facteursList.add("Secteur Énergie (Hydrocarbures) Swage(a,l,t)");
//		facteursList.add("Énergie Swage(a,l,t)");
		facteursList.add("Nombre d'Emplois Non-Qualifiés Ls (a,l,t)");
//		facteursList.add("Mines Ls (a,l,t)");
//		facteursList.add("Énergie (Hydrocarbures) Ls (a,l,t)");
//		facteursList.add("Énergie Ls (a,l,t)");
		facteursList.add("Nombre d'Emplois Qualifiés Ls (a,l,t)"); // TODO: fusion Nombre d'Emplois Qualifiés et Semi-Qualifiés
//		facteursList.add("Mines Ls (a,l,t)");
//		facteursList.add("Énergie (Hydrocarbures) Ls (a,l,t)");
//		facteursList.add("Énergie Ls (a,l,t)");
		//facteursList.add("Nombre d'Emplois Semi-Qualifiés lst(l,t)"); // TODO: fusion Nombre d'Emplois Qualifiés et Semi-Qualifiés
//		facteursList.add("Mines Ls (a,l,t)");
//		facteursList.add("Hydrocarbures Ls (a,l,t)");
//		facteursList.add("Énergie Ls (a,l,t)");
		facteursList.add("Nombre Total d'Emplois somme des ls");
//		facteursList.add("Valeur du Capital Secteur Mines sum(cap,pk_pt(a,v,t)*xf(a,cap,t))");
//		facteursList.add("Valeur du Capital Secteur Énergie (Hydrocarbures) sum(cap,pk_pt(a,v,t)*xf(a,cap,t))");
		facteursList.add("Valeur du Capital sum(cap,pk_pt(a,v,t)*xf(a,cap,t))");
		groupeIndicateurs.put("Facteurs de production", facteursList);

		// Vue d'Ensemble Macroéconomique
//		java.util.List<String> vueEnsembleMacroList = new ArrayList<>();
//		vueEnsembleMacroList.add("PIB Nominal gdpmp");
//		vueEnsembleMacroList.add("PIB Réel rgdpmp");
//		groupeIndicateurs.put("Vue d'Ensemble Macroéconomique", vueEnsembleMacroList);
	}

	private void initComponents() {
		setLayout(new BorderLayout(0, 0));
		setBackground(BACKGROUND_COLOR);
		setBorder(BorderFactory.createEmptyBorder(5, 5, 5, 5));

		// Titre principal
		JPanel headerPanel = new JPanel(new BorderLayout());
		headerPanel.setOpaque(false);

		JLabel titleLabel = new JLabel("Secteur de l'Énergie", JLabel.CENTER);
		titleLabel.setFont(new Font("Arial", Font.BOLD, 24));
		titleLabel.setForeground(HEADER_COLOR);
		titleLabel.setBackground(PANEL_BACKGROUND);
		titleLabel.setOpaque(true);
		titleLabel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
		headerPanel.add(titleLabel, BorderLayout.CENTER);

		add(headerPanel, BorderLayout.NORTH);

		// Panel principal
		JPanel mainPanel = new JPanel(new BorderLayout(10, 10));
		mainPanel.setOpaque(false);

		// Section des groupes et indicateurs (en haut)
		JPanel topSection = new JPanel(new BorderLayout(5, 0));
		topSection.setBackground(PANEL_BACKGROUND);
		topSection.setBorder(BorderFactory.createLineBorder(BORDER_COLOR));

		// Section gauche - Groupe
		JPanel groupeSection = new JPanel(new BorderLayout());
		groupeSection.setPreferredSize(new Dimension(200, 130));
		groupeSection.setBackground(PANEL_BACKGROUND);
		groupeSection.setBorder(BorderFactory.createMatteBorder(0, 0, 0, 1, BORDER_COLOR));

		JLabel groupeLabel = new JLabel("Groupe", JLabel.CENTER);
		groupeLabel.setFont(new Font("Arial", Font.BOLD, 12));
		groupeLabel.setBorder(BorderFactory.createMatteBorder(0, 0, 1, 0, BORDER_COLOR));
		groupeSection.add(groupeLabel, BorderLayout.NORTH);

		// Liste des groupes
		JPanel groupeListPanel = new JPanel();
		groupeListPanel.setLayout(new BoxLayout(groupeListPanel, BoxLayout.Y_AXIS));
		groupeListPanel.setBackground(PANEL_BACKGROUND);

		for (String groupe : groupeIndicateurs.keySet()) {
			JButton btn = createGroupeButton(groupe);
			groupeListPanel.add(btn);
		}

		JScrollPane groupeScroll = new JScrollPane(groupeListPanel);
		groupeScroll.setBorder(null);
		groupeScroll.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
		groupeSection.add(groupeScroll, BorderLayout.CENTER);

		// Panel central contenant les indicateurs et options d'affichage
		JPanel centralPanel = new JPanel(new BorderLayout());
		centralPanel.setBackground(PANEL_BACKGROUND);

		// Section centre-gauche - Indicateurs
		JPanel indicateursSection = new JPanel(new BorderLayout());
		indicateursSection.setBackground(PANEL_BACKGROUND);
		indicateursSection.setPreferredSize(new Dimension(400, 130));
		indicateursSection.setBorder(BorderFactory.createMatteBorder(0, 0, 0, 1, BORDER_COLOR));

		JLabel indicateursLabel = new JLabel("Indicateurs Macroéconomiques", JLabel.CENTER);
		indicateursLabel.setFont(new Font("Arial", Font.BOLD, 12));
		indicateursLabel.setBorder(BorderFactory.createMatteBorder(0, 0, 1, 0, BORDER_COLOR));
		indicateursSection.add(indicateursLabel, BorderLayout.NORTH);

		// Panel pour les indicateurs - utilisation d'un layout personnalisé
		indicateursPanel = new JPanel();
		indicateursPanel.setLayout(new ResultatsPage.FixedGridLayout(2, 5, 1)); // 2 colonnes, 5px gap vertical, 1px gap horizontal
		indicateursPanel.setBackground(PANEL_BACKGROUND);

		indicateursScroll = new JScrollPane(indicateursPanel);
		indicateursScroll.setBorder(null);
		indicateursScroll.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
		indicateursSection.add(indicateursScroll, BorderLayout.CENTER);

		// Section centre-droite - Options d'affichage
		JPanel optionsSection = new JPanel(new BorderLayout());
		optionsSection.setBackground(PANEL_BACKGROUND);

		JLabel optionsLabel = new JLabel("Affichage", JLabel.CENTER);
		optionsLabel.setFont(new Font("Arial", Font.BOLD, 12));
		optionsLabel.setBorder(BorderFactory.createMatteBorder(0, 0, 1, 0, BORDER_COLOR));
		optionsSection.add(optionsLabel, BorderLayout.NORTH);

		// Création des cases à cocher
		JPanel checkBoxPanel = new JPanel();
		checkBoxPanel.setLayout(new BoxLayout(checkBoxPanel, BoxLayout.Y_AXIS));
		checkBoxPanel.setBackground(PANEL_BACKGROUND);
		checkBoxPanel.setBorder(BorderFactory.createEmptyBorder(10, 20, 10, 20));

		optionBAU = new JCheckBox("BAU");
		optionBAU.setFont(new Font("Arial", Font.PLAIN, 11));
		optionBAU.setBackground(PANEL_BACKGROUND);
		optionBAU.setSelected(true);

		optionBAUPI = new JCheckBox("BAU PI");
		optionBAUPI.setFont(new Font("Arial", Font.PLAIN, 11));
		optionBAUPI.setBackground(PANEL_BACKGROUND);

		optionBAUPIPlus = new JCheckBox("BAU PI PLUS");
		optionBAUPIPlus.setFont(new Font("Arial", Font.PLAIN, 11));
		optionBAUPIPlus.setBackground(PANEL_BACKGROUND);

		// Ajouter des listeners aux cases à cocher
		ActionListener checkboxListener = e -> updateGraphiques(currentGroupe, getSelectedIndicateur());

		optionBAU.addActionListener(checkboxListener);
		optionBAUPI.addActionListener(checkboxListener);
		optionBAUPIPlus.addActionListener(checkboxListener);

		checkBoxPanel.add(optionBAU);
		checkBoxPanel.add(Box.createVerticalStrut(10));
		checkBoxPanel.add(optionBAUPI);
		checkBoxPanel.add(Box.createVerticalStrut(10));
		checkBoxPanel.add(optionBAUPIPlus);

		optionsSection.add(checkBoxPanel, BorderLayout.CENTER);

		// Ajouter les sections au panneau central
		centralPanel.add(indicateursSection, BorderLayout.CENTER);
		centralPanel.add(optionsSection, BorderLayout.EAST);

		// Ajouter les sections au panel supérieur
		topSection.add(groupeSection, BorderLayout.WEST);
		topSection.add(centralPanel, BorderLayout.CENTER);

		// Section des graphiques (en bas)
		JPanel graphsSection = new JPanel(new GridLayout(1, 2, 10, 0));
		graphsSection.setBackground(BACKGROUND_COLOR);

		evolCompPanel = createGraphPanel("Evolutions comparées");
		evolAnnPanel = createGraphPanel("Evolutions annuelles");

		graphsSection.add(evolCompPanel);
		graphsSection.add(evolAnnPanel);

		// Diviser l'espace avec un JSplitPane
		JSplitPane splitPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT, topSection, graphsSection);
		splitPane.setDividerLocation(130); // Hauteur fixe pour la section supérieure
		splitPane.setDividerSize(5);
		splitPane.setBorder(null);

		mainPanel.add(splitPane, BorderLayout.CENTER);
		add(mainPanel, BorderLayout.CENTER);

		// Initialiser les indicateurs avec le groupe par défaut
		updateIndicateurs(currentGroupe);
	}

	private String getSelectedIndicateur() {
		// Trouver l'indicateur actuellement sélectionné
		for (Component c : indicateursPanel.getComponents()) {
			if (c instanceof JButton && c.getBackground().equals(SELECTED_BACKGROUND)) {
				return ((JButton) c).getText();
			}
		}

		// Par défaut, retourner le premier indicateur du groupe actuel
		java.util.List<String> indicateurs = groupeIndicateurs.get(currentGroupe);
		return indicateurs != null && !indicateurs.isEmpty() ? indicateurs.get(0) : "";
	}

	private JButton createGroupeButton(String title) {
		JButton button = new JButton(title);
		button.setHorizontalAlignment(SwingConstants.LEFT);
		button.setFont(new Font("Arial", Font.PLAIN, 11));
		button.setForeground(TEXT_COLOR);
		button.setBorderPainted(false);
		button.setFocusPainted(false);
		button.setBackground(title.equals(currentGroupe) ? SELECTED_BACKGROUND : PANEL_BACKGROUND);
		button.setMaximumSize(new Dimension(Integer.MAX_VALUE, BUTTON_HEIGHT));
		button.setPreferredSize(new Dimension(200, BUTTON_HEIGHT));

		// Action pour sélectionner un groupe
		button.addActionListener(e -> {
			currentGroupe = title;

			// Mettre à jour l'apparence des boutons
			for (Component c : ((JButton) e.getSource()).getParent().getComponents()) {
				if (c instanceof JButton) {
					c.setBackground(c == button ? SELECTED_BACKGROUND : PANEL_BACKGROUND);
				}
			}

			// Mettre à jour les indicateurs
			updateIndicateurs(currentGroupe);
		});

		return button;
	}

	private void updateIndicateurs(String groupe) {
		indicateursPanel.removeAll();
		java.util.List<String> indicateurs = groupeIndicateurs.get(groupe);

		if (indicateurs != null) {
			// Ajouter les indicateurs avec taille fixe
			for (String indicateur : indicateurs) {
				JButton indButton = createIndicateurButton(indicateur);
				indicateursPanel.add(indButton);
			}
		}

		indicateursPanel.revalidate();
		indicateursPanel.repaint();

		// Remonter au début du scroll
		SwingUtilities.invokeLater(() -> {
			indicateursScroll.getVerticalScrollBar().setValue(0);
		});
	}

	private JButton createIndicateurButton(String indicateur) {
		JButton button = new JButton(indicateur);
		button.setHorizontalAlignment(SwingConstants.LEFT);
		button.setFont(new Font("Arial", Font.PLAIN, 11));
		button.setForeground(TEXT_COLOR);
		button.setBorder(BorderFactory.createLineBorder(BORDER_COLOR));
		button.setFocusPainted(false);

		// Définir une taille fixe pour tous les boutons d'indicateurs
		button.setPreferredSize(new Dimension(INDICATEUR_WIDTH, INDICATEUR_HEIGHT));
		button.setMinimumSize(new Dimension(INDICATEUR_WIDTH, INDICATEUR_HEIGHT));
		button.setMaximumSize(new Dimension(INDICATEUR_WIDTH, INDICATEUR_HEIGHT));

		// Présélectionner certains indicateurs pour correspondre à l'image
		boolean isSelected = false;
		if (currentGroupe.equals("Composantes du PIB Nominal") &&
				indicateur.equals("Importations Nominales Agrégées totimp")) {
			isSelected = true;
		} else if (currentGroupe.equals("Composantes du PIB réel") &&
				indicateur.startsWith("Importations Réelles Agrégées")) {
			isSelected = true;
		}

		button.setBackground(isSelected ? SELECTED_BACKGROUND : PANEL_BACKGROUND);

		// Action pour la sélection d'un indicateur
		button.addActionListener(e -> {
			// Réinitialiser tous les indicateurs
			for (Component c : indicateursPanel.getComponents()) {
				if (c instanceof JButton) {
					c.setBackground(PANEL_BACKGROUND);
				}
			}

			// Sélectionner cet indicateur
			button.setBackground(SELECTED_BACKGROUND);

			// Mettre à jour les graphiques
			updateGraphiques(currentGroupe, indicateur);
		});

		return button;
	}

	private JPanel createGraphPanel(String title) {
		JPanel panel = new JPanel(new BorderLayout());
		panel.setBackground(PANEL_BACKGROUND);
		panel.setBorder(BorderFactory.createLineBorder(BORDER_COLOR));

		JLabel titleLabel = new JLabel(title, JLabel.CENTER);
		titleLabel.setFont(new Font("Arial", Font.BOLD, 14));
		titleLabel.setForeground(HEADER_COLOR);
		titleLabel.setBorder(BorderFactory.createEmptyBorder(5, 0, 5, 0));
		panel.add(titleLabel, BorderLayout.NORTH);

		// Espace pour le graphique
		JPanel graphArea = new JPanel() {
			@Override
			protected void paintComponent(Graphics g) {
				super.paintComponent(g);
				if (title.equals("Evolutions comparées")) {
					drawEvolutionsComparees(g);
				} else {
					drawEvolutionsAnnuelles(g);
				}
			}
		};
		graphArea.setBackground(PANEL_BACKGROUND);
		panel.add(graphArea, BorderLayout.CENTER);

		return panel;
	}

	private void drawEvolutionsComparees(Graphics g) {
		// Dessiner le graphique des évolutions comparées en tenant compte des options sélectionnées
		Graphics2D g2d = (Graphics2D) g;
		g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

		int width = g.getClipBounds().width;
		int height = g.getClipBounds().height;

		// Axes
		g2d.setColor(Color.BLACK);
		g2d.drawLine(50, height - 50, width - 20, height - 50); // axe X
		g2d.drawLine(50, height - 50, 50, 20); // axe Y

		// Barres (simulation)
		g2d.setColor(new Color(180, 0, 0));
		for (int i = 0; i < 20; i++) {
			int barHeight = (int) (Math.pow(1.2, i) * 10);
			if (barHeight > height - 100) barHeight = height - 100;
			g2d.fillRect(60 + i * ((width - 80) / 20), height - 50 - barHeight, 10, barHeight);
		}

		// Étiquettes années
		g2d.setColor(Color.BLACK);
		g2d.setFont(new Font("Arial", Font.PLAIN, 8));
		for (int i = 0; i < 20; i += 2) {
			g2d.drawString("20" + (i+21), 60 + i * ((width - 80) / 20), height - 35);
		}

		// Légende
		g2d.setFont(new Font("Arial", Font.PLAIN, 10));
		g2d.setColor(Color.BLACK);
		g2d.drawString("Delta - min", 60, 15);
		g2d.setColor(new Color(180, 0, 0));
		g2d.fillRect(120, 10, 10, 10);

		// Afficher les options d'affichage sélectionnées
		g2d.setColor(Color.BLACK);
		g2d.setFont(new Font("Arial", Font.PLAIN, 9));

		StringBuilder options = new StringBuilder("Options: ");
		if (optionBAU.isSelected()) options.append("BAU ");
		if (optionBAUPI.isSelected()) options.append("BAU PI ");
		if (optionBAUPIPlus.isSelected()) options.append("BAU PI PLUS ");

		g2d.drawString(options.toString(), width - 180, 15);
	}

	private void drawEvolutionsAnnuelles(Graphics g) {
		// Dessiner le graphique des évolutions annuelles en tenant compte des options sélectionnées
		Graphics2D g2d = (Graphics2D) g;
		g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

		int width = g.getClipBounds().width;
		int height = g.getClipBounds().height;

		// Axes
		g2d.setColor(Color.BLACK);
		g2d.drawLine(50, height - 50, width - 20, height - 50); // axe X
		g2d.drawLine(50, height - 50, 50, 20); // axe Y

		// Préparer les tableaux pour les courbes
		int[] pointsX = new int[20];
		java.util.List<int[]> allPointsY = new ArrayList<>();
		List<Color> curveColors = new ArrayList<>();

		// Définir les courbes à afficher en fonction des options sélectionnées
		if (optionBAU.isSelected()) {
			int[] pointsY1 = new int[20];
			for (int i = 0; i < 20; i++) {
				pointsY1[i] = height - 50 - (int)(Math.log(i+1) * 50);
			}
			allPointsY.add(pointsY1);
			curveColors.add(new Color(0, 0, 180)); // BAU en bleu
		}

		if (optionBAUPI.isSelected()) {
			int[] pointsY2 = new int[20];
			for (int i = 0; i < 20; i++) {
				pointsY2[i] = height - 50 - (int)(Math.log(i+1) * 55);
			}
			allPointsY.add(pointsY2);
			curveColors.add(new Color(180, 0, 0)); // BAU PI en rouge
		}

		if (optionBAUPIPlus.isSelected()) {
			int[] pointsY3 = new int[20];
			for (int i = 0; i < 20; i++) {
				pointsY3[i] = height - 50 - (int)(Math.log(i+1) * 60);
			}
			allPointsY.add(pointsY3);
			curveColors.add(new Color(0, 150, 0)); // BAU PI PLUS en vert
		}

		// Calculer les positions X
		for (int i = 0; i < 20; i++) {
			pointsX[i] = 50 + i * ((width - 70) / 19);
		}

		// Dessiner les courbes
		for (int curveIndex = 0; curveIndex < allPointsY.size(); curveIndex++) {
			int[] pointsY = allPointsY.get(curveIndex);
			g2d.setColor(curveColors.get(curveIndex));
			g2d.setStroke(new BasicStroke(2.0f));

			// Tracer la ligne
			for (int i = 0; i < 19; i++) {
				g2d.drawLine(pointsX[i], pointsY[i], pointsX[i+1], pointsY[i+1]);
			}

			// Ajouter les points
			for (int i = 0; i < 20; i++) {
				g2d.fillOval(pointsX[i]-3, pointsY[i]-3, 6, 6);
			}
		}

		// Étiquettes années
		g2d.setColor(Color.BLACK);
		g2d.setFont(new Font("Arial", Font.PLAIN, 8));
		for (int i = 0; i < 20; i += 2) {
			g2d.drawString("20" + (i+21), pointsX[i], height - 35);
		}

		// Légende
		int legendX = 60;
		int legendY = 15;

		g2d.setFont(new Font("Arial", Font.PLAIN, 10));

		if (optionBAU.isSelected()) {
			g2d.setColor(new Color(0, 0, 180));
			g2d.drawString("BAU", legendX, legendY);
			g2d.fillOval(legendX + 30, legendY - 5, 6, 6);
			legendX += 50;
		}

		if (optionBAUPI.isSelected()) {
			g2d.setColor(new Color(180, 0, 0));
			g2d.drawString("BAU PI", legendX, legendY);
			g2d.fillOval(legendX + 40, legendY - 5, 6, 6);
			legendX += 60;
		}

		if (optionBAUPIPlus.isSelected()) {
			g2d.setColor(new Color(0, 150, 0));
			g2d.drawString("BAU PI PLUS", legendX, legendY);
			g2d.fillOval(legendX + 70, legendY - 5, 6, 6);
		}
	}

	private void updateGraphiques(String groupe, String indicateur) {
		// Mettre à jour les graphiques en fonction de l'indicateur sélectionné et des options d'affichage
		System.out.println("Mise à jour des graphiques pour: " + groupe + " - " + indicateur);
		System.out.println("Options: BAU=" + optionBAU.isSelected() +
				", BAU PI=" + optionBAUPI.isSelected() +
				", BAU PI PLUS=" + optionBAUPIPlus.isSelected());

		evolCompPanel.repaint();
		evolAnnPanel.repaint();
	}

	// Classe pour créer un layout avec des cellules de taille fixe
	static class FixedGridLayout implements LayoutManager {
		private int columns;
		private int vgap;
		private int hgap;

		public FixedGridLayout(int cols, int vgap, int hgap) {
			this.columns = cols;
			this.vgap = vgap;
			this.hgap = hgap;
		}

		@Override
		public void addLayoutComponent(String name, Component comp) {
			// Non utilisé
		}

		@Override
		public void removeLayoutComponent(Component comp) {
			// Non utilisé
		}

		@Override
		public Dimension preferredLayoutSize(Container parent) {
			synchronized (parent.getTreeLock()) {
				int componentCount = parent.getComponentCount();
				int rows = (componentCount + columns - 1) / columns;

				// Utiliser la taille fixée pour les cellules
				int width = columns * INDICATEUR_WIDTH + (columns - 1) * hgap;
				int height = rows * INDICATEUR_HEIGHT + (rows - 1) * vgap;

				Insets insets = parent.getInsets();
				return new Dimension(
						width + insets.left + insets.right,
						height + insets.top + insets.bottom
				);
			}
		}

		@Override
		public Dimension minimumLayoutSize(Container parent) {
			return preferredLayoutSize(parent);
		}

		@Override
		public void layoutContainer(Container parent) {
			synchronized (parent.getTreeLock()) {
				Insets insets = parent.getInsets();
				int componentCount = parent.getComponentCount();

				if (componentCount == 0) {
					return;
				}

				int x = insets.left;
				int y = insets.top;

				// Placer chaque composant dans sa cellule avec une taille fixe
				for (int i = 0; i < componentCount; i++) {
					int row = i / columns;
					int col = i % columns;

					int posX = x + col * (INDICATEUR_WIDTH + hgap);
					int posY = y + row * (INDICATEUR_HEIGHT + vgap);

					Component c = parent.getComponent(i);
					c.setBounds(posX, posY, INDICATEUR_WIDTH, INDICATEUR_HEIGHT);
				}
			}
		}
	}

}
