import javax.swing.*;
import java.awt.*;
import java.util.*;

public class LightHeroDemo extends JFrame implements Runnable
{
	public static void main (String[] args)
	{
		LightHeroDemo myframe = new LightHeroDemo();
		new Thread(myframe).start();
	}

	public void run()
	{
		Scanner scanner = new Scanner(System.in);
		scanner.nextLine();
	}

	public LightHeroDemo()
	{

		this.setLocation(500,200);
		this.setSize(800,800);
		this.setTitle("Light Hero Demo");
		this.setVisible(true);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

	}


}
