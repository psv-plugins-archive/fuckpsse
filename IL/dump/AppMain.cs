using System;

using Sce.PlayStation.Core;
using Sce.PlayStation.Core.Environment;
using Sce.PlayStation.Core.Graphics;
using System.IO;

namespace dump
{
	public class AppMain
	{	
		public static void Copy(string inputFilePath, string outputFilePath)
	    {
			SystemEvents.CheckEvents();
			graphics.SetClearColor(1.0f, 0.0f, 0.0f, 0.0f);
			graphics.Clear();
			graphics.SwapBuffers();
	        FileStream fileStream = File.Open(@outputFilePath,FileMode.CreateNew,FileAccess.Write);
            FileStream fs = File.Open(@inputFilePath,FileMode.Open,FileAccess.Read);
           long i = 0;
           while(i < fs.Length) {
                int toRead = (int)fs.Length - (int)i;
                if(toRead > 1*(1000 * 1000))
                    toRead = 1*(1000 * 1000);
                byte[] buf = new byte[toRead];
                i += fs.Read(buf,0,toRead );
                fileStream.Write(buf,0,toRead );
           }
			fs.Close();
			fileStream.Close();
			
	     }
		
		static void SaveMemoryCopy(string sDir)
		{
			SystemEvents.CheckEvents();
			graphics.SetClearColor(1.0f, 0.0f, 0.0f, 0.0f);
			graphics.Clear();
			graphics.SwapBuffers();
	        foreach (string d in Directory.GetDirectories(sDir))
	        {
				if(!Directory.Exists(d.Replace("Application","Temp")))
				{
					Console.WriteLine("Creating: "+d.Replace("Application","Temp"));
					Directory.CreateDirectory(d.Replace("Application","Temp"));
				}
	            foreach (string f in Directory.GetFiles(d))
	            {
					Console.WriteLine("Creating: "+f.Replace("Application","Temp"));
					Copy(f,f.Replace("Application","Temp"));
	            }
	            SaveMemoryCopy(d);
	        }
		}
		
		private static GraphicsContext graphics;
		
		public static void Main (string[] args)
		{

			
			Initialize ();
			
			FileStream ff = File.OpenRead("/Application/App.exe");
		
			foreach(string f in Directory.GetFiles("/Application"))
			{
				SystemEvents.CheckEvents();
				graphics.SetClearColor(1.0f, 0.0f, 0.0f, 0.0f);
				graphics.Clear();
				graphics.SwapBuffers();
				Console.WriteLine("Copying: "+f+ " To: "+f.Replace("Application","Temp"));
				Copy(f,f.Replace("Application","Temp"));
			}
			
			SaveMemoryCopy("/Application");
			
			
			/*
			foreach(String dir in Directory.GetDirectories("/Application","*",SearchOption.AllDirectories))
			{
				SystemEvents.CheckEvents();
				Update();
				
				// Clear the screen
				graphics.SetClearColor (1.0f, 0.0f, 0.0f, 0.0f);
				graphics.Clear ();
	
				// Present the screen
				graphics.SwapBuffers ();
				
				try{
					Directory.CreateDirectory(dir.Replace("Application","Documents/Application"));
				}
				finally
				{
				}
					
			}*/
			
			
			
			/*
			foreach(String file in Directory.GetFiles("/Application","*",SearchOption.AllDirectories))
			{
				SystemEvents.CheckEvents();
				Update();
				
				// Clear the screen
				graphics.SetClearColor (1.0f, 0.0f, 0.0f, 0.0f);
				graphics.Clear ();
	
				// Present the screen
				graphics.SwapBuffers ();
				Byte[] ByteArray = File.ReadAllBytes(file);
				File.WriteAllBytes(file.Replace("Application","Documents/Application"),ByteArray);
				

			}*/
			while(true)
			{
				SystemEvents.CheckEvents();
				Render();
			}
			
		}

		public static void Initialize ()
		{
			// Set up the graphics system
			graphics = new GraphicsContext ();
		}
		
		public static void Render ()
		{
			// Clear the screen
			graphics.SetClearColor (0.0f, 1.0f, 0.0f, 0.0f);
			graphics.Clear ();

			// Present the screen
			graphics.SwapBuffers ();
		}
	}
}
