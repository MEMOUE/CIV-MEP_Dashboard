package src;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import java.awt.*;
import java.io.File;

/**
 * Header component for the MMPE Dashboard
 * Displays the ministry logo, title and national emblem
 */
public class Header extends JPanel {

	private JLabel ssubtitleLabel;
	private JLabel titleLabel;
	private JLabel emblemeLabel;
	private int leftRightMargin = 25; // Marge à gauche et à droite

	public Header() {
		initComponents();
	}

	private void initComponents() {
		// Set layout
		setLayout(new BorderLayout());
		setBackground(Color.WHITE);
		setBorder(BorderFactory.createCompoundBorder(
				BorderFactory.createMatteBorder(0, 0, 1, 0, new Color(220, 220, 220)),
				BorderFactory.createEmptyBorder(5, 0, 5, 0)
		));

		// Panel principal avec marges
		JPanel mainPanel = new JPanel(new BorderLayout());
		mainPanel.setBackground(Color.WHITE);
		mainPanel.setBorder(new EmptyBorder(0, leftRightMargin, 0, leftRightMargin));

		// Logo stylisé on the left with panel
		JPanel logoPanel = new JPanel(new BorderLayout());
		logoPanel.setBackground(Color.WHITE);
		logoPanel.setBorder(new EmptyBorder(0, 0, 0, 10)); // Marge à droite du logo

		// Création du label stylisé CIV-MEP avec HTML pour les couleurs
		ssubtitleLabel = new JLabel("<html><span style='color: #FF8C00; font-family: Segoe Print; font-size: 40pt; font-weight: bold;'>CIV-</span><span style='color: #2ECC71; font-family: Segoe Print; font-size: 40pt; font-weight: bold;'>MEP</span></html>");
		ssubtitleLabel.setPreferredSize(new Dimension(200, 80));
		ssubtitleLabel.setHorizontalAlignment(SwingConstants.CENTER);
		ssubtitleLabel.setVerticalAlignment(SwingConstants.CENTER);
		logoPanel.add(ssubtitleLabel, BorderLayout.CENTER);
		mainPanel.add(logoPanel, BorderLayout.WEST);

		// Title in the center with improved styling
		JPanel titlePanel = new JPanel();
		titlePanel.setLayout(new BoxLayout(titlePanel, BoxLayout.Y_AXIS));
		titlePanel.setBackground(Color.WHITE);
		titlePanel.setBorder(new EmptyBorder(8, 0, 8, 0)); // Marge verticale

		JLabel republicLabel = new JLabel("RÉPUBLIQUE DE CÔTE D'IVOIRE");
		republicLabel.setFont(new Font("Arial", Font.BOLD, 18));
		republicLabel.setForeground(new Color(80, 80, 80));
		republicLabel.setAlignmentX(Component.CENTER_ALIGNMENT);

		titleLabel = new JLabel("MINISTÈRE DES MINES, DU PÉTROLE ET DE L'ÉNERGIE");
		titleLabel.setFont(new Font("Arial", Font.BOLD, 20));
		titleLabel.setForeground(new Color(50, 50, 50));
		titleLabel.setAlignmentX(Component.CENTER_ALIGNMENT);

		titlePanel.add(Box.createVerticalGlue());
		titlePanel.add(republicLabel);
		titlePanel.add(Box.createVerticalStrut(8)); // Espacement augmenté
		titlePanel.add(titleLabel);
		titlePanel.add(Box.createVerticalGlue());

		mainPanel.add(titlePanel, BorderLayout.CENTER);

		// National emblem on the right with panel
		JPanel emblemePanel = new JPanel(new BorderLayout());
		emblemePanel.setBackground(Color.WHITE);
		emblemePanel.setBorder(new EmptyBorder(0, 10, 0, 0)); // Marge à gauche de l'emblème

		emblemeLabel = new JLabel();
		ImageIcon emblemeIcon = loadImage("images/symbole.png");
		if (emblemeIcon != null) {
			emblemeIcon = new ImageIcon(emblemeIcon.getImage().getScaledInstance(85, 85, Image.SCALE_SMOOTH));
			emblemeLabel.setIcon(emblemeIcon);
		}
		emblemeLabel.setPreferredSize(new Dimension(120, 80));
		emblemeLabel.setHorizontalAlignment(SwingConstants.RIGHT);
		emblemePanel.add(emblemeLabel, BorderLayout.CENTER);
		mainPanel.add(emblemePanel, BorderLayout.EAST);

		// Ajouter un léger dégradé de fond
		JPanel backgroundPanel = new JPanel() {
			@Override
			protected void paintComponent(Graphics g) {
				super.paintComponent(g);
				Graphics2D g2d = (Graphics2D) g;
				g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

				// Créer un dégradé très subtil de haut en bas
				GradientPaint gradient = new GradientPaint(
						0, 0, new Color(255, 255, 255),
						0, getHeight(), new Color(248, 248, 248)
				);
				g2d.setPaint(gradient);
				g2d.fillRect(0, 0, getWidth(), getHeight());
			}
		};
		backgroundPanel.setLayout(new BorderLayout());
		backgroundPanel.add(mainPanel, BorderLayout.CENTER);

		// Ajouter le panel principal au header
		add(backgroundPanel, BorderLayout.CENTER);

		// Set preferred size for the whole header
		setPreferredSize(new Dimension(960, 96));
	}

	/**
	 * Utility method to load images
	 */
	private ImageIcon loadImage(String path) {
		try {
			File file = new File(path);
			if (file.exists()) {
				return new ImageIcon(path);
			} else {
				System.err.println("Image file not found: " + path);
				return null;
			}
		} catch (Exception e) {
			System.err.println("Error loading image: " + e.getMessage());
			return null;
		}
	}
}