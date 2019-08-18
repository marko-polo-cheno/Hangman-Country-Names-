#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

using namespace std;

const string allCountries = "Afghanistan Albania Algeria Andorra Angola Anguilla Antigua-Barbuda Argentina Armenia Australia Austria Azerbaijan Bahamas Bahrain Bangladesh Barbados Belarus Belgium Belize Benin Bermuda Bhutan Bolivia Bosnia Herzegovina Botswana Brazil Brunei-Darussalam Bulgaria Burkina-Faso Burundi Cambodia Cameroon Canada Cape-Verde Cayman-Islands Central-African-Republic Chad Chile China Hong-Kong Macau Colombia Comoros Congo Costa-Rica Croatia Cuba Cyprus Czech-Republic Denmark Djibouti Dominica Dominican-Republic Ecuador Egypt El-Salvador Guinea Eritrea Estonia Eswatini Ethiopia Fiji Finland France French Guiana Gabon Gambia Germany Ghana Great Britain Greece Grenada Guadeloupe Guatemala Guinea Guinea-Bissau Guyana Haiti Honduras Hungary Iceland India Indonesia Iran Iraq Israel Italy Ivory Coast Jamaica Japan Jordan Kazakhstan Kenya North-Korea South-Korea Kosovo Kuwait Kyrgyzstan Laos Latvia Lebanon Lesotho Liberia Libya Liechtenstein Lithuania Luxembourg Madagascar Malawi Malaysia Maldives Mali Malta Martinique Mauritania Mauritius Mayotte Mexico Monaco Mongolia Montenegro Montserrat Morocco Mozambique Myanmar Namibia Nepal New-Zealand Nicaragua Niger Nigeria Macedonia Norway Oman Pacific-Islands Pakistan Panama Papua-New-Guinea Paraguay Peru Philippines Poland Portugal Puerto-Rico Qatar Romania Russia Rwanda Saint-Kitts-and-Nevis Saint-Lucia Saint-Vincent-and-the-Grenadines Samoa Sao-Tome-and-Principe Saudi-Arabia Senegal Serbia Seychelles Sierra-Leone Singapore Slovakia Slovenia Solomon-Islands Somalia South-Africa South-Sudan Spain Sri-Lanka Sudan Suriname Sweden Switzerland Syria Tajikistan Tanzania Thailand Netherlands Timor-Leste Togo Trinidad Tobago Tunisia Turkey Turkmenistan Turks-and-Caicos-Islands Uganda Ukraine United-Arab-Emirates United-States-of-America Uruguay Uzbekistan Venezuela Vietnam Virgin-Islands Yemen Zambia Zimbabwe";

const int MAX_TRIES=6;

int letterFill (char, string, string&);

//Why cant c++ just have its own 'split' 
const vector<string> split_in_C(const string& s, const char& c)
{
	string buff{""};
	vector<string> v;
	
	for(auto n:s)
	{
		if(n != c) buff+=n; 
    else if(n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if(buff != "") v.push_back(buff);
	
	return v;
}

int main ()
{
	char letter;
	int num_of_wrong_guesses=0;
	string word;

  //Turn huge string of country names into a string arraylist
	std::vector<std::string> wordsList;
	vector<string> v{split_in_C(allCountries, ' ')};
	for(auto n:v) wordsList.push_back(n);;

	//choose and copy a word from array of words randomly
	srand(time(NULL));
	int n=rand() % wordsList.size();
	word=wordsList[n];
    
	// Initialize the secret word with the * character.
	string unknown(word.length(),'*');

	// welcome the user
	cout << "\n\nWelcome to country themed hangman...\n\nGuess a country's name!\n\nEach letter is represented by a star,\nand remember that countries can have uppercase letters.\n\nType one letter in each turn.\n\nYou have " << MAX_TRIES << " tries to try and guess the word.\n\nMark Chen made this boring game. \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
  
  //Rids of 'spaces' eg. United_States_of_America
  letterFill('-', word, unknown);


	// Play until lives run out
	while (num_of_wrong_guesses < MAX_TRIES)
	{
		cout << "\n\n" << unknown;
		cout << "\n\nGuess a letter: ";
		cin >> letter;
		
    //Update game
		if (letterFill(letter, word, unknown)==0)
		{
			cout << endl << "Nah man... that letter doesn't belong!" << endl;
			num_of_wrong_guesses++;
		}
		else
		{
			cout << endl << "Nice :)" << endl;
		}
		
		// Check if user guessed the word.
		if (word!=unknown)
		{
			// Tell user how many guesses has left.
		  cout << "You have " << MAX_TRIES - num_of_wrong_guesses << " lives left." << endl;
		}
    else 
    {
      cout << word << endl;
			cout << "Yay! You know ur stuff :O";
			break;
    }
	}

	if(num_of_wrong_guesses == MAX_TRIES)
	{
		cout << "\nSorry, u is now dead..." << endl;
		cout << "The country was : " << word << endl;
	}

	cin.ignore();
	cin.get();
	return 0;
}

/* Takes guess and updates the covered secret word.*/
int letterFill (char guess, string secretword, string &wordSolved)
{
	int matches=0;
	for (int i = 0; i< secretword.length(); i++)
	{
		// Did we already match this letter in a previous guess?
		if (guess == wordSolved[i])
			return 0;
		// Is the guess in the secret word?
		if (guess == secretword[i])
		{
			wordSolved[i] = guess;
			matches++;
		}
	}
	return matches;
}