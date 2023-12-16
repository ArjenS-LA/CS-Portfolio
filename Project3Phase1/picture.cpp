#include "grid.h"
#include <cctype>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

const int HORIZ = 0;
const int VERT = 1;

const int FG = 0;
const int BG = 1;

void plotHorizontalLine(int r, int c, int width, int mode, char ch)
{
    if (mode == FG)
    {
        if (width >= 0)
        {
            for (int i = 0; i <= width; i++)
            {
                setChar(r, c + i, ch);
            }
        }
        else
        {
            for (int i = 0; i >= width; i--)
            {
                setChar(r, c + i, ch);
            }
        }
    }
    else //This runs for background mode
    {
        if (width >= 0)
        {
            for (int i = 0; i <= width; i++)
            {
                if (getChar(r, c + i) == ' ')
                {
                    setChar(r, c + i, ch);
                }
            }
        }
        else
        {
            for (int i = 0; i >= width; i--)
            {
                if (getChar(r, c + i) == ' ')
                {
                    setChar(r, c + i, ch);
                }
            }
        }
    }
}

void plotVerticalLine(int r, int c, int height, int mode, char ch)
{
    if (mode == FG)
    {
        if (height >= 0)
        {
            for (int i = 0; i <= height; i++)
            {
                setChar(r + i, c, ch);
            }
        }
        else
        {
            for (int i = 0; i >= height; i--)
            {
                setChar(r + i, c, ch);
            }
        }
    }
    else //Runs for background mode
    {
        if (height >= 0)
        {
            for (int i = 0; i <= height; i++)
            {
                if (getChar(r + i, c) == ' ')
                {
                    setChar(r + i, c, ch);
                }
            }
        }
        else
        {
            for (int i = 0; i >= height; i--)
            {
                if (getChar(r + i, c) == ' ')
                {
                    setChar(r + i, c, ch);
                }
            }
        }
    }
}

//Used to check if line can be plotted within the grid
bool checkLineWithinBounds(int dir, int r, int c, int distance)
{
    if (distance >= 0)
    {
        if (dir == 0) //dir == HORIZ
        {
            for (int i = 0; i <= distance; i++)
            {
                if ((c + i) > getCols())
                {
                    return false;
                }
            }
        }
        else //dir == VERT
        {
            for (int i = 0; i <= distance; i++)
            {
                if ((r + i) > getRows())
                {
                    return false;
                }
            }
        }
    }
    else //distance < 0
    {
        if (dir == 0)
        {
            for (int i = 0; i >= distance; i--)
            {
                if ((c + i) < 1)
                {
                    return false;
                }
            }
        }
        else //dir == VERT
        {
            for (int i = 0; i >= distance; i--)
            {
                if ((r + i) < 1)
                {
                    return false;
                }
            }
        }
    }
    //Line is within bounds
    return true;
}

//Success with
bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg)
{
    //Checks if parameters fit according to spec
    if (!(dir == HORIZ || dir == VERT))
    {
        return false;
    }

    if (!(fgbg == FG || fgbg == BG))
    {
        return false;
    }

    if (!(isprint(plotChar)))
    {
        return false;
    }

    /*This if/else branch determines whether line is
    vertical or horizontal */
    if (dir == HORIZ)
    {
        if (!checkLineWithinBounds(HORIZ, r, c, distance))
        {
            return false;
        }

        plotHorizontalLine(r, c, distance, fgbg, plotChar);
    }
    else // dir == VERT
    {
        if (!checkLineWithinBounds(VERT, r, c, distance))
        {
            return false;
        }

        plotVerticalLine(r, c, distance, fgbg, plotChar);
    }

    //Function ran successfully, so:
    return true;
}

int performCommands(string commandString, char& plotChar, int& mode, int& badPos)
{
    int currentRow = 1;
    int currentColumn = 1;

    if (!(mode == FG || mode == BG))
    {
        return 2;
    }

    if (!(isprint(plotChar)))
    {
        return 2;
    }

    /*This is the command string interpreter*/
    for (int i = 0; i < commandString.size(); i++)
    {
        switch (commandString.at(i))
        {
            //if (commandString.at(i) == 'h' || commandString.at(i) == 'H')
            case 'h':
            case 'H':
                /*If else branch tests if fits parameters then runs*/
                if (i + 1 < commandString.size() && commandString.at(i + 1) == '-')
                {
                    if (i + 2 < commandString.size() && isdigit(commandString.at(i + 2)))
                    {
                        if (!(i + 3 < commandString.size()) || !isdigit(commandString.at(i + 3))) //For single digit changes
                        {
                            string snippet(1, commandString.at(i + 2));
                            int v = stoi(snippet);
                            v = -v;

                            //NEED FUNCTION THAT CHECKS IF LINE IS IN BOUNDS
                            if (!checkLineWithinBounds(HORIZ, currentRow, currentColumn, v))
                            {
                                badPos = i;
                                return 3;
                            }
                            else
                            {
                                assert(plotLine(currentRow, currentColumn, v, HORIZ, plotChar, mode));
                                currentColumn += v;

                                i += 2; //TELLS SWITCH TO IGNORE WHAT WE HAVE ALREADY DEALT WITH
                                break;
                            }
                        }

                        if ((i + 3 < commandString.size()) && isdigit(commandString.at(i + 3))) //For double digit changes
                        {
                            string snippet = commandString.substr(i + 2, 2);
                            int v = stoi(snippet);
                            v = -v;
                            
                            //NEED FUNCTION THAT CHECKS IF LINE IS IN BOUNDS
                            if (!checkLineWithinBounds(HORIZ, currentRow, currentColumn, v))
                            {
                                badPos = i;
                                return 3;
                            }
                            else
                            {
                                assert(plotLine(currentRow, currentColumn, v, HORIZ, plotChar, mode));
                                currentColumn += v;

                                i += 3; //TELLS SWITCH TO IGNORE WHAT WE HAVE ALREADY DEALT WITH
                                break;
                            }
                        }                   
                    }
                    else
                    {
                        badPos = i + 2; //i + 2 does not match h- command
                        return 1;
                    }
                }
                else if (i + 1 < commandString.size() && isdigit(commandString.at(i + 1)))
                {
                    if (!(i + 2 < commandString.size()) || !isdigit(commandString.at(i + 2))) //For single digit changes
                    {
                        string snippet = commandString.substr(i + 1, 1);
                        int v = stoi(snippet);

                        //NEED FUNCTION THAT CHECKS IF LINE IS IN BOUNDS
                        if (!checkLineWithinBounds(HORIZ, currentRow, currentColumn, v))
                        {
                            badPos = i;
                            return 3;
                        }
                        else
                        {
                            assert(plotLine(currentRow, currentColumn, v, HORIZ, plotChar, mode));
                            currentColumn += v;

                            i += 1; //TELLS SWITCH TO IGNORE WHAT WE HAVE ALREADY DEALT WITH
                            break;
                        }
                    }

                    if ((i + 2 < commandString.size()) && isdigit(commandString.at(i + 2))) //For double digit changes
                    {
                        string snippet = commandString.substr(i + 1, 2);
                        int v = stoi(snippet);
                        //NEED FUNCTION THAT CHECKS IF LINE IS IN BOUNDS
                        if (!checkLineWithinBounds(HORIZ, currentRow, currentColumn, v))
                        {
                            badPos = i;
                            return 3;
                        }
                        else
                        {
                            assert(plotLine(currentRow, currentColumn, v, HORIZ, plotChar, mode));
                            currentColumn += v;

                            i += 2; //TELLS SWITCH TO IGNORE WHAT WE HAVE ALREADY DEALT WITH
                            break;
                        }
                    }
                }
                else //Shows i + 1 index does not match 'h' command
                {
                    badPos = i + 1;
                    return 1;
                }
                break; 
            case 'v':
            case 'V':
                /*If else branch tests if fits parameters then runs*/
                if (i + 1 < commandString.size() && commandString.at(i + 1) == '-')
                {
                    if (i + 2 < commandString.size() && isdigit(commandString.at(i + 2)))
                    {
                        if (!(i + 3 < commandString.size()) || !isdigit(commandString.at(i + 3))) //For single digit changes
                        {
                            string snippet(1, commandString.at(i + 2));
                            int v = stoi(snippet);
                            v = -v;

                            //NEED FUNCTION THAT CHECKS IF LINE IS IN BOUNDS
                            if (!checkLineWithinBounds(VERT, currentRow, currentColumn, v))
                            {
                                badPos = i;
                                return 3;
                            }
                            else
                            {
                                assert(plotLine(currentRow, currentColumn, v, VERT, plotChar, mode));
                                currentRow += v;

                                i += 2; //TELLS SWITCH TO IGNORE WHAT WE HAVE ALREADY DEALT WITH
                                break;
                            }
                        }

                        if ((i + 3 < commandString.size()) && isdigit(commandString.at(i + 3))) //For double digit changes
                        {
                            string snippet = commandString.substr(i + 2, 2);
                            int v = stoi(snippet);
                            v = -v;

                            //NEED FUNCTION THAT CHECKS IF LINE IS IN BOUNDS
                            if (!checkLineWithinBounds(VERT, currentRow, currentColumn, v))
                            {
                                badPos = i;
                                return 3;
                            }
                            else
                            {
                                assert(plotLine(currentRow, currentColumn, v, VERT, plotChar, mode));
                                currentRow += v;

                                i += 3; //TELLS SWITCH TO IGNORE WHAT WE HAVE ALREADY DEALT WITH
                                break;
                            }
                        }
                    }
                    else
                    {
                        badPos = i + 2; //i + 2 does not match h- command
                        return 1;
                    }
                }
                else if (i + 1 < commandString.size() && isdigit(commandString.at(i + 1)))
                {
                    if (!(i + 2 < commandString.size()) || !isdigit(commandString.at(i + 2))) //For single digit changes
                    {
                        string snippet = commandString.substr(i + 1, 1);
                        int v = stoi(snippet);

                        //NEED FUNCTION THAT CHECKS IF LINE IS IN BOUNDS
                        if (!checkLineWithinBounds(VERT, currentRow, currentColumn, v))
                        {
                            badPos = i;
                            return 3;
                        }
                        else
                        {
                            assert(plotLine(currentRow, currentColumn, v, VERT, plotChar, mode));
                            currentRow += v;

                            i += 1; //TELLS SWITCH TO IGNORE WHAT WE HAVE ALREADY DEALT WITH
                            break;
                        }
                    }

                    if ((i + 2 < commandString.size()) && isdigit(commandString.at(i + 2))) //For double digit changes
                    {
                        string snippet = commandString.substr(i + 1, 2);
                        int v = stoi(snippet);

                        //NEED FUNCTION THAT CHECKS IF LINE IS IN BOUNDS
                        if (!checkLineWithinBounds(VERT, currentRow, currentColumn, v))
                        {
                            badPos = i;
                            return 3;
                        }
                        else
                        {
                            assert(plotLine(currentRow, currentColumn, v, VERT, plotChar, mode));
                            currentRow += v;

                            i += 2; //TELLS SWITCH TO IGNORE WHAT WE HAVE ALREADY DEALT WITH
                            break;
                        }
                    }
                }
                else //Shows i + 1 index does not match 'h' command
                {
                    badPos = i + 1;
                    return 1;
                }
                break;

            case 'b':
            case 'B':
                if (i + 1 < commandString.size() && isprint(commandString.at(i + 1)))
                {
                    mode = BG;
                    plotChar = commandString.at(i + 1);
                    i++;

                    break; //Character isprint == true, program successful
                }
                else
                {
                    badPos = i + 1;
                    return 1;
                }

            case 'f':
            case 'F':
                if (i + 1 < commandString.size() && isprint(commandString.at(i + 1)))
                {
                    mode = FG;
                    plotChar = commandString.at(i + 1);
                    i++;

                    break; //Character isprint == true, program successful
                }
                else
                {
                    badPos = i + 1;
                    return 1;
                }

            case 'c':
            case 'C':
                currentRow = 1;
                currentColumn = 1;

                clearGrid();
                break;

            default:
                badPos = i;
                return 1;
        }
    }
    //End of Command String interpreter

    //Command String interpreter ran successfully
    return 0;
}

int main()
{
    setSize(30, 30);
    char currentChar = '%';
    int currentMode = FG;
    int position;

    assert(plotLine(1, 1, 1, 5, '*', FG) == false);
    assert(plotLine(1, 1, 1, HORIZ, '\a', FG) == false);
    assert(plotLine(1, 1, 1, HORIZ, '*', 6) == false);
    assert(plotLine(1, 1, 30, HORIZ, '*', FG) == false);
    assert(plotLine(1, 1, -1, HORIZ, '*', FG) == false);
    assert(plotLine(1, 1, 30, VERT, '*', FG) == false);
    assert(plotLine(1, 1, -1, VERT, '*', FG) == false);
    
    assert(performCommands("h10v10B^H-10V-10", currentChar, currentMode, position) == 0);
    draw();
    assert(performCommands("CH10F@h-5", currentChar, currentMode, position) == 0);
    draw();

    char badChar = '\t';
    int badMode = 5;
    assert(performCommands("h1", badChar, currentMode, position) == 2);
    assert(performCommands("h1", currentChar, badMode, position) == 2);
    
    assert(performCommands("m", currentChar, currentMode, position) == 1 && position == 0);
    assert(performCommands("b", currentChar, currentMode, position) == 1 && position == 1);
    assert(performCommands("b\t", currentChar, currentMode, position) == 1 && position == 1);
    assert(performCommands("f", currentChar, currentMode, position) == 1 && position == 1);
    assert(performCommands("f\t", currentChar, currentMode, position) == 1 && position == 1);
    assert(performCommands("h-", currentChar, currentMode, position) == 1 && position == 2);
    assert(performCommands("h", currentChar, currentMode, position) == 1 && position == 1);
    assert(performCommands("v-", currentChar, currentMode, position) == 1 && position == 2);
    assert(performCommands("v", currentChar, currentMode, position) == 1 && position == 1);
    assert(performCommands("v10Q", currentChar, currentMode, position) == 1 && position == 3);

    assert(performCommands("h-1", currentChar, currentMode, position) == 3 && position == 0);
    assert(performCommands("h-10", currentChar, currentMode, position) == 3 && position == 0);
    assert(performCommands("h29h1", currentChar, currentMode, position) == 3 && position == 3);
    assert(performCommands("h30", currentChar, currentMode, position) == 3 && position == 0);
    assert(performCommands("v-1", currentChar, currentMode, position) == 3 && position == 0);
    assert(performCommands("v-10", currentChar, currentMode, position) == 3 && position == 0);
    assert(performCommands("v29v1", currentChar, currentMode, position) == 3 && position == 3);
    assert(performCommands("v30", currentChar, currentMode, position) == 3 && position == 0);

    assert(performCommands("h10v10B^H-10V-10", currentChar, currentMode, position) == 0);
    assert(performCommands("h10v10B^H-10V-10", currentChar, currentMode, position) == 0);
    assert(performCommands("h10v10B^H-10V-10", currentChar, currentMode, position) == 0);
    assert(performCommands("h10v10B^H-10V-10", currentChar, currentMode, position) == 0);
    assert(performCommands("h10v10B^H-10V-10", currentChar, currentMode, position) == 0);
    assert(performCommands("h10v10B^H-10V-10", currentChar, currentMode, position) == 0);
    assert(performCommands("h10v10B^H-10V-10", currentChar, currentMode, position) == 0);
    assert(performCommands("h10v10B^H-10V-10", currentChar, currentMode, position) == 0);

    cout << "All tests succeeded\n";
}