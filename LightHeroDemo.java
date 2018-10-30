import javax.swing.*;
import java.awt.*;
import java.util.*;

public class LightHeroDemo extends JFrame implements Runnable
{
	private int[] myvals = new int[7];

	public static void main (String[] args)
	{
		LightHeroDemo myframe = new LightHeroDemo();
		new Thread(myframe).start();
	}

	public void parseLineForVals(String myin)
	{
		try
		{
		String[] splits = myin.split(",");
		for(int i = 0; i < 7; i++)
		{
			myvals[i] = Integer.parseInt(splits[i]);
		}
		}
		catch(Exception ex)
		{

		}	
	}

	public void run()
	{
		myvals[0] = 20;
		myvals[1] = 20;
		myvals[2] = 225;

		Scanner scanner = new Scanner(System.in);
		while(scanner.hasNextLine())
		{
			String myin = scanner.nextLine();
			parseLineForVals(myin);	
			this.repaint();
		}
	}

	public LightHeroDemo()
	{

		this.setLocation(500,200);
		this.setSize(800,800);
		this.setTitle("Light Hero Demo");
		this.setContentPane(new MyPaintCanvas());
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);


		this.setVisible(true);
	}

	private class MyPaintCanvas extends JPanel
	{
		public void paintComponent(Graphics g)
		{

			try
			{
			g.setColor(new Color(myvals[0],myvals[1],myvals[2]));
			g.fillRect(0,0,getWidth()/2,getHeight());
			g.setColor(new Color(myvals[3],myvals[4],myvals[5]));
			g.fillRect(getWidth()/2,0,getWidth()/2, (int) (getHeight()*.7));
			g.setColor(new Color(myvals[6],myvals[6],myvals[6]));
			g.fillRect(getWidth()/2,(int) (getHeight()*.7),getWidth()/2,(int) (getHeight()*.3));

			}
			catch(Exception ex)
			{
				
			}


		}
	}
}
