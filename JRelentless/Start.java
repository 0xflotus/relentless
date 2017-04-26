import java.awt.Dimension;
import java.awt.Insets;
import java.awt.Point;
import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.net.URL;
import java.net.URLConnection;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.Statement;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.ScrollPaneConstants;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;

public class Start extends JFrame {

	private JTextField tfLink, tfSelector;
	private JTextArea txtArea;
	private Entry ae = null;

	public Start() {
		initComponents();
		this.setSize(600, 450);
		this.setResizable(false);
		this.setLocationRelativeTo(null);
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		this.setLayout(null);
		this.setTitle("JRelentless v0.1");
		this.setVisible(true);
	}

	private void initComponents() {
		tfLink = new JTextField();
		tfLink.setLocation(new Point(10, 10));
		tfLink.setSize(new Dimension(430, 30));
		this.add(tfLink);

		JButton btnClick = new JButton("Scrap");
		btnClick.setLocation(445, 10);
		btnClick.setSize(120, 30);
		btnClick.setMargin(new Insets(0, 0, 0, 0));
		btnClick.addActionListener(ae -> scrap());
		this.add(btnClick);

		JLabel lblSelector = new JLabel("optionaler Selector");
		lblSelector.setBounds(10, 50, 130, 25);
		this.add(lblSelector);

		tfSelector = new JTextField();
		tfSelector.setBounds(140, 50, 300, 25);
		this.add(tfSelector);

		txtArea = new JTextArea();
		JScrollPane scrollPane = new JScrollPane(txtArea);
		scrollPane.setBounds(10, 90, 430, 300);
		scrollPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
		this.add(scrollPane);

		JButton btnDB = new JButton("Add to DB");
		btnDB.setBounds(450, 90, 120, 30);
		btnDB.setMargin(new Insets(0, 0, 0, 0));
		btnDB.addActionListener(ae -> addToDatabase());
		this.add(btnDB);
	}

	private void addToDatabase() {
		if (ae == null) {
			JOptionPane.showMessageDialog(this, "Keine Daten zum Hinzufuegen vorhanden.");
		} else {
			Connection c = null;
			Statement stmt = null;
			try {
				Class.forName("org.sqlite.JDBC");
				c = DriverManager.getConnection("jdbc:sqlite:relentless.sqlite");

				stmt = c.createStatement();
				String sql = "INSERT INTO entries (title,price,link,timestamp) " + "VALUES ('" + ae.getTitle() + "', "
						+ ae.getPrice() + ", 'http://example.org', 0 );";
				stmt.executeUpdate(sql);
				stmt.close();
				c.close();
			} catch (Exception ex) {
				JOptionPane.showMessageDialog(this, ex.getMessage());
			}
			System.out.println("Erfolgreich hinzugefügt.");
		}
	}

	private void scrap() {
		if (tfLink.getText().isEmpty()) {
			JOptionPane.showMessageDialog(this, "Es wurde kein Link angegeben.");
		} else {
			try {
				URL url = new URL(tfLink.getText());
				txtArea.append("Verbindung aufbauen: " + tfLink.getText() + "...\n");
				URLConnection urlC = url.openConnection();
				InputStream is = url.openStream();
				txtArea.append("Kopiert...  " + urlC.getContentType() + "\n");
				FileOutputStream fos = new FileOutputStream("localcopy");
				int oneChar, count = 0;
				while ((oneChar = is.read()) != -1) {
					fos.write(oneChar);
					count++;
				}
				is.close();
				fos.close();
				txtArea.append(count + " byte(s) kopiert\n");

				Document doc = Jsoup.parse(new File("localcopy"), "UTF-8");
				Element price = doc
						.select(tfSelector.getText().isEmpty() ? "#priceblock_ourprice" : "#" + tfSelector.getText())
						.first();
				Element title = doc.select("#productTitle").first();
				ae = new Entry(Float.parseFloat(price.text().substring(4).replace(',', '.')), title.text());
				txtArea.append("\n\n" + ae.toString() + "\n");
			} catch (Exception ex) {
				JOptionPane.showMessageDialog(this, ex.getMessage());
			}
			try {
				new File("localcopy").delete();
			} catch (SecurityException ex) {
				JOptionPane.showMessageDialog(this, ex.getMessage());
			}
		}
	}

	public static void main(String[] args) {
		new Start();
	}

}
