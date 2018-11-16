import javax.swing.*;
import java.awt.*;
import java.util.*;
import java.io.*;

public class LightHeroDemo extends JFrame implements Runnable
{
	private int[] myvals = new int[7];


	public static void main (String[] args)
	{
		LightHeroDemo myframe = new LightHeroDemo();
		new Thread(myframe).start();
		boolean odd = false;

		while(true)
		{

			myframe.repaint();
			try
			{
			Thread.sleep(10);
			}
			catch (Exception ex)
			{

			}

			if(odd)
				myframe.setSize(800,801);
			else
				myframe.setSize(800,800);

			odd = !odd;

		}

	}
		int max = 0;


	public void run()
	{

		int addr = 0;
		int value = 0;

		myvals[0] = 0;
		myvals[1] = 0;
		myvals[2] = 0;
		myvals[3] = 0;
		myvals[4] = 0;
		myvals[5] = 0;
		myvals[6] = 0;


		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		while(true)
		{
			try
			{
			addr = reader.read();
			value = reader.read();

			}
			catch(IOException ex)
			{

			}
			if(addr < 0 || addr > 6 || value < 0 || value > 255)
				continue;

			myvals[addr] = value;
			max = value>max?value:max;
			// System.out.printf("addr %d = %d\n",addr,value);
		}
	}

	public LightHeroDemo()
	{

		this.setLocation(500,200);
		this.setSize(800,800);
		this.setTitle("Light Hero Demo");
		this.setContentPane(new MyPaintCanvas());
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setResizable(false);


		this.setVisible(true);
	}

	private class MyPaintCanvas extends JPanel
	{
		public void paintComponent(Graphics g)
		{
			super.paintComponent(g);
			try
			{
			g.setColor(new Color((float) (myvals[0]+0.0)/max,(float) (myvals[1]+0.0)/max,(float) (myvals[2]+0.0)/max));
			g.fillRect(0,0,getWidth()/2,getHeight());
			g.setColor(new Color((float) (myvals[3]+0.0)/max,(float) (myvals[4]+0.0)/max,(float) (myvals[5]+0.0)/max));
			g.fillRect(getWidth()/2,0,getWidth()/2, getHeight());

			Color c = new Color(1.0f,1.0f,1.0f,(float) (myvals[6]+0.0)/max);

			g.setColor(c);

			int count = 9;

			int mywide = getWidth() / (count * 2);
			for(int i = 1; i < count; i+=2)
			{
				g.fillRect( getWidth()/2 + i * mywide,0,mywide,getHeight());
			
			}

			}
			catch(Exception ex)
			{
				
			}


		}
	}
}
