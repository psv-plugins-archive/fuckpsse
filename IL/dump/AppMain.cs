using System;

using Sce.PlayStation.Core;
using Sce.PlayStation.Core.Environment;
using Sce.PlayStation.Core.Graphics;
using Sce.PlayStation.Core.Input;

using System.IO;

namespace dump
{
	public class AppMain
	{
		private static GraphicsContext graphics;
		
		public static void Main (string[] args)
		{

			
			Initialize ();

			
			String[] Dirs = Directory.GetDirectories("/Application","*",SearchOption.AllDirectories);
			String[] Files = Directory.GetFiles("/Application","*",SearchOption.AllDirectories);
			
			foreach(String dir in Dirs)
			{
				try{
					Directory.CreateDirectory(dir.Replace("Application","Documents/Application"));
				}
				catch(Exception)
				{
				}
					
			}
			
			foreach(String file in Files)
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
				

			}
			while(true)
			{
				SystemEvents.CheckEvents();
				Update();
				Render();
			}
			
		}

		public static void Initialize ()
		{
			// Set up the graphics system
			graphics = new GraphicsContext ();
		}

		public static void Update ()
		{
			// Query gamepad for current state
			var gamePadData = GamePad.GetData (0);
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
