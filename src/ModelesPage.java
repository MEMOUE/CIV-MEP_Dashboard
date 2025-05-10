package src;

import javax.swing.*;
import javax.swing.border.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
import java.util.*;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class ModelesPage extends JPanel {
	private static final Color PRIMARY_COLOR = new Color(31, 97, 141);        // Bleu professionnel
	private static final Color SECONDARY_COLOR = new Color(41, 128, 185);     // Bleu clair accent
	private static final Color ACCENT_COLOR = new Color(22, 160, 133);        // Vert pour les succès
	private static final Color WARNING_COLOR = new Color(243, 156, 18);       // Orange pour avertissements
	private static final Color ERROR_COLOR = new Color(231, 76, 60);          // Rouge pour erreurs
	private static final Color BACKGROUND_COLOR = new Color(245, 245, 245);   // Gris très clair
	private static final Color CARD_COLOR = new Color(255, 255, 255);         // Blanc pour les cartes
	private static final Color TEXT_COLOR = new Color(52, 73, 94);            // Gris foncé pour le texte
	private static final Color DISABLED_COLOR = new Color(236, 240, 241);     // Gris clair pour désactivés

	// Police personnalisée
	private Font titleFont = new Font("Segoe UI", Font.BOLD, 20);
	private Font headerFont = new Font("Segoe UI", Font.BOLD, 16);
	private Font labelFont = new Font("Segoe UI", Font.PLAIN, 14);
	private Font buttonFont = new Font("Segoe UI", Font.BOLD, 14);
	private Font dialogFont = new Font("Segoe UI", Font.PLAIN, 14);

	// Constantes d'espacement
	private static final int PADDING = 15;
	private static final int MARGIN = 20;

	// Chemin vers l'exécutable GAMS
	private String gamsExecutablePath = "C:\\GAMS\\42\\gams.exe";

	// Chemin du projet MEGC
	private static final String PROJECT_PATH = "C:\\Users\\DELL\\projets\\Projet_MEGC";
	private static final String OPT_INC_PATH = PROJECT_PATH + "\\CIV_MPE_Structure\\inc\\opt.inc";

	// Années pour la simulation
	private static final int MIN_YEAR = 2020;
	private static final int MAX_YEAR = 2040;
	private static final int FIXED_START_YEAR = 2021;

	// Composants pour sélection des années
	private JSpinner startYearSpinner;
	private JSpinner endYearSpinner;
	private JLabel errorMessageLabel;

	// Composants pour sélection du fichier GAMS
	private JComboBox<String> gamsFileCombo;
	private JButton browseButton;
	private String selectedGamsFilePath;

	// Boutons et zones de sortie
	private JButton compileButton;
	private JButton startButton;

	// Pour les opérations en arrière-plan
	private ExecutorService executorService;
	private Process currentProcess;
	private volatile boolean processRunning = false;

	// Barre de progression
	private JProgressBar progressBar;
	private JLabel statusLabel;

	// Boîte de dialogue pour les messages d'exécution
	private JDialog executionDialog;
	private JTextArea dialogOutputArea;
	private JButton closeDialogButton;
	private JButton viewOutputButton;
	private JProgressBar dialogProgressBar;
	private JPanel dialogStatusPanel;
	private JLabel dialogStatusLabel;

	// Images
	private Image backgroundImage;
	private Image logoImage;

	// Buffer pour stocker les messages de sortie
	private StringBuilder outputBuffer = new StringBuilder();

	public ModelesPage() {
		// Initialisation du panneau principal
		setLayout(new BorderLayout());

		// Créer un panneau d'arrière-plan avec l'image
		JPanel backgroundPanel = new JPanel() {
			@Override
			protected void paintComponent(Graphics g) {
				super.paintComponent(g);
				if (backgroundImage != null) {
					// Dessiner l'image de fond sur tout le panneau
					g.drawImage(backgroundImage, 0, 0, getWidth(), getHeight(), this);
				} else {
					// Couleur de fond par défaut si l'image n'est pas disponible
					g.setColor(BACKGROUND_COLOR);
					g.fillRect(0, 0, getWidth(), getHeight());
				}
			}
		};
		backgroundPanel.setLayout(new BorderLayout());

		// Définir le panneau d'arrière-plan comme contenu principal
		setLayout(new BorderLayout());
		add(backgroundPanel, BorderLayout.CENTER);

		executorService = Executors.newSingleThreadExecutor();

		initComponents();
		layoutComponents(backgroundPanel);
		createExecutionDialog();
		addEventListeners();

		// Vérifier l'installation de GAMS de manière asynchrone
		SwingUtilities.invokeLater(this::checkGamsInstallation);
	}

	private void initComponents() {
		// Spinners pour les années
		SpinnerNumberModel startYearModel = new SpinnerNumberModel(FIXED_START_YEAR, MIN_YEAR, MAX_YEAR, 1);
		startYearSpinner = new JSpinner(startYearModel);
		startYearSpinner.setEnabled(false);
		JSpinner.DefaultEditor startEditor = (JSpinner.DefaultEditor) startYearSpinner.getEditor();
		startEditor.getTextField().setDisabledTextColor(TEXT_COLOR.darker());
		startEditor.getTextField().setBackground(DISABLED_COLOR);
		startEditor.getTextField().setFont(labelFont);
		startEditor.getTextField().setBorder(BorderFactory.createCompoundBorder(
				BorderFactory.createLineBorder(DISABLED_COLOR.darker()),
				BorderFactory.createEmptyBorder(5, 5, 5, 5)
		));

		SpinnerNumberModel endYearModel = new SpinnerNumberModel(2030, FIXED_START_YEAR, MAX_YEAR, 1);
		endYearSpinner = new JSpinner(endYearModel);
		JSpinner.DefaultEditor endEditor = (JSpinner.DefaultEditor) endYearSpinner.getEditor();
		endEditor.getTextField().setFont(labelFont);
		endEditor.getTextField().setBorder(BorderFactory.createCompoundBorder(
				BorderFactory.createLineBorder(SECONDARY_COLOR),
				BorderFactory.createEmptyBorder(5, 5, 5, 5)
		));

		// Message d'erreur
		errorMessageLabel = new JLabel("");
		errorMessageLabel.setForeground(ERROR_COLOR);
		errorMessageLabel.setFont(new Font("Segoe UI", Font.ITALIC, 12));
		errorMessageLabel.setVisible(false);

		// Liste des fichiers GAMS
		File projectDir = new File(PROJECT_PATH + "\\CIV_MPE_Structure");
		String[] gamsFileNames = listGamsFiles(projectDir);

		gamsFileCombo = new JComboBox<>(gamsFileNames);
		gamsFileCombo.setFont(labelFont);
		gamsFileCombo.setBackground(CARD_COLOR);
		gamsFileCombo.setBorder(BorderFactory.createCompoundBorder(
				BorderFactory.createLineBorder(SECONDARY_COLOR),
				BorderFactory.createEmptyBorder(5, 5, 5, 5)
		));

		browseButton = createStyledButton("Parcourir", SECONDARY_COLOR);
		browseButton.setIcon(UIManager.getIcon("FileView.directoryIcon"));

		if (gamsFileNames.length > 0) {
			selectedGamsFilePath = projectDir.getAbsolutePath() + "\\" + gamsFileNames[0];
		} else {
			selectedGamsFilePath = "";
		}

		// Boutons
		compileButton = createStyledButton("Compiler GAMS", PRIMARY_COLOR);
		compileButton.setIcon(UIManager.getIcon("FileView.fileIcon"));

		startButton = createStyledButton("Démarrer Simulation", ACCENT_COLOR);
		startButton.setIcon(UIManager.getIcon("Tree.expandedIcon"));

		// Barre de progression
		progressBar = new JProgressBar();
		progressBar.setIndeterminate(true);
		progressBar.setVisible(false);
		progressBar.setForeground(ACCENT_COLOR);
		progressBar.setBackground(CARD_COLOR);
		progressBar.setBorderPainted(false);

		// Statut
		statusLabel = new JLabel("Prêt");
		statusLabel.setFont(new Font("Segoe UI", Font.ITALIC, 12));
		statusLabel.setForeground(TEXT_COLOR);
	}

	private void createExecutionDialog() {
		// Créer la boîte de dialogue
		Frame parent = (Frame) SwingUtilities.getWindowAncestor(this);
		if (parent == null) {
			// Si parent est null (ce qui peut arriver lors de l'initialisation), utilisez un nouveau JFrame vide
			parent = new JFrame();
		}

		executionDialog = new JDialog(parent, "Exécution GAMS", true);
		executionDialog.setLayout(new BorderLayout());
		executionDialog.setSize(700, 500);
		executionDialog.setLocationRelativeTo(this);
		executionDialog.setDefaultCloseOperation(JDialog.DO_NOTHING_ON_CLOSE);  // Gérer la fermeture manuellement

		// En-tête
		JPanel dialogHeaderPanel = new JPanel(new BorderLayout());
		dialogHeaderPanel.setBackground(PRIMARY_COLOR);
		dialogHeaderPanel.setBorder(BorderFactory.createEmptyBorder(10, 15, 10, 15));

		JLabel dialogTitle = new JLabel("Journal d'Exécution GAMS");
		dialogTitle.setFont(headerFont);
		dialogTitle.setForeground(Color.WHITE);
		dialogTitle.setIcon(UIManager.getIcon("Tree.openIcon"));
		dialogHeaderPanel.add(dialogTitle, BorderLayout.WEST);

		// Zone de texte pour les sorties
		dialogOutputArea = new JTextArea();
		dialogOutputArea.setEditable(false);
		dialogOutputArea.setFont(new Font("Consolas", Font.PLAIN, 13));
		dialogOutputArea.setBackground(new Color(40, 44, 52));
		dialogOutputArea.setForeground(new Color(171, 178, 191));
		dialogOutputArea.setMargin(new Insets(PADDING, PADDING, PADDING, PADDING));

		JScrollPane dialogScrollPane = new JScrollPane(dialogOutputArea);
		dialogScrollPane.setBorder(null);

		// Panneau de statut
		dialogStatusPanel = new JPanel(new BorderLayout(10, 0));
		dialogStatusPanel.setBackground(CARD_COLOR);
		dialogStatusPanel.setBorder(BorderFactory.createEmptyBorder(8, 15, 8, 15));

		dialogStatusLabel = new JLabel("Exécution en cours...");
		dialogStatusLabel.setFont(new Font("Segoe UI", Font.ITALIC, 12));
		dialogStatusLabel.setForeground(SECONDARY_COLOR);

		dialogProgressBar = new JProgressBar();
		dialogProgressBar.setIndeterminate(true);
		dialogProgressBar.setForeground(ACCENT_COLOR);
		dialogProgressBar.setBackground(CARD_COLOR);
		dialogProgressBar.setBorderPainted(false);

		dialogStatusPanel.add(dialogStatusLabel, BorderLayout.WEST);
		dialogStatusPanel.add(dialogProgressBar, BorderLayout.CENTER);

		// Panneau de boutons
		JPanel dialogButtonPanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
		dialogButtonPanel.setBackground(CARD_COLOR);
		dialogButtonPanel.setBorder(BorderFactory.createMatteBorder(1, 0, 0, 0, new Color(230, 230, 230)));

		viewOutputButton = createStyledButton("Voir Détails", SECONDARY_COLOR);
		closeDialogButton = createStyledButton("Fermer", PRIMARY_COLOR);

		dialogButtonPanel.add(viewOutputButton);
		dialogButtonPanel.add(closeDialogButton);

		// Assembler la boîte de dialogue
		executionDialog.add(dialogHeaderPanel, BorderLayout.NORTH);
		executionDialog.add(dialogScrollPane, BorderLayout.CENTER);
		executionDialog.add(dialogStatusPanel, BorderLayout.SOUTH);
		executionDialog.add(dialogButtonPanel, BorderLayout.SOUTH);

		// Gérer les événements de la boîte de dialogue
		closeDialogButton.addActionListener(e -> {
			if (processRunning) {
				int response = JOptionPane.showConfirmDialog(
						executionDialog,
						"L'exécution est toujours en cours. Voulez-vous l'arrêter et fermer?",
						"Confirmation",
						JOptionPane.YES_NO_OPTION,
						JOptionPane.WARNING_MESSAGE
				);

				if (response == JOptionPane.YES_OPTION) {
					// Arrêter le processus
					if (currentProcess != null) {
						cleanupProcess(currentProcess);
						currentProcess = null;
					}

					// Terminer l'exécution
					setProcessing(false, "Exécution interrompue");
					executionDialog.setVisible(false);
				}
			} else {
				executionDialog.setVisible(false);
			}
		});

		// Gestion de la fenêtre lors de la tentative de fermeture
		executionDialog.addWindowListener(new java.awt.event.WindowAdapter() {
			@Override
			public void windowClosing(java.awt.event.WindowEvent windowEvent) {
				closeDialogButton.doClick();  // Utiliser la même logique que le bouton de fermeture
			}
		});

		// Le bouton "Voir Détails" sera implémenté plus tard pour afficher des détails supplémentaires
		viewOutputButton.addActionListener(e -> {
			// Afficher une boîte de dialogue avec le journal complet
			JTextArea fullLogArea = new JTextArea(outputBuffer.toString());
			fullLogArea.setEditable(false);
			fullLogArea.setFont(new Font("Consolas", Font.PLAIN, 12));

			JScrollPane logScrollPane = new JScrollPane(fullLogArea);
			logScrollPane.setPreferredSize(new Dimension(800, 600));

			JDialog logDialog = new JDialog(executionDialog, "Journal d'exécution complet", true);
			logDialog.setLayout(new BorderLayout());
			logDialog.add(logScrollPane, BorderLayout.CENTER);

			JButton closeLogButton = createStyledButton("Fermer", PRIMARY_COLOR);
			closeLogButton.addActionListener(event -> logDialog.dispose());

			JPanel logButtonPanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
			logButtonPanel.add(closeLogButton);
			logDialog.add(logButtonPanel, BorderLayout.SOUTH);

			logDialog.pack();
			logDialog.setLocationRelativeTo(executionDialog);
			logDialog.setVisible(true);
		});
	}

	private JButton createStyledButton(String text, Color color) {
		JButton button = new JButton(text);
		button.setFont(buttonFont);
		button.setForeground(Color.WHITE);
		button.setBackground(color);
		button.setFocusPainted(false);
		button.setBorderPainted(false);
		button.setOpaque(true);
		button.setBorder(BorderFactory.createEmptyBorder(8, 15, 8, 15));

		// Ajouter des effets de survol
		button.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseEntered(MouseEvent e) {
				button.setBackground(color.brighter());
			}

			@Override
			public void mouseExited(MouseEvent e) {
				button.setBackground(color);
			}

			@Override
			public void mousePressed(MouseEvent e) {
				button.setBackground(color.darker());
			}

			@Override
			public void mouseReleased(MouseEvent e) {
				button.setBackground(color);
			}
		});

		return button;
	}

	private String[] listGamsFiles(File directory) {
		if (!directory.exists() || !directory.isDirectory()) {
			return new String[0];
		}

		File[] gamsFiles = directory.listFiles((dir, name) -> name.toLowerCase().endsWith(".gms"));
		String[] fileNames = new String[gamsFiles != null ? gamsFiles.length : 0];

		if (gamsFiles != null) {
			for (int i = 0; i < gamsFiles.length; i++) {
				fileNames[i] = gamsFiles[i].getName();
			}
		}

		return fileNames;
	}

	private void layoutComponents(JPanel backgroundPanel) {
		// Créer le panneau d'en-tête (ne pas utiliser d'image de fond car elle est déjà dans le conteneur principal)
		JPanel headerPanel = new JPanel();
		headerPanel.setLayout(new BorderLayout());
		headerPanel.setOpaque(false); // Rendre le panneau transparent pour voir l'image de fond

		// Panneau pour le logo au lieu du JLabel avec texte
		JPanel logoPanel = new JPanel(new BorderLayout()) {
			@Override
			protected void paintComponent(Graphics g) {
				super.paintComponent(g);
				// Dessiner le logo s'il est disponible
				if (logoImage != null) {
					// Calculer la taille du logo (hauteur proportionnelle à la hauteur du panneau)
					int logoHeight = getHeight() - 10; // Marge de 5px en haut et en bas
					int logoWidth = logoHeight * logoImage.getWidth(this) / logoImage.getHeight(this);

					// Centrer le logo verticalement
					int y = (getHeight() - logoHeight) / 2;
					// Positionner le logo à gauche avec une marge
					int x = 10;

					g.drawImage(logoImage, x, y, logoWidth, logoHeight, this);
				}
			}

			@Override
			public Dimension getPreferredSize() {
				// Définir une largeur préférée pour le panneau de logo
				return new Dimension(150, super.getPreferredSize().height);
			}
		};
		logoPanel.setOpaque(false);
		logoPanel.setBorder(BorderFactory.createEmptyBorder(5, MARGIN, 5, 0));


		JPanel mainCardPanel = new JPanel(new BorderLayout()) {
			@Override
			protected void paintComponent(Graphics g) {
				super.paintComponent(g);
				// Créer un fond semi-transparent
				Graphics2D g2d = (Graphics2D) g;
				g2d.setColor(new Color(255, 255, 255, 220)); // Blanc avec 85% d'opacité
				g2d.fillRect(0, 0, getWidth(), getHeight());
			}
		};
		mainCardPanel.setOpaque(false); // Rendre le panneau transparent pour voir l'image de fond
		mainCardPanel.setBorder(BorderFactory.createCompoundBorder(
				BorderFactory.createEmptyBorder(MARGIN, MARGIN, MARGIN, MARGIN),
				getShadowBorder()
		));

		JPanel mainPanel = new JPanel();
		mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.Y_AXIS));
		mainPanel.setBackground(new Color(CARD_COLOR.getRed(), CARD_COLOR.getGreen(), CARD_COLOR.getBlue(), 240)); // Légère transparence
		mainPanel.setOpaque(true); // Nécessaire pour voir la couleur semi-transparente
		mainPanel.setBorder(BorderFactory.createEmptyBorder(PADDING, PADDING, PADDING, PADDING));

		// Panneau de configuration des années avec légère transparence
		JPanel yearPanel = new JPanel();
		yearPanel.setLayout(new GridBagLayout());
		yearPanel.setBackground(new Color(CARD_COLOR.getRed(), CARD_COLOR.getGreen(), CARD_COLOR.getBlue(), 240)); // Légère transparence
		yearPanel.setOpaque(true);
		yearPanel.setBorder(BorderFactory.createCompoundBorder(
				BorderFactory.createMatteBorder(0, 0, 1, 0, new Color(230, 230, 230, 200)),
				BorderFactory.createEmptyBorder(PADDING, PADDING, PADDING, PADDING)
		));

		GridBagConstraints gbc = new GridBagConstraints();
		gbc.fill = GridBagConstraints.HORIZONTAL;
		gbc.insets = new Insets(5, 5, 5, 5);
		gbc.weightx = 1.0; // Les composants s'étendent horizontalement

		// Titre section années
		JLabel yearSectionTitle = new JLabel("Période de Simulation");
		yearSectionTitle.setFont(headerFont);
		yearSectionTitle.setForeground(PRIMARY_COLOR);
		yearSectionTitle.setIcon(UIManager.getIcon("OptionPane.informationIcon"));
		gbc.gridx = 0;
		gbc.gridy = 0;
		gbc.gridwidth = 2;
		gbc.anchor = GridBagConstraints.WEST;
		yearPanel.add(yearSectionTitle, gbc);

		// Année de début
		JLabel startYearLabel = new JLabel("Année de début (fixée):");
		startYearLabel.setFont(labelFont);
		startYearLabel.setForeground(TEXT_COLOR);
		gbc.gridx = 0;
		gbc.gridy = 1;
		gbc.gridwidth = 1;
		gbc.anchor = GridBagConstraints.EAST;
		gbc.insets = new Insets(15, 5, 5, 10);
		yearPanel.add(startYearLabel, gbc);

		gbc.gridx = 1;
		gbc.gridy = 1;
		gbc.anchor = GridBagConstraints.WEST;
		gbc.insets = new Insets(15, 5, 5, 5);
		yearPanel.add(startYearSpinner, gbc);

		// Année de fin
		JLabel endYearLabel = new JLabel("Année de fin (max 2040):");
		endYearLabel.setFont(labelFont);
		endYearLabel.setForeground(TEXT_COLOR);
		gbc.gridx = 0;
		gbc.gridy = 2;
		gbc.anchor = GridBagConstraints.EAST;
		gbc.insets = new Insets(10, 5, 5, 10);
		yearPanel.add(endYearLabel, gbc);

		gbc.gridx = 1;
		gbc.gridy = 2;
		gbc.anchor = GridBagConstraints.WEST;
		gbc.insets = new Insets(10, 5, 5, 5);
		yearPanel.add(endYearSpinner, gbc);

		// Message d'erreur
		gbc.gridx = 0;
		gbc.gridy = 3;
		gbc.gridwidth = 2;
		gbc.insets = new Insets(5, 5, 5, 5);
		yearPanel.add(errorMessageLabel, gbc);

		// Panneau de sélection du fichier GAMS avec légère transparence
		JPanel filePanel = new JPanel();
		filePanel.setLayout(new GridBagLayout());
		filePanel.setBackground(new Color(CARD_COLOR.getRed(), CARD_COLOR.getGreen(), CARD_COLOR.getBlue(), 240)); // Légère transparence
		filePanel.setOpaque(true);
		filePanel.setBorder(BorderFactory.createCompoundBorder(
				BorderFactory.createMatteBorder(0, 0, 1, 0, new Color(230, 230, 230, 200)),
				BorderFactory.createEmptyBorder(PADDING, PADDING, PADDING, PADDING)
		));

		// Titre section fichier
		JLabel fileSectionTitle = new JLabel("Sélection du Modèle GAMS");
		fileSectionTitle.setFont(headerFont);
		fileSectionTitle.setForeground(PRIMARY_COLOR);
		fileSectionTitle.setIcon(UIManager.getIcon("FileView.fileIcon"));
		gbc.gridx = 0;
		gbc.gridy = 0;
		gbc.gridwidth = 3;
		gbc.anchor = GridBagConstraints.WEST;
		gbc.insets = new Insets(5, 5, 15, 5);
		filePanel.add(fileSectionTitle, gbc);

		// Label pour fichier
		JLabel fileLabel = new JLabel("Fichier GAMS à exécuter:");
		fileLabel.setFont(labelFont);
		fileLabel.setForeground(TEXT_COLOR);
		gbc.gridx = 0;
		gbc.gridy = 1;
		gbc.gridwidth = 1;
		gbc.anchor = GridBagConstraints.EAST;
		gbc.insets = new Insets(5, 5, 5, 10);
		filePanel.add(fileLabel, gbc);

		// Combobox
		gbc.gridx = 1;
		gbc.gridy = 1;
		gbc.weightx = 1.0;
		gbc.fill = GridBagConstraints.HORIZONTAL;
		gbc.anchor = GridBagConstraints.WEST;
		filePanel.add(gamsFileCombo, gbc);

		// Bouton parcourir
		gbc.gridx = 2;
		gbc.gridy = 1;
		gbc.weightx = 0.0;
		gbc.fill = GridBagConstraints.NONE;
		gbc.insets = new Insets(5, 10, 5, 5);
		filePanel.add(browseButton, gbc);

		// Panneau de boutons d'action avec légère transparence
		JPanel actionPanel = new JPanel();
		actionPanel.setLayout(new FlowLayout(FlowLayout.CENTER, 20, 15));
		actionPanel.setBackground(new Color(CARD_COLOR.getRed(), CARD_COLOR.getGreen(), CARD_COLOR.getBlue(), 240)); // Légère transparence
		actionPanel.setOpaque(true);
		actionPanel.setBorder(BorderFactory.createEmptyBorder(PADDING, PADDING, PADDING, PADDING));

		actionPanel.add(compileButton);
		actionPanel.add(startButton);

		// Assemble les différentes sections dans le panneau principal
		mainPanel.add(yearPanel);
		mainPanel.add(filePanel);
		mainPanel.add(actionPanel);

		mainCardPanel.add(mainPanel, BorderLayout.CENTER);

		// Panneau de statut avec légère transparence
		JPanel statusPanel = new JPanel(new BorderLayout(10, 0));
		statusPanel.setBackground(new Color(CARD_COLOR.getRed(), CARD_COLOR.getGreen(), CARD_COLOR.getBlue(), 240)); // Légère transparence
		statusPanel.setOpaque(true);
		statusPanel.setBorder(BorderFactory.createEmptyBorder(8, 15, 8, 15));

		statusPanel.add(statusLabel, BorderLayout.WEST);
		statusPanel.add(progressBar, BorderLayout.CENTER);

		// Assembler tous les composants dans le panneau d'arrière-plan
		backgroundPanel.add(headerPanel, BorderLayout.NORTH);
		backgroundPanel.add(mainCardPanel, BorderLayout.CENTER);
		backgroundPanel.add(statusPanel, BorderLayout.SOUTH);
	}

	private Border getShadowBorder() {
		return new CompoundBorder(
				new MatteBorder(1, 1, 1, 1, new Color(218, 218, 218)),
				new MatteBorder(0, 0, 2, 0, new Color(200, 200, 200))
		);
	}

	private void addEventListeners() {
		// Gestion du bouton parcourir
		browseButton.addActionListener(e -> {
			JFileChooser fileChooser = new JFileChooser();
			fileChooser.setCurrentDirectory(new File(PROJECT_PATH + "\\CIV_MPE_Structure"));
			fileChooser.setFileFilter(new FileNameExtensionFilter("Fichiers GAMS (*.gms)", "gms"));

			int result = fileChooser.showOpenDialog(this);
			if (result == JFileChooser.APPROVE_OPTION) {
				File selectedFile = fileChooser.getSelectedFile();
				selectedGamsFilePath = selectedFile.getAbsolutePath();

				// Mise à jour de la combobox
				boolean fileAlreadyInCombo = false;
				for (int i = 0; i < gamsFileCombo.getItemCount(); i++) {
					if (gamsFileCombo.getItemAt(i).equals(selectedFile.getName())) {
						gamsFileCombo.setSelectedIndex(i);
						fileAlreadyInCombo = true;
						break;
					}
				}

				if (!fileAlreadyInCombo) {
					gamsFileCombo.addItem(selectedFile.getName());
					gamsFileCombo.setSelectedItem(selectedFile.getName());
				}

				logToBuffer("Fichier GAMS sélectionné: " + selectedGamsFilePath);
			}
		});

		// Gestion de la sélection dans la combobox
		gamsFileCombo.addActionListener(e -> {
			String selectedFileName = (String) gamsFileCombo.getSelectedItem();
			if (selectedFileName != null && !selectedFileName.isEmpty()) {
				selectedGamsFilePath = PROJECT_PATH + "\\CIV_MPE_Structure\\" + selectedFileName;
			}
		});

		// Validation de la plage d'années
		endYearSpinner.addChangeListener(e -> validateYearRange());

		// Gestion du bouton compiler
		compileButton.addActionListener(e -> {
			if (checkGamsExecutable() && validateYearRange()) {
				updateOptIncFile();

				int endYear = (Integer) endYearSpinner.getValue();

				// Réinitialiser la zone de sortie et le buffer
				dialogOutputArea.setText("");
				outputBuffer.setLength(0);

				// Mise à jour UI
				setProcessing(true, "Compilation en cours...");

				// Exécuter GAMS en mode compilation, sans afficher le journal directement
				executorService.submit(() -> {
					try {
						// Option de compilation seulement
						executeGamsWithoutTerminal(selectedGamsFilePath, "action=c", "Compilation GAMS");
					} finally {
						// Réactiver les boutons quand c'est terminé
						SwingUtilities.invokeLater(() -> {
							setProcessing(false, "Compilation terminée");
						});
					}
				});
			}
		});

		// Gestion du bouton démarrer
		startButton.addActionListener(e -> {
			if (checkGamsExecutable() && validateYearRange()) {
				updateOptIncFile();

				int endYear = (Integer) endYearSpinner.getValue();

				// Réinitialiser la zone de sortie et le buffer
				dialogOutputArea.setText("");
				outputBuffer.setLength(0);

				// Mise à jour UI
				setProcessing(true, "Simulation en cours...");

				// Exécuter GAMS en mode exécution complète, sans afficher le journal directement
				executorService.submit(() -> {
					try {
						executeGamsWithoutTerminal(selectedGamsFilePath, "", "Simulation GAMS");
					} finally {
						// Réactiver les boutons quand c'est terminé
						SwingUtilities.invokeLater(() -> {
							setProcessing(false, "Simulation terminée");
						});
					}
				});
			}
		});
	}

	private void setProcessing(boolean processing, String status) {
		compileButton.setEnabled(!processing);
		startButton.setEnabled(!processing);
		browseButton.setEnabled(!processing);
		gamsFileCombo.setEnabled(!processing);
		endYearSpinner.setEnabled(!processing);

		progressBar.setVisible(processing);
		statusLabel.setText(status);

		if (processing) {
			statusLabel.setForeground(SECONDARY_COLOR);
		} else {
			statusLabel.setForeground(TEXT_COLOR);
		}

		// Indique si un processus est en cours d'exécution
		processRunning = processing;
	}

	private void logToBuffer(String message) {
		outputBuffer.append("[INFO] " + message + "\n");
		dialogOutputArea.append("[INFO] " + message + "\n");
	}

	private boolean validateYearRange() {
		int endYear = (Integer) endYearSpinner.getValue();

		// Vérifier que l'année de fin est dans la plage autorisée
		if (endYear < FIXED_START_YEAR || endYear > MAX_YEAR) {
			errorMessageLabel.setText("L'année de fin doit être comprise entre " + FIXED_START_YEAR + " et " + MAX_YEAR);
			errorMessageLabel.setVisible(true);
			return false;
		}

		// Si tout est correct, masquer le message d'erreur
		errorMessageLabel.setVisible(false);
		return true;
	}

	private void updateOptIncFile() {
		try {
			// Lire le fichier opt.inc
			Path optIncPath = Paths.get(OPT_INC_PATH);
			if (!Files.exists(optIncPath)) {
				logToBuffer("Le fichier opt.inc n'a pas été trouvé à l'emplacement: " + OPT_INC_PATH);
				return;
			}

			String content = new String(Files.readAllBytes(optIncPath), StandardCharsets.UTF_8);

			// Obtenir les années de début et de fin
			int endYear = (Integer) endYearSpinner.getValue();

			// Définir plusieurs patterns possibles pour la ligne de temps de simulation
			List<String> patterns = new ArrayList<>();
			// Pattern exact correspondant à votre fichier
			patterns.add("t\\(tf\\)\\s+sim\\s+time\\s+/\\s*\\d+\\*\\d+\\s*/");
			// Pattern avec des espaces supplémentaires
			patterns.add("t\\s*\\(\\s*tf\\s*\\)\\s+sim\\s+time\\s+/\\s*\\d+\\s*\\*\\s*\\d+\\s*/");
			// Pattern avec formatage différent
			patterns.add("t\\(tf\\)\\s+sim\\s+time\\s*/\\s*\\d+\\*\\d+\\s*/");

			boolean found = false;

			for (String pattern : patterns) {
				Pattern regexPattern = Pattern.compile(pattern);
				Matcher matcher = regexPattern.matcher(content);

				if (matcher.find()) {
					// Construire le remplacement - préserver le formatage original
					String originalText = matcher.group(0);
					String replacement = originalText.replaceFirst("\\d+\\*\\d+", FIXED_START_YEAR + "*" + endYear);

					// Remplacer dans le contenu
					String modifiedContent = content.replace(originalText, replacement);
					Files.write(optIncPath, modifiedContent.getBytes(StandardCharsets.UTF_8));

					logToBuffer("Plage de simulation mise à jour dans opt.inc: " + FIXED_START_YEAR + " à " + endYear);
					found = true;
					break;
				}
			}

			if (!found) {
				// Essai plus générique - chercher une ligne avec "t(tf)" et "sim time"
				int startIdx = content.indexOf("t(tf)");
				int endIdx = -1;

				if (startIdx != -1) {
					// Chercher la fin de ligne après t(tf)
					endIdx = content.indexOf("/", startIdx);
					if (endIdx != -1) {
						// Chercher le prochain caractère de nouvelle ligne après la fin de la directive
						int nextNewline = content.indexOf("\n", endIdx);
						if (nextNewline != -1) {
							String originalLine = content.substring(startIdx, nextNewline);

							// Vérifier si cette ligne contient une plage d'années (recherche de x*y)
							Pattern yearPattern = Pattern.compile("(\\d+)\\*(\\d+)");
							Matcher yearMatcher = yearPattern.matcher(originalLine);

							if (yearMatcher.find()) {
								// Remplacer la plage d'années
								String modifiedLine = originalLine.replaceFirst("\\d+\\*\\d+", FIXED_START_YEAR + "*" + endYear);
								String modifiedContent = content.replace(originalLine, modifiedLine);
								Files.write(optIncPath, modifiedContent.getBytes(StandardCharsets.UTF_8));

								logToBuffer("Plage de simulation mise à jour dans opt.inc: " + FIXED_START_YEAR + " à " + endYear);
								found = true;
							}
						}
					}
				}

				if (!found) {
					logToBuffer("Impossible de trouver la ligne de plage de temps dans opt.inc");
					logToBuffer("Veuillez vérifier manuellement le fichier: " + OPT_INC_PATH);

					// Afficher le début du contenu du fichier pour aider au débogage
					String contentStart = content.substring(0, Math.min(500, content.length())) + "...";
					logToBuffer("Début du fichier opt.inc:");
					logToBuffer("---------------------------------------");
					logToBuffer(contentStart);
					logToBuffer("---------------------------------------");
				}
			}

		} catch (IOException e) {
			logToBuffer("Erreur lors de la mise à jour du fichier opt.inc: " + e.getMessage());
			e.printStackTrace();
		}
	}

	private boolean checkGamsExecutable() {
		// Vérifier d'abord si le chemin est un répertoire et non un fichier
		File gamsPath = new File(gamsExecutablePath);
		if (gamsPath.isDirectory()) {
			// Si c'est un répertoire, essayer de trouver gams.exe à l'intérieur
			gamsExecutablePath = new File(gamsPath, "gams.exe").getAbsolutePath();
			logToBuffer("Chemin ajusté pour pointer vers l'exécutable: " + gamsExecutablePath);
		}

		File gamsExe = new File(gamsExecutablePath);
		if (!gamsExe.exists()) {
			JOptionPane.showMessageDialog(
					this,
					"Impossible de trouver l'exécutable GAMS à l'emplacement:\n" +
							gamsExecutablePath + "\n\n" +
							"Veuillez spécifier manuellement son emplacement.",
					"GAMS introuvable",
					JOptionPane.WARNING_MESSAGE
			);

			// Permettre à l'utilisateur de spécifier le chemin de GAMS
			JFileChooser fileChooser = new JFileChooser();
			fileChooser.setDialogTitle("Sélectionner l'exécutable GAMS");
			fileChooser.setFileFilter(new FileNameExtensionFilter("Exécutable (*.exe)", "exe"));

			if (fileChooser.showOpenDialog(this) == JFileChooser.APPROVE_OPTION) {
				gamsExecutablePath = fileChooser.getSelectedFile().getAbsolutePath();
				logToBuffer("Nouvel emplacement de GAMS spécifié: " + gamsExecutablePath);
				return checkGamsExecutable(); // Vérifier à nouveau
			}

			return false;
		}

		// Vérifier les permissions d'exécution
		if (!gamsExe.canExecute()) {
			try {
				// Essayer de définir le fichier comme exécutable
				boolean success = gamsExe.setExecutable(true);
				if (!success) {
					JOptionPane.showMessageDialog(
							this,
							"Impossible de définir les permissions d'exécution pour GAMS.\n" +
									"Vous devrez peut-être exécuter ce programme en tant qu'administrateur.",
							"Erreur de permissions",
							JOptionPane.ERROR_MESSAGE
					);
					return false;
				}
			} catch (SecurityException se) {
				JOptionPane.showMessageDialog(
						this,
						"Accès refusé lors de la tentative de modification des permissions:\n" + se.getMessage(),
						"Erreur de sécurité",
						JOptionPane.ERROR_MESSAGE
				);
				return false;
			}
		}

		return true;
	}

	private void checkGamsInstallation() {
		// Effacer le buffer au démarrage
		outputBuffer.setLength(0);

		if (!checkGamsExecutable()) {
			// Afficher directement un message d'erreur à l'utilisateur plutôt que d'utiliser le terminal
			JOptionPane.showMessageDialog(
					this,
					"GAMS n'a pas été trouvé à l'emplacement par défaut.\n" +
							"Les fonctionnalités de compilation et exécution peuvent ne pas fonctionner.\n" +
							"Vous pourrez spécifier manuellement l'emplacement de GAMS lors de la compilation.",
					"GAMS non trouvé",
					JOptionPane.WARNING_MESSAGE
			);

			// Stocker l'information dans le buffer pour référence future
			logToBuffer("GAMS n'a pas été trouvé à l'emplacement par défaut.");
			logToBuffer("Les fonctionnalités de compilation et exécution peuvent ne pas fonctionner.");
			logToBuffer("Vous pouvez spécifier manuellement l'emplacement de GAMS lors de la compilation.");
		} else {
			// Afficher un message de succès
			JOptionPane.showMessageDialog(
					this,
					"GAMS a été trouvé avec succès à :\n" + gamsExecutablePath + "\n\n" +
							"Le système est prêt pour l'exécution de modèles GAMS.",
					"GAMS trouvé",
					JOptionPane.INFORMATION_MESSAGE
			);

			// Stocker l'information dans le buffer pour référence future
			logToBuffer("GAMS trouvé à: " + gamsExecutablePath);
			logToBuffer("Système prêt pour l'exécution de modèles GAMS.");
		}
	}

	// Méthode pour afficher le journal d'exécution à la demande
	private void showExecutionLog(String operationType) {
		// Création d'une boîte de dialogue pour afficher le journal
		JDialog logDialog = new JDialog((Frame) SwingUtilities.getWindowAncestor(this),
				"Journal d'exécution - " + operationType, false);
		logDialog.setLayout(new BorderLayout());
		logDialog.setSize(800, 600);
		logDialog.setLocationRelativeTo(null);

		// En-tête
		JPanel headerPanel = new JPanel(new BorderLayout());
		headerPanel.setBackground(PRIMARY_COLOR);
		headerPanel.setBorder(BorderFactory.createEmptyBorder(10, 15, 10, 15));

		JLabel titleLabel = new JLabel("Journal d'exécution - " + operationType);
		titleLabel.setFont(headerFont);
		titleLabel.setForeground(Color.WHITE);
		titleLabel.setIcon(UIManager.getIcon("Tree.openIcon"));
		headerPanel.add(titleLabel, BorderLayout.WEST);

		// Zone de texte pour le journal
		JTextArea logTextArea = new JTextArea(outputBuffer.toString());
		logTextArea.setEditable(false);
		logTextArea.setFont(new Font("Consolas", Font.PLAIN, 13));
		logTextArea.setBackground(new Color(40, 44, 52));
		logTextArea.setForeground(new Color(171, 178, 191));
		logTextArea.setMargin(new Insets(PADDING, PADDING, PADDING, PADDING));

		JScrollPane scrollPane = new JScrollPane(logTextArea);
		scrollPane.setBorder(null);

		// Barre de boutons en bas
		JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
		buttonPanel.setBorder(BorderFactory.createMatteBorder(1, 0, 0, 0, new Color(230, 230, 230)));

		JButton saveButton = createStyledButton("Enregistrer le journal", SECONDARY_COLOR);
		saveButton.addActionListener(evt -> {
			JFileChooser fileChooser = new JFileChooser();
			fileChooser.setDialogTitle("Enregistrer le journal");
			fileChooser.setFileFilter(new FileNameExtensionFilter("Fichiers texte (*.txt)", "txt"));

			if (fileChooser.showSaveDialog(logDialog) == JFileChooser.APPROVE_OPTION) {
				File file = fileChooser.getSelectedFile();
				if (!file.getName().toLowerCase().endsWith(".txt")) {
					file = new File(file.getAbsolutePath() + ".txt");
				}

				try (PrintWriter writer = new PrintWriter(file, StandardCharsets.UTF_8)) {
					writer.write(outputBuffer.toString());
					JOptionPane.showMessageDialog(logDialog,
							"Journal enregistré avec succès dans : " + file.getAbsolutePath(),
							"Enregistrement réussi",
							JOptionPane.INFORMATION_MESSAGE);
				} catch (IOException ex) {
					JOptionPane.showMessageDialog(logDialog,
							"Erreur lors de l'enregistrement du journal : " + ex.getMessage(),
							"Erreur",
							JOptionPane.ERROR_MESSAGE);
				}
			}
		});

		JButton closeButton = createStyledButton("Fermer", PRIMARY_COLOR);
		closeButton.addActionListener(evt -> logDialog.dispose());

		buttonPanel.add(saveButton);
		buttonPanel.add(closeButton);

		// Assemblage de la boîte de dialogue
		logDialog.add(headerPanel, BorderLayout.NORTH);
		logDialog.add(scrollPane, BorderLayout.CENTER);
		logDialog.add(buttonPanel, BorderLayout.SOUTH);

		// Affichage
		logDialog.setVisible(true);
	}

	// Méthode pour exécuter GAMS sans afficher le terminal
	private void executeGamsWithoutTerminal(String gamsFilePath, String additionalOptions, String operationType) {
		try {
			File workingDir = new File(gamsFilePath).getParentFile();
			String fileName = new File(gamsFilePath).getName();

			// Log pour le buffer interne seulement (pas d'affichage dans un terminal visible)
			logToBuffer("Exécution de la commande: " + gamsExecutablePath + " " + fileName);
			logToBuffer("Dans le répertoire: " + workingDir.getAbsolutePath());
			if (!additionalOptions.isEmpty()) {
				logToBuffer("Avec les options: " + additionalOptions);
			}

			// Construire la commande GAMS
			List<String> command = new ArrayList<>();

			// Ajouter l'exécutable GAMS
			command.add(gamsExecutablePath);

			// Ajouter le nom du fichier
			command.add(fileName);

			// Ajouter les options supplémentaires si elles existent
			if (!additionalOptions.isEmpty()) {
				command.add(additionalOptions);
			}

			// Ajouter le niveau de journalisation
			command.add("lo=3");

			ProcessBuilder processBuilder = new ProcessBuilder(command);

			// Définir le répertoire de travail
			processBuilder.directory(workingDir);

			// Rediriger les erreurs vers la sortie standard
			processBuilder.redirectErrorStream(true);

			// Afficher la commande complète pour le log interne
			StringBuilder fullCommand = new StringBuilder();
			for (String part : processBuilder.command()) {
				fullCommand.append(part).append(" ");
			}
			final String commandString = fullCommand.toString();
			logToBuffer("Commande complète: " + commandString);

			// Démarrer le processus
			currentProcess = processBuilder.start();

			// Créer un thread pour lire la sortie du processus (mais sans l'afficher)
			Thread outputThread = new Thread(() -> {
				try (BufferedReader reader = new BufferedReader(new InputStreamReader(currentProcess.getInputStream()))) {
					String line;
					while ((line = reader.readLine()) != null) {
						final String outputLine = line;
						// Stocker dans le buffer sans afficher
						outputBuffer.append(outputLine).append("\n");
						dialogOutputArea.append(outputLine + "\n");
					}
				} catch (IOException e) {
					outputBuffer.append("[ERREUR] Erreur lors de la lecture de la sortie: " + e.getMessage() + "\n");
				}
			});
			outputThread.setDaemon(true);
			outputThread.start();

			// Attendre que le processus se termine dans un thread séparé
			Thread waitThread = new Thread(() -> {
				try {
					int exitCode = currentProcess.waitFor();

					// S'assurer que le thread de lecture de sortie est terminé
					outputThread.join(1000);

					// Préparer les messages de résultat
					final String resultMessage = "Processus GAMS terminé avec le code: " + exitCode;
					final String statusMessage = exitCode == 0 ?
							operationType + " terminée avec succès" :
							operationType + " terminée avec erreurs";

					// Pour un processus réussi, récupérer l'information sur les fichiers de résultat
					File lstFile = null;
					if (exitCode == 0) {
						lstFile = new File(workingDir, fileName.replace(".gms", ".lst"));
						if (lstFile.exists()) {
							outputBuffer.append("[INFO] Fichier de résultat créé: " + lstFile.getName() + "\n");
							outputBuffer.append("[INFO] Chemin: " + lstFile.getAbsolutePath() + "\n");
						}
					}

					// Afficher une boîte de dialogue de résultat
					final File finalLstFile = lstFile;
					SwingUtilities.invokeLater(() -> {
						if (exitCode == 0) {
							// Succès - afficher un message avec des options
							Object[] options = {"Voir le journal d'exécution", "Ouvrir le fichier résultat", "Fermer"};

							int choice = JOptionPane.showOptionDialog(
									null,
									operationType + " terminée avec succès.\n" +
											(finalLstFile != null && finalLstFile.exists() ?
													"Un fichier de résultat a été créé à : \n" + finalLstFile.getAbsolutePath() : ""),
									"Succès",
									JOptionPane.YES_NO_CANCEL_OPTION,
									JOptionPane.INFORMATION_MESSAGE,
									null,
									options,
									options[2]  // option par défaut: "Fermer"
							);

							if (choice == 0) {
								// Afficher le journal d'exécution
								showExecutionLog(operationType);
							} else if (choice == 1 && finalLstFile != null && finalLstFile.exists()) {
								// Ouvrir le fichier résultat
								try {
									Desktop.getDesktop().open(finalLstFile);
								} catch (IOException ex) {
									JOptionPane.showMessageDialog(
											null,
											"Impossible d'ouvrir le fichier résultat : " + ex.getMessage(),
											"Erreur",
											JOptionPane.ERROR_MESSAGE
									);
								}
							}
							// Pour l'option "Fermer", ne rien faire de plus
						} else {
							// Erreur - afficher un message avec option de voir le journal
							Object[] options = {"Voir le journal d'exécution", "Fermer"};

							int choice = JOptionPane.showOptionDialog(
									null,
									operationType + " terminée avec des erreurs.\n" +
											"Code de sortie : " + exitCode,
									"Erreur",
									JOptionPane.YES_NO_OPTION,
									JOptionPane.ERROR_MESSAGE,
									null,
									options,
									options[1]  // option par défaut: "Fermer"
							);

							if (choice == 0) {
								// Afficher le journal d'exécution
								showExecutionLog(operationType);
							}
							// Pour l'option "Fermer", ne rien faire de plus
						}

						// Mettre à jour le statut dans l'interface principale
						statusLabel.setText(statusMessage);
						statusLabel.setForeground(exitCode == 0 ? ACCENT_COLOR : ERROR_COLOR);

						// Libérer les ressources du processus
						cleanupProcess(currentProcess);

						// Réinitialiser les références
						currentProcess = null;
						processRunning = false;
					});

				} catch (InterruptedException e) {
					SwingUtilities.invokeLater(() -> {
						outputBuffer.append("[ERREUR] Processus interrompu: " + e.getMessage() + "\n");
						processRunning = false;
						currentProcess = null;

						JOptionPane.showMessageDialog(
								null,
								"Le processus a été interrompu de manière inattendue.",
								"Erreur",
								JOptionPane.ERROR_MESSAGE
						);
					});
				}
			});
			waitThread.setDaemon(true);
			waitThread.start();

		} catch (IOException e) {
			final String errorMessage = "Erreur lors de l'exécution de GAMS: " + e.getMessage();
			SwingUtilities.invokeLater(() -> {
				// Stocker l'erreur dans le buffer
				outputBuffer.append("\n========== ERREUR D'EXÉCUTION ==========\n");
				outputBuffer.append("[ERREUR] " + errorMessage + "\n");

				// Afficher la trace d'erreur complète dans le buffer
				StringWriter sw = new StringWriter();
				e.printStackTrace(new PrintWriter(sw));
				String stackTrace = sw.toString();
				outputBuffer.append("\nTrace d'erreur complète:\n")
						.append("---------------------------------------\n")
						.append(stackTrace)
						.append("---------------------------------------\n");

				// Afficher une boîte de dialogue d'erreur avec option de voir le journal
				Object[] options = {"Voir le journal d'exécution", "Fermer"};

				int choice = JOptionPane.showOptionDialog(
						null,
						"Une erreur s'est produite lors de l'exécution de GAMS:\n" + e.getMessage(),
						"Erreur",
						JOptionPane.YES_NO_OPTION,
						JOptionPane.ERROR_MESSAGE,
						null,
						options,
						options[1]  // option par défaut: "Fermer"
				);

				if (choice == 0) {
					// Afficher le journal d'exécution
					showExecutionLog(operationType);
				}

				// Mettre à jour le statut dans l'interface principale
				statusLabel.setText("Erreur lors de l'exécution");
				statusLabel.setForeground(ERROR_COLOR);

				// Réinitialiser les références
				currentProcess = null;
				processRunning = false;
			});
		}
	}

	// Méthode pour terminer proprement un processus et ses flux
	private void cleanupProcess(Process process) {
		if (process != null) {
			try {
				// Fermer tous les flux
				process.getInputStream().close();
				process.getOutputStream().close();
				process.getErrorStream().close();

				// Terminer le processus
				process.destroy();

				// Si le processus ne se termine pas rapidement, le forcer
				if (process.isAlive()) {
					process.destroyForcibly();
				}
			} catch (IOException e) {
				// Ignorer les erreurs lors de la fermeture
			}
		}
	}

	// Méthode pour nettoyer les ressources lors de la fermeture
	public void cleanup() {
		if (executorService != null && !executorService.isShutdown()) {
			executorService.shutdown();
		}

		// Si un processus GAMS est en cours d'exécution, l'arrêter
		if (currentProcess != null && processRunning) {
			cleanupProcess(currentProcess);
			currentProcess = null;
			processRunning = false;
		}
	}
}