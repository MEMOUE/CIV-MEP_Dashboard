package src;

import javax.swing.*;
import java.awt.*;
import java.io.File;

/**
 * Accueil (Home) page component for the MMPE Dashboard
 * Displays the main background image with menu title
 */
public class Accueil extends JPanel {

	private Image backgroundImage;
	private JLabel titleLabel;
	private JLabel subtitleLabel;
	private JLabel ssubtitleLabel;

	public Accueil() {
		initComponents();
	}

	private void initComponents() {
		setLayout(new BorderLayout());

		// Load background image avec le chemin exact
		try {
			// Utiliser le chemin exact indiqué
			String imagePath = "Projet_MEGC/CIV_MPE_Structure/images/Accueil2.jpg";
			File file = new File(imagePath);
			if (file.exists()) {
				backgroundImage = new ImageIcon(imagePath).getImage();
				System.out.println("Image chargée avec succès: " + imagePath);
			} else {
				// Essayer un chemin alternatif si le premier échoue
				imagePath = "images/Accueil2.jpg";
				file = new File(imagePath);
				if (file.exists()) {
					backgroundImage = new ImageIcon(imagePath).getImage();
					System.out.println("Image chargée avec succès via chemin alternatif: " + imagePath);
				} else {
					System.err.println("Image d'arrière-plan introuvable à " + imagePath);
					backgroundImage = null;
				}
			}
		} catch (Exception e) {
			System.err.println("Erreur lors du chargement de l'image: " + e.getMessage());
			e.printStackTrace();
			backgroundImage = null;
		}

		// Create a central panel for the text content with a GridBagLayout for better centering
		JPanel contentPanel = new JPanel(new GridBagLayout()) {
			@Override
			protected void paintComponent(Graphics g) {
				// Custom painting for semi-transparent panel
				g.setColor(new Color(0, 0, 0, 100));
				g.fillRect(0, 0, getWidth(), getHeight());
			}
		};
		contentPanel.setOpaque(false);

		// Créer un sous-panel pour organiser verticalement les textes
		JPanel textPanel = new JPanel();
		textPanel.setLayout(new BoxLayout(textPanel, BoxLayout.Y_AXIS));
		textPanel.setOpaque(false);

		// Title "MENU PRINCIPAL"
		titleLabel = new JLabel("MENU PRINCIPAL");
		titleLabel.setFont(new Font("Arial", Font.BOLD, 48));
		titleLabel.setForeground(Color.WHITE);
		titleLabel.setAlignmentX(Component.CENTER_ALIGNMENT);
		titleLabel.setHorizontalAlignment(SwingConstants.CENTER);

		// Subtitle
		subtitleLabel = new JLabel("Bienvenue sur le Tableau de Bord");
		subtitleLabel.setFont(new Font("Arial", Font.PLAIN, 18));
		subtitleLabel.setForeground(Color.WHITE);
		subtitleLabel.setAlignmentX(Component.CENTER_ALIGNMENT);
		subtitleLabel.setHorizontalAlignment(SwingConstants.CENTER);

		// Second subtitle
		ssubtitleLabel = new JLabel("CIV-MEP");
		ssubtitleLabel.setFont(new Font("Arial", Font.BOLD, 48));
		ssubtitleLabel.setForeground(Color.WHITE);
		ssubtitleLabel.setAlignmentX(Component.CENTER_ALIGNMENT);
		ssubtitleLabel.setHorizontalAlignment(SwingConstants.CENTER);

		// Définir la taille maximale des labels pour qu'ils prennent toute la largeur disponible
		titleLabel.setMaximumSize(new Dimension(Integer.MAX_VALUE, titleLabel.getPreferredSize().height));
		subtitleLabel.setMaximumSize(new Dimension(Integer.MAX_VALUE, subtitleLabel.getPreferredSize().height));
		ssubtitleLabel.setMaximumSize(new Dimension(Integer.MAX_VALUE, ssubtitleLabel.getPreferredSize().height));

		// Ajouter les composants au panel de texte avec espacement réduit
		textPanel.add(Box.createVerticalStrut(20)); // Marge supérieure
		textPanel.add(titleLabel);
		textPanel.add(Box.createVerticalStrut(10)); // Espacement réduit entre titre et sous-titre (était 20)
		textPanel.add(subtitleLabel);
		textPanel.add(Box.createVerticalStrut(10)); // Espacement réduit entre sous-titre et CIV-MEP (était 40)
		textPanel.add(ssubtitleLabel);
		textPanel.add(Box.createVerticalStrut(20)); // Marge inférieure

		// Définir une taille préférée pour le panel de texte
		textPanel.setPreferredSize(new Dimension(600, 200)); // Hauteur réduite pour rapprocher les éléments

		// Ajouter le panel de texte au panel de contenu
		contentPanel.add(textPanel);

		// Add the content panel to the center
		add(contentPanel, BorderLayout.CENTER);
	}

	@Override
	protected void paintComponent(Graphics g) {
		super.paintComponent(g);

		// Draw the background image
		if (backgroundImage != null) {
			Graphics2D g2d = (Graphics2D) g.create();
			g2d.drawImage(backgroundImage, 0, 0, getWidth(), getHeight(), this);
			g2d.dispose();
		} else {
			// Fallback color if image not available
			g.setColor(new Color(51, 51, 51));
			g.fillRect(0, 0, getWidth(), getHeight());
		}
	}
}