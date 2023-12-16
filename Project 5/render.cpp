#pragma warning(disable:6262)
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>

using namespace std;

const int MAX_WORD_LENGTH = 180;

int render(int lineLength, istream& inf, ostream& outf)
{
	if (lineLength < 1)
		return -2;

	char ch;
	char* word = new char[MAX_WORD_LENGTH];
	char* prevWord = new char[MAX_WORD_LENGTH];
	int lineLeft = lineLength;
	int wordLength;
	int prevWordLength;
	bool wordsBefore = false;
	bool inParagraph = false;

	int value = 0; //Default return will be 0 unless a word portion > lineLength

	while (inf.get(ch))
	{
		if (!isspace(ch)) //In this branch, we will make and outf word portions
		{
			if (wordsBefore) //stores previous word in temp (for later tests with punctuation)
			{
				prevWord[0] = '\0';
				strcpy(prevWord, word);
				prevWordLength = strlen(prevWord);
			}

			word[0] = '\0'; //Null terminates string
			inf.putback(ch);
			int i = 0;
			while (inf.get(ch))
			{
				if (ch == '-') //Includes hyphen in word, but stops loop
				{
					word[i] = ch;
					word[i + 1] = '\0';
					break;
				}

				if (isspace(ch)) //Doesn't include whitespace in words
				{
					inf.putback(ch);
					word[i] = '\0';
					break;
				}

				word[i] = ch;
				i++;
			}

			if (word[i] != '\0' && word[i + 1] != '\0') //Accounts for the end of infile
			{
				word[i] = '\0';
			}

			wordLength = strlen(word); //Updates wordLength

			if (wordLength > lineLength) //RETURN 1 BUT WRITE AS MUCH OF THE WORD ON THE LINE AS YOU CAN
			{
				if (wordsBefore)
					outf << endl;

				int charsRemaining = lineLength;

				for (int i = 0; i < wordLength; i++)
				{
					if (charsRemaining == 0)
					{
						outf << endl;
						charsRemaining = lineLength;
						wordsBefore = false;
						inParagraph = true;
					}

					outf << word[i];
					charsRemaining--;

					if (word[i] == '-') 
					{
						// If the word is split at a hyphen, move to the next line
						outf << endl;
						charsRemaining = lineLength;
						wordsBefore = false;
						inParagraph = true;
					}
				}
				value = 1;
				continue;
			}

			//For a word "@P@"
			if (strcmp(word, "@P@") == 0)
			{
				if (inParagraph) //Tests whether we are in a paragraph or not
				{
					outf << endl << endl;
					wordsBefore = false;
					inParagraph = false;
					lineLeft = lineLength;
					continue;
				}
				else //Repeat @P@
				{
					continue;
				}
			}

			if (wordLength <= lineLeft) //Evaluates if word can fit on line (including spaces) 
			{
				if (wordsBefore) //WRITE WHITESPACE BEFORE (CONSIDERING PREVIOUS WORDS PUNCTUATIONS)
				{
					//prevWord stores previous string, checks the pucntu
					if (prevWord[prevWordLength - 1] == '.' || prevWord[prevWordLength - 1] == '?' || prevWord[prevWordLength - 1] == '!' || prevWord[prevWordLength - 1] == ':')
					{
						lineLeft -= 2; //Considers the spaces

						if (wordLength <= lineLeft) //If word can fit with the two spaces
						{
							outf << " " << " " << word;
							lineLeft -= wordLength;
							wordsBefore = true;
							inParagraph = true;
							continue;
						}
						if (wordLength > lineLeft) //If word cannot fit with the spaces
						{
							outf << endl << word;
							lineLeft = lineLength - wordLength;
							wordsBefore = true;
							inParagraph = true;
							continue;
						}
					}
					else if (prevWord[prevWordLength - 1] == '-')
					{
						outf << word;
						lineLeft -= wordLength;;
						wordsBefore = true;
						inParagraph = true;
						continue;
					}
					else //Previous word portion did not end with punctuation or hyphen
					{
						lineLeft--; //Considers the space

						if (wordLength <= lineLeft) //If word can fit with the space
						{
							outf << " " << word;
							lineLeft -= wordLength;
							wordsBefore = true;
							inParagraph = true;
							continue;
						}
						if (wordLength > lineLeft) //If word cannot fit with the space
						{
							outf << endl << word;
							lineLeft = lineLength - wordLength;
							wordsBefore = true;
							inParagraph = true;
							continue;
						}
					}
				}
				else //Word is on a new line, outputs normally
				{
					outf << word;
					lineLeft -= wordLength;
					wordsBefore = true;
					inParagraph = true;
					continue;
				}
			}
			else //wordLength > lineLeft
			{
				outf << endl << word;
				lineLeft = lineLength - wordLength;
				wordsBefore = true;
				inParagraph = true;
				continue;
			}
		}
	}
	//When we reach here, there are no more characters for us to evaulate

	delete[] word;
	delete[] prevWord;

	return value;
}

int main()
{
	ofstream outfile("c:/users/arjen/source/repos/project 5/results.txt");   // outfile is a name of our choosing.
	ifstream infile("c:/users/arjen/source/repos/project 5/data.txt");

	int returnValue = render(20, infile, outfile);

	cout << returnValue << " - Value returned by render\n";
}

