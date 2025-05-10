package src;

import javax.swing.*;
import java.awt.*;

/**
 * Main application class for the MMPE Dashboard
 * Integrates Header, Footer and various page components
 */
public class DashboardApp extends JFrame {

	private Header headerPanel;
	private Footer footerPanel;
	private JPanel contentPanel;
	private CardLayout cardLayout;

	// Page components - each is a dedicated Java class
	private Accueil accueilPage;
	private ResultatsPage resultatsPage;
	private MinesPage minesPage;
	private EnergiePage energiePage;
	private ModelesPage modelesPage;
	private HydrocarburesPage hydrocarburesPage;

	public DashboardApp() {
		initComponents();
	}

	private void initComponents() {
		// Configure the frame
		setTitle("MMPE Dashboard");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(1000, 700);
		setMinimumSize(new Dimension(800, 600));
		setLocationRelativeTo(null);

		// Set main layout
		getContentPane().setLayout(new BorderLayout());

		// Initialize header
		headerPanel = new Header();
		getContentPane().add(headerPanel, BorderLayout.NORTH);

		// Initialize content area with CardLayout for page switching
		cardLayout = new CardLayout();
		contentPanel = new JPanel(cardLayout);
		getContentPane().add(contentPanel, BorderLayout.CENTER);

		// Create pages
		createPages();

		// Initialize footer with navigation
		footerPanel = new Footer();
		footerPanel.setPageChangeListener(new Footer.PageChangeListener() {
			@Override
			public void onPageChanged(String pageName) {
				cardLayout.show(contentPanel, pageName);
			}
		});
		getContentPane().add(footerPanel, BorderLayout.SOUTH);

		// Set default selected page
		footerPanel.setSelectedPage("accueil");
	}

	private void createPages() {
		// Accueil (Home) page
		accueilPage = new Accueil();
		contentPanel.add(accueilPage, "accueil");

		// Résultats Généraux page
		resultatsPage = new ResultatsPage();
		contentPanel.add(resultatsPage, "resultats");

		// Mines page
		minesPage = new MinesPage();
		contentPanel.add(minesPage, "mines");

		// Energie page
		energiePage = new EnergiePage();
		contentPanel.add(energiePage, "energie");

		// Modèles et Simulations page
		modelesPage = new ModelesPage();
		contentPanel.add(modelesPage, "modeles");

		// Hydrocarbures page
		hydrocarburesPage = new HydrocarburesPage();
		contentPanel.add(hydrocarburesPage, "hydrocarbures");
	}

	/**
	 * Application entry point
	 */
	public static void main(String[] args) {
		// Set look and feel to system default
		try {
			UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		} catch (Exception e) {
			e.printStackTrace();
		}

		// Start application on EDT
		SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				DashboardApp app = new DashboardApp();
				app.setVisible(true);
			}
		});
	}
}