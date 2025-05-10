package src;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.geom.*;
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
	private Color iconColor = new Color(60, 60, 60); // Couleur des icônes

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
				new HomeIcon(),
				"accueil"
		);

		// Modèles button
		NavButton modelesBtn = createNavButton(
				"MODÈLES ET SIMULATIONS",
				new ModelIcon(),
				"modeles"
		);

		// Résultats button
		NavButton resultatBtn = createNavButton(
				"RÉSULTATS GÉNÉRAUX",
				new ResultatIcon(),
				"resultats"
		);

		// Mines button
		NavButton minesBtn = createNavButton(
				"MINES",
				new MineIcon(),
				"mines"
		);

		// Hydrocarbures button
		NavButton hydrocarburesBtn = createNavButton(
				"HYDROCARBURES",
				new HydrocarbureIcon(),
				"hydrocarbures"
		);

		// Energie button
		NavButton energieBtn = createNavButton(
				"ENERGIE",
				new EnergieIcon(),
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
	private NavButton createNavButton(String text, Icon icon, final String pageName) {
		NavButton button = new NavButton(text, icon, pageName);

		// Ajouter les événements via MouseListener
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

		public NavButton(String text, Icon icon, String pageName) {
			this.pageName = pageName;
			this.selected = false;
			this.hover = false;

			setLayout(new BorderLayout());
			setOpaque(false);
			setCursor(new Cursor(Cursor.HAND_CURSOR));
			setBorder(new EmptyBorder(8, 8, 8, 8));

			// Icon
			iconLabel = new JLabel();
			iconLabel.setIcon(icon);
			iconLabel.setHorizontalAlignment(SwingConstants.CENTER);

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
	}

	/**
	 * Classes d'icônes personnalisées
	 */
	private abstract class BaseIcon implements Icon {
		protected int width = 42;
		protected int height = 42;
		protected Color color = iconColor;

		// Palette de couleurs attrayantes
		protected Color accentColor1 = new Color(41, 128, 185);    // Bleu
		protected Color accentColor2 = new Color(39, 174, 96);     // Vert
		protected Color accentColor3 = new Color(211, 84, 0);      // Orange
		protected Color accentColor4 = new Color(142, 68, 173);    // Violet
		protected Color accentColor5 = new Color(241, 196, 15);    // Jaune
		protected Color highlightColor = new Color(255, 255, 255, 120); // Blanc semi-transparent pour effets

		@Override
		public int getIconWidth() {
			return width;
		}

		@Override
		public int getIconHeight() {
			return height;
		}
	}

	private class HomeIcon extends BaseIcon {
		@Override
		public void paintIcon(Component c, Graphics g, int x, int y) {
			Graphics2D g2d = (Graphics2D) g.create();
			g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

			// Fond arrondi léger
			RoundRectangle2D.Double bg = new RoundRectangle2D.Double(
					x + 4, y + 4, width - 8, height - 8, 8, 8
			);
			g2d.setColor(new Color(245, 245, 245, 90));
			g2d.fill(bg);

			// Dessiner une maison
			// Toit avec dégradé
			Path2D.Double roof = new Path2D.Double();
			roof.moveTo(x + width/2, y + 5);
			roof.lineTo(x + width - 10, y + height/2 - 5);
			roof.lineTo(x + width - 10, y + height/2);
			roof.lineTo(x + width/2, y + 10);
			roof.lineTo(x + 10, y + height/2);
			roof.lineTo(x + 10, y + height/2 - 5);
			roof.closePath();

			GradientPaint roofGradient = new GradientPaint(
					x + width/2, y + 5, accentColor3,
					x + width/2, y + height/2, new Color(211, 84, 0, 200)
			);
			g2d.setPaint(roofGradient);
			g2d.fill(roof);

			// Contour du toit
			g2d.setColor(new Color(150, 60, 0));
			g2d.setStroke(new BasicStroke(1.0f));
			g2d.draw(roof);

			// Corps de la maison
			Rectangle2D.Double house = new Rectangle2D.Double(
					x + width/4, y + height/2, width/2, height/2 - 5
			);
			GradientPaint houseGradient = new GradientPaint(
					x + width/4, y + height/2, accentColor1,
					x + width/4 + width/2, y + height/2, new Color(52, 152, 219)
			);
			g2d.setPaint(houseGradient);
			g2d.fill(house);
			g2d.setColor(new Color(30, 100, 150));
			g2d.draw(house);

			// Porte
			Rectangle2D.Double door = new Rectangle2D.Double(
					x + width/2 - 5, y + height - 15, 10, 15
			);
			g2d.setColor(new Color(120, 66, 18));
			g2d.fill(door);

			// Poignée de porte
			g2d.setColor(Color.YELLOW);
			g2d.fillOval(x + width/2 + 2, y + height - 10, 2, 2);

			// Fenêtre
			Rectangle2D.Double window = new Rectangle2D.Double(
					x + width/4 + 3, y + height/2 + 5, 10, 10
			);
			g2d.setColor(accentColor5);
			g2d.fill(window);

			// Grille de fenêtre
			g2d.setColor(new Color(30, 100, 150));
			g2d.drawLine(x + width/4 + 8, y + height/2 + 5, x + width/4 + 8, y + height/2 + 15);
			g2d.drawLine(x + width/4 + 3, y + height/2 + 10, x + width/4 + 13, y + height/2 + 10);

			// Cheminée
			Rectangle2D.Double chimney = new Rectangle2D.Double(
					x + width - 15, y + 10, 5, 10
			);
			g2d.setColor(new Color(150, 60, 0));
			g2d.fill(chimney);

			g2d.dispose();
		}
	}

	private class ModelIcon extends BaseIcon {
		@Override
		public void paintIcon(Component c, Graphics g, int x, int y) {
			Graphics2D g2d = (Graphics2D) g.create();
			g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

			// Fond carré arrondi
			RoundRectangle2D.Double bg = new RoundRectangle2D.Double(
					x + 4, y + 4, width - 8, height - 8, 10, 10
			);
			GradientPaint bgGradient = new GradientPaint(
					x, y, new Color(accentColor4.getRed(), accentColor4.getGreen(), accentColor4.getBlue(), 40),
					x, y + height, new Color(accentColor4.getRed(), accentColor4.getGreen(), accentColor4.getBlue(), 10)
			);
			g2d.setPaint(bgGradient);
			g2d.fill(bg);

			g2d.setColor(accentColor4);
			g2d.setStroke(new BasicStroke(1.2f));
			g2d.draw(bg);

			// Éléments de modélisation
			// Cercle
			Ellipse2D.Double circle = new Ellipse2D.Double(
					x + 10, y + 10, 12, 12
			);
			g2d.setColor(accentColor5);
			g2d.fill(circle);
			g2d.setColor(new Color(180, 140, 10));
			g2d.draw(circle);

			// Rectangle
			Rectangle2D.Double rect = new Rectangle2D.Double(
					x + width - 22, y + 10, 12, 12
			);
			g2d.setColor(accentColor1);
			g2d.fill(rect);
			g2d.setColor(new Color(30, 100, 150));
			g2d.draw(rect);

			// Losange
			Path2D.Double diamond = new Path2D.Double();
			diamond.moveTo(x + width/2, y + 10);
			diamond.lineTo(x + width/2 + 7, y + 17);
			diamond.lineTo(x + width/2, y + 24);
			diamond.lineTo(x + width/2 - 7, y + 17);
			diamond.closePath();
			g2d.setColor(accentColor3);
			g2d.fill(diamond);
			g2d.setColor(new Color(150, 60, 0));
			g2d.draw(diamond);

			// Lignes de connexion
			g2d.setStroke(new BasicStroke(1.5f));
			g2d.setColor(new Color(100, 100, 100));

			// Ligne 1 : du cercle au losange
			g2d.drawLine(x + 22, y + 16, x + width/2 - 7, y + 17);

			// Ligne 2 : du losange au rectangle
			g2d.drawLine(x + width/2 + 7, y + 17, x + width - 22, y + 16);

			// Flèches de flux de données
			Path2D.Double arrow1 = new Path2D.Double();
			arrow1.moveTo(x + width/2 - 10, y + 17);
			arrow1.lineTo(x + width/2 - 7, y + 15);
			arrow1.lineTo(x + width/2 - 7, y + 19);
			arrow1.closePath();
			g2d.fill(arrow1);

			Path2D.Double arrow2 = new Path2D.Double();
			arrow2.moveTo(x + width - 25, y + 16);
			arrow2.lineTo(x + width - 22, y + 14);
			arrow2.lineTo(x + width - 22, y + 18);
			arrow2.closePath();
			g2d.fill(arrow2);

			// Graphique en bas
			g2d.setColor(accentColor2);
			g2d.setStroke(new BasicStroke(2.0f));
			Path2D.Double curve = new Path2D.Double();
			curve.moveTo(x + 8, y + height - 12);
			curve.curveTo(
					x + 15, y + height - 25,
					x + 25, y + height - 10,
					x + width - 8, y + height - 18
			);
			g2d.draw(curve);

			// Points de données sur la courbe
			g2d.setColor(accentColor2.darker());
			g2d.fillOval(x + 8, y + height - 14, 4, 4);
			g2d.fillOval(x + 18, y + height - 20, 4, 4);
			g2d.fillOval(x + 28, y + height - 12, 4, 4);
			g2d.fillOval(x + width - 10, y + height - 20, 4, 4);

			g2d.dispose();
		}
	}

	private class ResultatIcon extends BaseIcon {
		@Override
		public void paintIcon(Component c, Graphics g, int x, int y) {
			Graphics2D g2d = (Graphics2D) g.create();
			g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

			// Fond semi-transparent
			RoundRectangle2D.Double bg = new RoundRectangle2D.Double(
					x + 4, y + 4, width - 8, height - 8, 10, 10
			);
			g2d.setColor(new Color(accentColor2.getRed(), accentColor2.getGreen(), accentColor2.getBlue(), 20));
			g2d.fill(bg);

			// Cadre avec léger arrondi
			RoundRectangle2D.Double frame = new RoundRectangle2D.Double(
					x + 5, y + 5, width - 10, height - 10, 4, 4
			);
			g2d.setColor(accentColor1);
			g2d.setStroke(new BasicStroke(1.2f));
			g2d.draw(frame);

			// Axe X avec graduation
			g2d.setColor(new Color(60, 60, 60));
			g2d.drawLine(x + 8, y + height - 8, x + width - 8, y + height - 8);

			// Petites graduations
			int numTicks = 5;
			for (int i = 0; i < numTicks; i++) {
				int xPos = x + 8 + (i * (width - 16) / (numTicks - 1));
				g2d.drawLine(xPos, y + height - 8, xPos, y + height - 6);
			}

			// Axe Y avec graduation
			g2d.drawLine(x + 8, y + 8, x + 8, y + height - 8);

			// Petites graduations Y
			int numTicksY = 4;
			for (int i = 0; i < numTicksY; i++) {
				int yPos = y + height - 8 - (i * (height - 16) / (numTicksY - 1));
				g2d.drawLine(x + 6, yPos, x + 8, yPos);
			}

			// Barres de graphique avec dégradés
			// Barre 1
			Rectangle2D.Double bar1 = new Rectangle2D.Double(
					x + 12, y + height - 25, 8, 17
			);
			GradientPaint gp1 = new GradientPaint(
					x + 12, y, accentColor1,
					x + 20, y, new Color(accentColor1.getRed(), accentColor1.getGreen(), accentColor1.getBlue(), 180)
			);
			g2d.setPaint(gp1);
			g2d.fill(bar1);
			g2d.setColor(accentColor1.darker());
			g2d.draw(bar1);

			// Barre 2
			Rectangle2D.Double bar2 = new Rectangle2D.Double(
					x + 22, y + height - 35, 8, 27
			);
			GradientPaint gp2 = new GradientPaint(
					x + 22, y, accentColor2,
					x + 30, y, new Color(accentColor2.getRed(), accentColor2.getGreen(), accentColor2.getBlue(), 180)
			);
			g2d.setPaint(gp2);
			g2d.fill(bar2);
			g2d.setColor(accentColor2.darker());
			g2d.draw(bar2);

			// Barre 3
			Rectangle2D.Double bar3 = new Rectangle2D.Double(
					x + 32, y + height - 20, 8, 12
			);
			GradientPaint gp3 = new GradientPaint(
					x + 32, y, accentColor5,
					x + 40, y, new Color(accentColor5.getRed(), accentColor5.getGreen(), accentColor5.getBlue(), 180)
			);
			g2d.setPaint(gp3);
			g2d.fill(bar3);
			g2d.setColor(accentColor5.darker());
			g2d.draw(bar3);

			// Barre 4
			Rectangle2D.Double bar4 = new Rectangle2D.Double(
					x + 42, y + height - 28, 8, 20
			);
			GradientPaint gp4 = new GradientPaint(
					x + 42, y, accentColor3,
					x + 50, y, new Color(accentColor3.getRed(), accentColor3.getGreen(), accentColor3.getBlue(), 180)
			);
			g2d.setPaint(gp4);
			g2d.fill(bar4);
			g2d.setColor(accentColor3.darker());
			g2d.draw(bar4);

			// Texte "MAX"
			g2d.setColor(new Color(50, 50, 50));
			g2d.setFont(new Font("SansSerif", Font.BOLD, 9));
			g2d.drawString("MAX", x + 20, y + height - 38);

			g2d.dispose();
		}
	}

	private class MineIcon extends BaseIcon {
		@Override
		public void paintIcon(Component c, Graphics g, int x, int y) {
			Graphics2D g2d = (Graphics2D) g.create();
			g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

			// Fond léger
			RoundRectangle2D.Double bg = new RoundRectangle2D.Double(
					x + 4, y + 4, width - 8, height - 8, 10, 10
			);
			g2d.setColor(new Color(accentColor5.getRed(), accentColor5.getGreen(), accentColor5.getBlue(), 30));
			g2d.fill(bg);

			// Dessiner un casque de mineur avec dégradé
			Ellipse2D.Double helmet = new Ellipse2D.Double(
					x + 10, y + 8, width - 20, height/2 - 4
			);

			GradientPaint helmetGradient = new GradientPaint(
					x + width/2, y + 8, accentColor5,
					x + width/2, y + height/2, new Color(200, 170, 10)
			);
			g2d.setPaint(helmetGradient);
			g2d.fill(helmet);

			// Contour du casque
			g2d.setColor(new Color(150, 120, 10));
			g2d.setStroke(new BasicStroke(1.2f));
			g2d.draw(helmet);

			// Visière du casque
			g2d.setStroke(new BasicStroke(1.5f));
			g2d.setColor(new Color(50, 50, 50));
			g2d.drawLine(x + 12, y + height/2, x + width - 12, y + height/2);

			// Lampe
			Ellipse2D.Double lamp = new Ellipse2D.Double(
					x + width/2 - 4, y + 6, 8, 8
			);

			// Effet de brillance pour la lampe
			RadialGradientPaint lampGradient = new RadialGradientPaint(
					new Point2D.Float(x + width/2, y + 10),
					8.0f,
					new float[] {0.0f, 0.7f, 1.0f},
					new Color[] {
							Color.WHITE,
							new Color(255, 255, 180),
							new Color(255, 200, 50)
					}
			);
			g2d.setPaint(lampGradient);
			g2d.fill(lamp);
			g2d.setColor(new Color(200, 150, 0));
			g2d.draw(lamp);

			// Rayons de la lampe
			g2d.setStroke(new BasicStroke(1.0f));
			g2d.setColor(new Color(255, 220, 0));
			g2d.drawLine(x + width/2, y + 4, x + width/2, y + 2);
			g2d.drawLine(x + width/2 + 4, y + 6, x + width/2 + 6, y + 3);
			g2d.drawLine(x + width/2 - 4, y + 6, x + width/2 - 6, y + 3);

			// Pioche (symbole de mine)
			g2d.setColor(new Color(100, 100, 100));
			g2d.setStroke(new BasicStroke(2.0f));

			// Manche de la pioche
			Path2D.Double handle = new Path2D.Double();
			handle.moveTo(x + 10, y + height - 8);
			handle.lineTo(x + width - 14, y + height/2 + 10);
			g2d.draw(handle);

			// Tête de pioche stylisée
			Path2D.Double pickHead = new Path2D.Double();
			pickHead.moveTo(x + width - 20, y + height/2 + 6);
			pickHead.lineTo(x + width - 14, y + height/2 + 10);
			pickHead.lineTo(x + width - 8, y + height/2 + 14);
			g2d.setColor(accentColor3);
			g2d.setStroke(new BasicStroke(2.5f));
			g2d.draw(pickHead);

			// Petites roches/minerais
			g2d.setColor(new Color(140, 140, 140));
			g2d.fillOval(x + 8, y + height - 14, 6, 6);
			g2d.fillOval(x + 16, y + height - 12, 8, 8);
			g2d.setColor(new Color(100, 100, 100));
			g2d.drawOval(x + 8, y + height - 14, 6, 6);
			g2d.drawOval(x + 16, y + height - 12, 8, 8);

			// Reflet sur un minerai pour effet brillant
			g2d.setColor(new Color(255, 255, 255, 120));
			g2d.fillOval(x + 17, y + height - 11, 3, 2);

			g2d.dispose();
		}
	}

	private class HydrocarbureIcon extends BaseIcon {
		@Override
		public void paintIcon(Component c, Graphics g, int x, int y) {
			Graphics2D g2d = (Graphics2D) g.create();
			g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

			// Fond léger
			RoundRectangle2D.Double bg = new RoundRectangle2D.Double(
					x + 4, y + 4, width - 8, height - 8, 10, 10
			);
			g2d.setColor(new Color(accentColor3.getRed(), accentColor3.getGreen(), accentColor3.getBlue(), 20));
			g2d.fill(bg);

			// Dessiner un puits de pétrole stylisé
			// Structure du puits
			Path2D.Double derrick = new Path2D.Double();
			// Base
			derrick.moveTo(x + 15, y + height - 8);
			derrick.lineTo(x + width - 15, y + height - 8);
			// Pilier gauche
			derrick.moveTo(x + 15, y + height - 8);
			derrick.lineTo(x + width/2 - 4, y + 8);
			// Pilier droit
			derrick.moveTo(x + width - 15, y + height - 8);
			derrick.lineTo(x + width/2 + 4, y + 8);
			// Sommet
			derrick.moveTo(x + width/2 - 4, y + 8);
			derrick.lineTo(x + width/2 + 4, y + 8);
			// Barres horizontales
			derrick.moveTo(x + 18, y + height - 15);
			derrick.lineTo(x + width - 18, y + height - 15);
			derrick.moveTo(x + 21, y + height - 22);
			derrick.lineTo(x + width - 21, y + height - 22);
			derrick.moveTo(x + 24, y + height - 29);
			derrick.lineTo(x + width - 24, y + height - 29);

			// Dessiner la structure en noir
			g2d.setColor(new Color(40, 40, 40));
			g2d.setStroke(new BasicStroke(1.5f));
			g2d.draw(derrick);

			// Goutte de pétrole (plus grande au sommet)
			Path2D.Double drop = new Path2D.Double();
			drop.moveTo(x + width/2, y + 12);
			drop.curveTo(
					x + width/2 - 8, y + 20,
					x + width/2 - 8, y + 30,
					x + width/2, y + 35
			);
			drop.curveTo(
					x + width/2 + 8, y + 30,
					x + width/2 + 8, y + 20,
					x + width/2, y + 12
			);

			// Dégradé pour la goutte de pétrole
			GradientPaint dropGradient = new GradientPaint(
					x + width/2 - 8, y + 12, new Color(30, 30, 30),
					x + width/2 + 8, y + 35, new Color(80, 50, 20)
			);
			g2d.setPaint(dropGradient);
			g2d.fill(drop);
			g2d.setColor(new Color(20, 20, 20));
			g2d.setStroke(new BasicStroke(1.0f));
			g2d.draw(drop);

			// Petite flaque de pétrole au sol
			Ellipse2D.Double puddle = new Ellipse2D.Double(
					x + width/2 - 10, y + height - 12, 20, 7
			);
			GradientPaint puddleGradient = new GradientPaint(
					x + width/2, y + height - 12, new Color(60, 30, 10),
					x + width/2, y + height - 5, new Color(20, 20, 20)
			);
			g2d.setPaint(puddleGradient);
			g2d.fill(puddle);

			// Reflet sur la goutte principale
			g2d.setColor(new Color(255, 255, 255, 80));
			g2d.fillOval(x + width/2 - 3, y + 18, 6, 4);

			// Pompe à pétrole (bras oscillant - tête de cheval)
			Path2D.Double pump = new Path2D.Double();
			pump.moveTo(x + width/2 - 2, y + height - 25);
			pump.lineTo(x + width/2 - 8, y + height - 20);
			pump.lineTo(x + width/2 - 10, y + height - 30);
			pump.lineTo(x + width/2 - 5, y + height - 32);
			g2d.setColor(new Color(80, 80, 80));
			g2d.setStroke(new BasicStroke(2.0f));
			g2d.draw(pump);

			// Petite goutte secondaire
			Path2D.Double smallDrop = new Path2D.Double();
			smallDrop.moveTo(x + width/2 + 10, y + height - 25);
			smallDrop.curveTo(
					x + width/2 + 7, y + height - 22,
					x + width/2 + 7, y + height - 18,
					x + width/2 + 10, y + height - 16
			);
			smallDrop.curveTo(
					x + width/2 + 13, y + height - 18,
					x + width/2 + 13, y + height - 22,
					x + width/2 + 10, y + height - 25
			);

			g2d.setColor(new Color(30, 30, 30));
			g2d.fill(smallDrop);

			g2d.dispose();
		}
	}

	private class EnergieIcon extends BaseIcon {
		@Override
		public void paintIcon(Component c, Graphics g, int x, int y) {
			Graphics2D g2d = (Graphics2D) g.create();
			g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

			// Fond léger avec gradient
			RoundRectangle2D.Double bg = new RoundRectangle2D.Double(
					x + 4, y + 4, width - 8, height - 8, 10, 10
			);
			GradientPaint bgGradient = new GradientPaint(
					x, y, new Color(accentColor4.getRed(), accentColor4.getGreen(), accentColor4.getBlue(), 30),
					x, y + height, new Color(accentColor1.getRed(), accentColor1.getGreen(), accentColor1.getBlue(), 15)
			);
			g2d.setPaint(bgGradient);
			g2d.fill(bg);

			// Cercle symbolisant l'énergie renouvelable/concept circulaire d'énergie
			Ellipse2D.Double circle = new Ellipse2D.Double(
					x + 8, y + 8, width - 16, height - 16
			);

			// Dessiner un cercle avec un dégradé
			GradientPaint circleGradient = new GradientPaint(
					x + 8, y + 8, new Color(accentColor1.getRed(), accentColor1.getGreen(), accentColor1.getBlue(), 50),
					x + width - 8, y + height - 8, new Color(accentColor2.getRed(), accentColor2.getGreen(), accentColor2.getBlue(), 50)
			);
			g2d.setPaint(circleGradient);
			g2d.setStroke(new BasicStroke(1.5f));
			g2d.draw(circle);

			// Flèches circulaires - symbolisant le cycle de l'énergie et la durabilité
			int centerX = x + width/2;
			int centerY = y + height/2;
			int radius = width/2 - 12;

			// Première flèche
			Path2D.Double arrow1 = new Path2D.Double();
			arrow1.moveTo(centerX, centerY - radius);  // Point de départ en haut
			arrow1.quadTo(
					centerX + radius, centerY - radius,
					centerX + radius, centerY
			);

			// Tête de flèche 1
			Path2D.Double arrowHead1 = new Path2D.Double();
			arrowHead1.moveTo(centerX + radius + 2, centerY);
			arrowHead1.lineTo(centerX + radius - 3, centerY - 5);
			arrowHead1.lineTo(centerX + radius - 3, centerY + 5);
			arrowHead1.closePath();

			// Deuxième flèche
			Path2D.Double arrow2 = new Path2D.Double();
			arrow2.moveTo(centerX + radius, centerY);  // Point de départ à droite
			arrow2.quadTo(
					centerX + radius, centerY + radius,
					centerX, centerY + radius
			);

			// Tête de flèche 2
			Path2D.Double arrowHead2 = new Path2D.Double();
			arrowHead2.moveTo(centerX, centerY + radius + 2);
			arrowHead2.lineTo(centerX - 5, centerY + radius - 3);
			arrowHead2.lineTo(centerX + 5, centerY + radius - 3);
			arrowHead2.closePath();

			// Troisième flèche
			Path2D.Double arrow3 = new Path2D.Double();
			arrow3.moveTo(centerX, centerY + radius);  // Point de départ en bas
			arrow3.quadTo(
					centerX - radius, centerY + radius,
					centerX - radius, centerY
			);

			// Tête de flèche 3
			Path2D.Double arrowHead3 = new Path2D.Double();
			arrowHead3.moveTo(centerX - radius - 2, centerY);
			arrowHead3.lineTo(centerX - radius + 3, centerY - 5);
			arrowHead3.lineTo(centerX - radius + 3, centerY + 5);
			arrowHead3.closePath();

			// Dessiner les flèches avec des couleurs différentes
			g2d.setColor(accentColor2);
			g2d.setStroke(new BasicStroke(2.0f));
			g2d.draw(arrow1);
			g2d.fill(arrowHead1);

			g2d.setColor(accentColor3);
			g2d.draw(arrow2);
			g2d.fill(arrowHead2);

			g2d.setColor(accentColor1);
			g2d.draw(arrow3);
			g2d.fill(arrowHead3);

			// Éclair central (symbole d'énergie)
			Path2D.Double bolt = new Path2D.Double();
			bolt.moveTo(centerX + 3, centerY - 8);
			bolt.lineTo(centerX - 6, centerY - 1);
			bolt.lineTo(centerX, centerY);
			bolt.lineTo(centerX - 3, centerY + 8);
			bolt.lineTo(centerX + 6, centerY + 1);
			bolt.lineTo(centerX, centerY);
			bolt.closePath();

			// Dégradé pour l'éclair
			GradientPaint boltGradient = new GradientPaint(
					centerX - 6, centerY - 8, accentColor5,
					centerX + 6, centerY + 8, new Color(250, 200, 0)
			);
			g2d.setPaint(boltGradient);
			g2d.fill(bolt);
			g2d.setColor(new Color(200, 150, 0));
			g2d.setStroke(new BasicStroke(0.8f));
			g2d.draw(bolt);

			// Éclat autour de l'éclair
			Ellipse2D.Double glow = new Ellipse2D.Double(
					centerX - 8, centerY - 8, 16, 16
			);
			g2d.setColor(new Color(255, 255, 200, 50));
			g2d.fill(glow);

			g2d.dispose();
		}
	}
}