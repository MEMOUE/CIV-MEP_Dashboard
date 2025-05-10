package src;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.geom.RoundRectangle2D;
import java.util.ArrayList;
import java.util.List;

/**
 * Footer component for the MMPE Dashboard
 * Contains navigation buttons to different sections with professional design
 */
public class Footer extends JPanel {

	private List<NavButton> navButtons;
	private NavButton selectedButton;
	private PageChangeListener pageChangeListener;
	private Color primaryColor = new Color(41, 128, 185); // Bleu professionnel
	private Color secondaryColor = new Color(255, 243, 204); // Jaune clair pour la sélection
	private Color hoverColor = new Color(245, 245, 245); // Gris clair pour le survol
	private Color borderColor = new Color(230, 210, 160); // Bordure pour les boutons sélectionnés

	public Footer() {
		initComponents();
	}

	/**
	 * Interface for notifying page changes
	 */
	public interface PageChangeListener {
		void onPageChanged(String pageName);
	}

	public void setPageChangeListener(PageChangeListener listener) {
		this.pageChangeListener = listener;
	}

	private void initComponents() {
		// Set layout
		setLayout(new BorderLayout());
		setBackground(Color.WHITE);
		setBorder(BorderFactory.createCompoundBorder(
				BorderFactory.createMatteBorder(1, 0, 0, 0, new Color(220, 220, 220)),
				BorderFactory.createEmptyBorder(5, 0, 5, 0)
		));

		// Create main panel for buttons
		JPanel buttonsPanel = new JPanel() {
			@Override
			protected void paintComponent(Graphics g) {
				super.paintComponent(g);
				Graphics2D g2d = (Graphics2D) g;
				g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

				// Create gradient from top to bottom
				GradientPaint gradient = new GradientPaint(
						0, 0, new Color(255, 255, 255),
						0, getHeight(), new Color(245, 245, 245)
				);
				g2d.setPaint(gradient);
				g2d.fillRect(0, 0, getWidth(), getHeight());
			}
		};
		buttonsPanel.setLayout(new FlowLayout(FlowLayout.CENTER, 15, 8));
		buttonsPanel.setOpaque(false);

		// Create navigation buttons
		navButtons = new ArrayList<>();

		// Accueil (Home) button
		NavButton accueilBtn = createNavButton(
				"ACCUEIL",
				"images/home.png",
				"accueil"
		);

		// Modèles button
		NavButton modelesBtn = createNavButton(
				"MODÈLES ET SIMULATIONS",
				"images/model.png",
				"modeles"
		);

		// Résultats button
		NavButton resultatBtn = createNavButton(
				"RÉSULTATS GÉNÉRAUX",
				"images/resultat.png",
				"resultats"
		);

		// Mines button
		NavButton minesBtn = createNavButton(
				"MINES",
				"images/mine.png",
				"mines"
		);

		// Hydrocarbures button
		NavButton hydrocarburesBtn = createNavButton(
				"HYDROCARBURES",
				"images/hydrocarbure.png",
				"hydrocarbures"
		);

		// Energie button
		NavButton energieBtn = createNavButton(
				"ENERGIE",
				"images/energie.png",
				"energie"
		);

		// Add all buttons to the panel
		for (NavButton button : navButtons) {
			buttonsPanel.add(button);
		}

		// Add buttons panel to main panel
		add(buttonsPanel, BorderLayout.CENTER);

		// Set preferred size for the footer
		setPreferredSize(new Dimension(960, 110));
	}

	/**
	 * Utility method to create navigation buttons
	 */
	private NavButton createNavButton(String text, String imagePath, final String pageName) {
		NavButton button = new NavButton(text, imagePath, pageName);

		// Ajouter les événements via MouseListener (pas ActionListener car ce n'est plus un JButton)
		button.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				setSelectedButton(button);
				if (pageChangeListener != null) {
					pageChangeListener.onPageChanged(pageName);
				}
			}
		});

		navButtons.add(button);
		return button;
	}

	/**
	 * Set the selected button and update UI
	 */
	public void setSelectedButton(NavButton button) {
		if (selectedButton != null) {
			selectedButton.setSelected(false);
		}
		selectedButton = button;
		selectedButton.setSelected(true);
	}

	/**
	 * Set the selected page by name
	 */
	public void setSelectedPage(String pageName) {
		for (NavButton button : navButtons) {
			if (button.getPageName().equals(pageName)) {
				setSelectedButton(button);
				break;
			}
		}
	}

	/**
	 * Custom navigation button class with professional styling
	 */
	private class NavButton extends JPanel {
		private boolean selected;
		private boolean hover;
		private String pageName;
		private JLabel iconLabel;
		private JLabel textLabel;
		private Color bgColor = Color.WHITE;
		private float arcSize = 20.0f; // Rayon de l'arrondi

		public NavButton(String text, String imagePath, String pageName) {
			this.pageName = pageName;
			this.selected = false;
			this.hover = false;

			setLayout(new BorderLayout());
			setOpaque(false);
			setCursor(new Cursor(Cursor.HAND_CURSOR));
			setBorder(new EmptyBorder(8, 8, 8, 8));

			// Icon
			iconLabel = new JLabel();
			ImageIcon icon = loadImage(imagePath);
			if (icon != null) {
				icon = new ImageIcon(icon.getImage().getScaledInstance(42, 42, Image.SCALE_SMOOTH));
				iconLabel.setIcon(icon);
				iconLabel.setHorizontalAlignment(SwingConstants.CENTER);
			}

			// Text
			textLabel = new JLabel(text);
			textLabel.setFont(new Font("Arial", Font.BOLD, 12));
			textLabel.setHorizontalAlignment(SwingConstants.CENTER);
			textLabel.setBorder(new EmptyBorder(6, 0, 0, 0));
			textLabel.setForeground(new Color(80, 80, 80));

			// Add components with padding
			JPanel contentPanel = new JPanel(new BorderLayout(0, 5));
			contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
			contentPanel.setOpaque(false);
			contentPanel.add(iconLabel, BorderLayout.CENTER);
			contentPanel.add(textLabel, BorderLayout.SOUTH);

			add(contentPanel, BorderLayout.CENTER);

			// Set preferred size
			setPreferredSize(new Dimension(200, 90));

			// Add mouse listeners for hover effect
			addMouseListener(new MouseAdapter() {
				@Override
				public void mouseEntered(MouseEvent e) {
					if (!selected) {
						hover = true;
						updateColors();
						repaint();
					}
				}

				@Override
				public void mouseExited(MouseEvent e) {
					hover = false;
					updateColors();
					repaint();
				}

				@Override
				public void mousePressed(MouseEvent e) {
					// Effet visuel pour montrer que le bouton est enfoncé
					bgColor = new Color(secondaryColor.getRed() - 15,
							secondaryColor.getGreen() - 15,
							secondaryColor.getBlue() - 15);
					repaint();
				}

				@Override
				public void mouseReleased(MouseEvent e) {
					// Restaurer l'apparence après pression
					updateColors();
					repaint();
				}
			});

			updateColors();
		}

		public String getPageName() {
			return pageName;
		}

		public void setSelected(boolean selected) {
			this.selected = selected;
			updateColors();
			repaint();
		}

		private void updateColors() {
			if (selected) {
				bgColor = secondaryColor;
				textLabel.setForeground(new Color(50, 50, 50));
				textLabel.setFont(new Font("Arial", Font.BOLD, 12));
			} else if (hover) {
				bgColor = hoverColor;
				textLabel.setForeground(new Color(60, 60, 60));
				textLabel.setFont(new Font("Arial", Font.BOLD, 12));
			} else {
				bgColor = new Color(255, 255, 255, 0); // Transparent
				textLabel.setForeground(new Color(80, 80, 80));
				textLabel.setFont(new Font("Arial", Font.BOLD, 12));
			}
		}

		@Override
		protected void paintComponent(Graphics g) {
			Graphics2D g2d = (Graphics2D) g;
			g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

			// Dessiner le fond avec les coins arrondis
			g2d.setColor(bgColor);
			g2d.fill(new RoundRectangle2D.Float(0, 0, getWidth(), getHeight(), arcSize, arcSize));

			// Si sélectionné, dessiner la bordure et l'ombre
			if (selected) {
				// Dessiner une ombre légère
				g2d.setColor(new Color(0, 0, 0, 20));
				g2d.fill(new RoundRectangle2D.Float(2, 3, getWidth(), getHeight(), arcSize, arcSize));

				// Dessiner la bordure
				g2d.setColor(borderColor);
				g2d.setStroke(new BasicStroke(1.5f));
				g2d.draw(new RoundRectangle2D.Float(1, 1, getWidth()-2, getHeight()-2, arcSize, arcSize));

				// Dessiner un surlignage au-dessus du bouton
				g2d.setColor(new Color(220, 180, 80));
				g2d.fillRect(getWidth()/4, 0, getWidth()/2, 3);
			}

			super.paintComponent(g);
		}

		/**
		 * Utility method to load images
		 */
		private ImageIcon loadImage(String path) {
			try {
				return new ImageIcon(path);
			} catch (Exception e) {
				System.err.println("Error loading image: " + e.getMessage());
				return null;
			}
		}
	}
}