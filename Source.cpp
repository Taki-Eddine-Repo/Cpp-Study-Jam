#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
using namespace std;


/// <summary>
/// 
/// </summary>
/// <param name="user"></param>
/// <param name="pass"></param>
/// <returns></returns>
int login(string user, string pass)
{
	string readLine;
	ifstream users("users.txt");
	while (getline(users, readLine, ';'))
	{
		if (readLine[0] == '\n')
		{
			readLine = string(readLine.begin() + 1, readLine.end());
		}
		if (readLine == user)
		{
			getline(users, readLine, ';');
			if (readLine == pass)
			{
				getline(users, readLine, ';');
				if (readLine == "admin")
					return 1; // user found
				else
					return 2; // user is a customer
			}
			else
			{
				return 3; // wrong password
			}
		}
	}
	users.close();
	return 4; // user NOT FOUND. Wrong username or user doesn't exist create one.
}

/// <summary>
/// 
/// </summary>
/// <param name="user"></param>
/// <param name="pass"></param>
/// <returns></returns>

int signup(string user, string pass)
{
	string readLine;
	fstream users("users.txt", fstream::in | fstream::out | fstream::app);
	int counter = 0;
	while (getline(users, readLine, '\n'))
	{
		counter++;
	}
	users.clear();
	users.seekg(0);
	users.seekp(0);
	while (getline(users, readLine, ';'))
	{
		if (readLine == user)
		{
			return 5;
		}
		else
		{
			getline(users, readLine, '\n');
		}
	}
	users.clear();
	users.seekg(0);
	users.seekp(0);

	users << user<< ";" << pass << ";" << "customer;\n";
	users.close();
	return 6;
}

int menu(int& res)
{
	switch (res)
	{
	case 1:
		cout << "1- Update the menu." << endl
			<< "2- View current orders." << endl
			<< "3- View orders history." << endl
			<< "4- Sign out" << endl;
		break;
	case 2:
		cout << "1- Make order." << endl
			<< "2- View menu." << endl
			<< "3- Track my order" << endl
			<< "4- My history" << endl
			<< "5- Sign out" << endl;
		break;
	}
	int choice;
	cin >> choice;
	return choice;
}
void rest_menu()
{
	fstream rest_menu;
	string temp;
	rest_menu.open("menu.txt", fstream::in | fstream::out | fstream::app);
	int counter = 1;
	while (getline(rest_menu, temp, ';'))
	{
		string name = (temp[0] == '\n') ? string(temp.begin() + 1, temp.end()) : temp;
		getline(rest_menu, temp, ';');
		string price = temp;
		getline(rest_menu, temp, ';');
		string quantity = temp;
		cout << counter << "- " << name << " RM" << price << endl;
		counter++;
	}
	rest_menu.close();
}
void add_to_menu(string name, int price, int quantity)
{
	fstream rest_menu("menu.txt", fstream::in | fstream::out | fstream::app);
	rest_menu << endl << name << ";" << price << ";" << quantity;
	rest_menu.close();
}
pair<string**, int> _LoadMenu()
{
	string readLine;
	int counter = 0;
	fstream rest_menu("menu.txt", fstream::in);
	while (getline(rest_menu, readLine, '\n'))
	{
		counter++;
	}
	rest_menu.clear();
	rest_menu.seekg(0);
	rest_menu.seekp(0);
	string** _LoadMenu = new string * [counter];
	for (size_t i = 0; i < counter; i++)
	{
		_LoadMenu[i] = new string[2];
		getline(rest_menu, readLine, ';');
		_LoadMenu[i][0] = (readLine[0] == '\n') ? string(readLine.begin()+1, readLine.end()) : readLine;
		getline(rest_menu, readLine, ';');
		_LoadMenu[i][1] = readLine;
	}
	rest_menu.close();
	return make_pair(_LoadMenu, counter);
}
int remove_item(string name)
{
	string readLine;
	pair<string**, int> _LoadedMenu;
	bool _Found = false;
	fstream rest_menu("menu.txt", fstream::in | fstream::out);
	while (getline(rest_menu, readLine, ';'))
	{
		if (readLine == name)
		{
			_Found == true;
		}
		getline(rest_menu, readLine, ';');
	}
	if (_Found)
		_LoadedMenu = _LoadMenu();
	else return 0;
	for (size_t i = 0; i < _LoadedMenu.second; i++)
	{
		if (_LoadedMenu.first[i][0] == name) {
			continue;
		}
		rest_menu << endl << name << ";" << _LoadedMenu.first[i][1] << ";" << _LoadedMenu.first[i][2];
	}
	rest_menu.close();
	delete[] _LoadedMenu.first;
	return 1;
}
int update_menu(int choice)
{
	switch (choice)
	{
	case 1:
	{
		string _OldName, _NewName;
		bool _Found = false;
		int _pos;
		cin.clear();
		cin.ignore();
		cout << "Enter the old name: "; getline(cin, _OldName);
		if (_OldName != "exit")
			break;
		pair<string**, int> _LoadedMenu = _LoadMenu();
		for (size_t i = 0; i < _LoadedMenu.second; i++)
		{
			if (_LoadedMenu.first[i][0] == _OldName)
			{
				_pos = i;
				_Found == true;
				break;
			}
		}
		while (!_Found)
		{
			cout << "Sorry, the itme does not exist: "; getline(cin, _OldName);
		}
		cin.clear();
		cin.ignore();
		cout << "Enter the new name: "; getline(cin, _NewName);
		_LoadedMenu.first[_pos][0] = _NewName;
		fstream rest_menu("menu.txt", fstream::in | fstream::out);
		string readLine;
		for (size_t i = 0; i < _LoadedMenu.second; i++)
		{
			rest_menu << endl << _NewName << ";" << _LoadedMenu.first[i][1] << ";" << _LoadedMenu.first[i][2];
		}
		delete[] _LoadedMenu.first;
		rest_menu.close();
	}
		break;
	case 2:
		break;
	}
}
int update_rest_menu(int _SmChoice)
{
	switch (_SmChoice)
	{
	case 1:
	{
		
		string name, readLine;
		float price; 
		int quantity;

		cin.clear();
		cin.ignore();
		cout << "Name: "; getline(cin, name);
		bool _Found = false;
		fstream rest_menu("menu.txt", fstream::in | fstream::out);
		while (getline(rest_menu, readLine, ';'))
		{
			readLine = (readLine[0] == '\n') ? string(readLine.begin() + 1, readLine.end()) : readLine;
			if (readLine == name)
			{
				_Found == true;
			}
			getline(rest_menu, readLine, ';');
			getline(rest_menu, readLine, ';');
		}
		while (_Found && name != "exit")
		{
			cout << "This already exists item already exists. Enter exit to exit" << endl;
			cout << "Name: "; getline(cin, name);
		}
		
		rest_menu.close();
		cout << "Price: "; cin >> price;
		cin.clear();
		cin.ignore();
		cout << "Quantity: "; cin >> quantity;
		add_to_menu(name, price, quantity);
	}
		break;
	case 2: 
	{
		string name;
		int _OpResult = remove_item(name);
		if (_OpResult)
			cout << "Successfully removed, please press any key to continue...";
		else cout << "There was an error, please try again...";
		cin.clear();
		cin.ignore();
		cin.get();
	}
		break;
	case 3: 
		cout << "1- Update name" << endl;
		cout << "2- Update price" << endl;
		int choice;
		cin >> choice;
		int results = update_menu(choice);
		break;
	default:
		break;
	}
	return 7;
}
int main()
{
	int choice = 0, status = -1, res = -1;
	while (choice != 5)
	{
		cout << "One stop shop to fill your tummy" << endl;
		cout << "1- Login" << endl
			<< "2- Sign up" << endl
			<< "3- Forgot password" << endl
			<< "4- Contact us" << endl
			<< "5- exit" << endl << "Your choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			string username, password;
			cout << "Enter username: ";
			cin >> username;
			cout << "Password: ";
			cin >> password;
			res = login(username, password);
		}
		break;
		case 2:
		{
			string username, password;
			cout << "Enter username: ";
			cin >> username;
			cout << "Password: ";
			cin >> password;
			res = signup(username, password);
			// perform sign up stuff get error code from signup function and set status accordingly
		}
		break;
		case 3:
		{
			// perform the forgot password stuff.
		}
		break;
		case 4:
		{
			// show contact us
		}
		break;
		case 5:
			break;
		default:
			cout << "Hmm... Are you sure you chose one of the options?";
			break;
		}
		switch (res)
		{
		case 1:
			cout << "Successfully logged in as an admin."
				<< endl << "Please press any key to continue...";
			cin.clear();
			cin.ignore();
			cin.get();
			system("CLS");
			choice = 5;
			break;
		case 2:
			cout << "Successfully logged in."
				<< endl << "Please press any key to start ordering...";
			cin.clear();
			cin.ignore();
			cin.get();
			system("CLS");
			choice = 5;
			break;
		case 3:
			cout << "Hmmmm... It appears that the password you entered is wrong."
				<< endl << "Please try again" << endl;
			continue;
			break;
		case 4:
			cout << "Hmmmm... It appears that the user does not exist."
				<< endl << "Please try again or sign up." << endl;
			continue;
			break;
		case 5:
			cout << "Hmmmm... It appears that the user you're trying to register already exists."
				<< endl << "Please try another username or login." << endl;
			continue;
			break;
		case 6:
			cout << "Welcome to the restaurant!"
				<< endl << "Please press any key to go back to the main menu and login!" << endl;
			cin.clear();
			cin.ignore();
			cin.get();
			system("CLS");
			continue;
			break;
		default:
			break;
		}
		int mChoice = menu(res);
		if (res == 1) // means it's an admin
		{
			switch (mChoice)
			{
			case 1:
			{
				cout << "What do you want to do?"
					<< endl << "1- Add to menu"
					<< endl << "2- Remove from menu" << endl
					<< "3- Update menu";
				int _SmChoice;
				cin >> _SmChoice;
				int rest_menu_res = update_rest_menu(_SmChoice);
				// update the menu
			}

				break;
			case 2:
				// view current orders
				break;
			case 3:
				// view orders history
				break;
			case 4:
				// sign out
				break;
			}
		}
		else if (res == 2) // means its a customer
		{
			cout << "1- Make order." << endl
				<< "2- View menu." << endl
				<< "3- Track my order" << endl
				<< "4- My history" << endl
				<< "5- Sign out" << endl;
			switch (mChoice)
			{
			case 1:
				// make_order()
				break;
			case 2:
				rest_menu();
				break;
			case 3:
				// track_order()
				break;
			case 4:
				// my_history()
				break;
			case 5:
				// sign out
				break;
			default:
				break;
			}
		}
	}
}