using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

public class Day08
{
    public static void Main(string[] args)
    {
        string[] lines = File.ReadLines("08.input").ToArray();

        int width = lines[0].Length;
        int height = lines.Length;
        var visibleTrees = new HashSet<int>();

        // Top -> bottom
        for(int x=0; x<width; ++x)
        {
            int max = 0;
            for(int y=0; y<height; ++y)
            {
                int h = lines[y][x];
                if(y == 0 || y == height-1 || h > max)
                {
                    max = h;
                    visibleTrees.Add(x + y * width);
                }
            }
        }

        // Bottom -> top
        for(int x=0; x<width; ++x)
        {
            int max = 0;
            for(int y=height; y-->0;)
            {
                int h = lines[y][x];
                if(y == 0 || y == height-1 || h > max)
                {
                    max = h;
                    visibleTrees.Add(x + y * width);
                }
            }
        }

        // Left -> right
        for(int y=0; y<height; ++y)
        {
            int max = 0;
            for(int x=0; x<width; ++x)
            {
                int h = lines[y][x];
                if(x == 0 || x == width-1 || h > max)
                {
                    max = h;
                    visibleTrees.Add(x + y * width);
                }
            }
        }

        // Right -> left
        for(int y=0; y<height; ++y)
        {
            int max = 0;
            for(int x=width; x-->0;)
            {
                int h = lines[y][x];
                if(x == 0 || x == width-1 || h > max)
                {
                    max = h;
                    visibleTrees.Add(x + y * width);
                }
            }
        }

        Console.WriteLine(visibleTrees.Count);
    }
}

