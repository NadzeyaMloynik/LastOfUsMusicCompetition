#include"Header.h"

vector<info> vectInf;
vector<infCont> vectCont;
vector<ApplyCont> vectApply;

//MUSIC
void Klavishy(int num) {
	int x = 28, y = 12;
	for (int i = 1; i <= 6; i++) {
		x = 28;
		for (int j = 1; j <= 7; j++) {
			if (num == j && num % 2 != 0) {
				GoToXY(x++, y);
				GoToXY(x, y);
				BackLightRed(); cout << "        ";
				x += 8;
			}
			else if (num == j && num % 2 == 0) {
				GoToXY(x++, y);
				GoToXY(x, y);
				BackLYellow(); cout << "        ";
				x += 8;
			}
			else x += 9;
		}
		GoToXY(x, y++);
		White();
	}
	Sleep(60);
}
void PlayMusic() {
	AudioDevicePtr device = OpenDevice();
	OutputStreamPtr ndo = OpenSound(device, "Musik/do.wav", false);
	OutputStreamPtr nre = OpenSound(device, "Musik/re.wav", false);
	OutputStreamPtr nmi = OpenSound(device, "Musik/mi.wav", false);
	OutputStreamPtr nfa = OpenSound(device, "Musik/fa.wav", false);
	OutputStreamPtr nsol = OpenSound(device, "Musik/sol.wav", false);
	OutputStreamPtr nlya = OpenSound(device, "Musik/lya.wav", false);
	OutputStreamPtr nsi = OpenSound(device, "Musik/si.wav", false);
	int rool;
	bool p = true;
	string nota = "";
	bool isGO = 1;
	do {

		//Klavishy(0);

		int x = 28, y = 7;
		GoToXY(x + 5, y - 5);
		Grey();
		cout << "Перед тем как выйти из приложения сыграй что-нибудь ";
		LightRed();
		GoToXY(x + 57, y - 5); cout << "<3";
		GoToXY(x, y++);
		White();
		cout << "    ¶1       ¶2       ¶3       ¶4       ¶5       ¶6       ¶7    ";
		y++;
		GoToXY(x, y++);
		cout << "________________________________________________________________";
		GoToXY(x - 2, y++);
		cout << "==|   до   |   ре   |   ми   |   фа   |  соль  |   ля   |   си   |==";
		GoToXY(x - 1, y++);
		cout << "\\================================================================/";
		for (int i = 1; i <= 6; i++) {
			x = 28;
			for (int j = 1; j <= 7; j++) {
				if (j % 2 != 0) {
					GoToXY(x++, y);
					White(); cout << "|";
					GoToXY(x, y);
					BackWhite(); cout << "         ";
					x += 8;
				}
				else {
					White();
					GoToXY(x++, y);
					cout << "|";
					GoToXY(x, y);
					cout << "         ";
					x += 8;
				}
			}
			GoToXY(x, y++);
			White(); cout << "|" << endl;
		}
		x = 28;
		GoToXY(x - 1, y++);
		cout << "/=================================================================\\";
		GoToXY(x - 1, y++);
		cout << "|_________________________________________________________________|";
		y += 7;
		GoToXY(38, y);
		Grey();
		cout << "  (Для выхода из приложения нажмите ESC) " << endl;

		do {
			if (_kbhit()) {
				rool = _getch();
				switch (rool)
				{
				case ONE:
				{ Klavishy(1); p = false; ndo->play();
				break; }
				case TWO:
				{ Klavishy(2); p = false; nre->play();
				break; }
				case TREE:
				{ Klavishy(3); p = false; nmi->play();
				break; }
				case FOUR:
				{ Klavishy(4); p = false; nfa->play();
				break; }
				case FIVE:
				{ Klavishy(5); p = false; nsol->play();
				break; }
				case SIX:
				{ Klavishy(6); p = false; nlya->play();
				break; }
				case SEVEN:
				{ Klavishy(7); p = false; nsi->play();
				break; }
				case ESC: {isGO = 0; p = false;
					break; }
				}
			}
		} while (p);
		p = true;
	} while (isGO);

}
/////////////////////////////////////////////////

string RandString() {
	string s;
	int a;
	srand(time(0));

	for (int i = 0; i < rand() % 100; i++) {
		a = 33 + rand() % 94;
		s += a;
	}
	return s;
}


//READ INFORMATION
void ReadAppluCont() {
	fstream apply;
	ApplyCont cont;
	apply.open("statement.txt", fstream::in);
	while (apply >> cont.year) {
		int num = apply.tellp();
		apply.seekp(num + 2);
		getline(apply, cont.name);
		getline(apply, cont.country);
		getline(apply, cont.musicInst);
		vectApply.push_back(cont);
	}
	apply.close();
}
void readInf() {
	fstream inf;
	info info;
	inf.open("inf.txt", fstream::in);
	while (inf >> info.login) {
		int num = inf.tellp();
		inf.seekp(num + 2);
		getline(inf, info.password);
		inf >> info.role;
		inf >> info.isActive;
		inf >> info.keyWord;
		vectInf.push_back(info);
	}
	inf.close();
}
void readContest() {
	fstream cont;
	infCont contest;
	cont.open("contest.txt", fstream::in);
	while (cont >> contest.year) {
		int num = cont.tellp();
		cont.seekp(num + 2);
		getline(cont, contest.name);
		getline(cont, contest.country);
		getline(cont, contest.musicInst);
		cont >> contest.place;
		cont >> contest.rating;
		vectCont.push_back(contest);
	}
	cont.close();
}
/////////////////////////////////////////////////


//ENCRYPTIONS
string EncryptionOUT(string password, string keyWord) {
	int key;
	for (int i = 0; i < size(keyWord); i++) {
		key = keyWord[i];
	}
	int symbol;
	string inf = "";
	for (int i = 0; i < size(password); i++) {
		symbol = password[i] + key;
		inf += to_string(symbol) + " ";
	}
	return inf;
}
bool EncryptionIN(string password, string password1, string keyWord) {
	int key;
	for (int i = 0; i < size(keyWord); i++) {
		key = keyWord[i];
	}
	string checkPassword;
	int symbol;

	for (int i = 0; i < size(password); i++) {
		symbol = password[i] + key;
		checkPassword += to_string(symbol) + " ";
	}

	if (checkPassword == password1)
		return 1;
	else return 0;
}
/////////////////////////////////////////////////


bool AddContest() {
	infCont cont;
	bool isCorrect = 1;
	int x = 47;
	GoToXY(x, 11);
	cout << "ФИО конкурсанта: ";
	string a;
	a = getchar();
	getline(cin, cont.name);
	if (a != "\n")
		cont.name.insert(0, a);
	GoToXY(x, 12);
	cout << "Возраст конкурсанта: ";
	cin >> cont.year;
	if (cont.year <= 0 || cont.year > 20) {
		GoToXY(37, 14);
		cout << "Конкурсант не может быть старше 20 лет и " << endl;
		GoToXY(35, 15);
		cout << "его возраст не может быть меньше или равен ноль" << endl;
		GoToXY(47, 16);
		cout << "Конкурсант не добавлен." << endl;
		return 0;
	}
	GoToXY(x, 13);
	cout << "Страна конкурсанта: ";
	getchar();
	getline(cin, cont.country);
	GoToXY(x, 14);
	cout << "Музыкальный инструмент: ";
	getline(cin, cont.musicInst);
	do {
		GoToXY(x, 15);
		cout << "Занятое место: ";
		isCorrect = 1;
		cin >> cont.place;
		if (cont.place <= 0) {
			GoToXY(36, 17);
			cout << "Занятое место не может быть меньше или равно ноль." << endl;
			GoToXY(45, 18);
			cout << "Введите занятое место еще раз." << endl;
			_getch();
			system("cls");
			isCorrect = 0;
		}
	} while (isCorrect == 0);
	cont.rating = 0;
	vectCont.push_back(cont);
	system("cls");
	GoToXY(42, 11);
	cout << "Конкурсант успешно добавлен в систему." << endl << endl;
	return 1;
}
int Authorization(int& role) {
	fstream inf;

	inf.open("inf.txt", fstream::in);
	info person[2];
	person[0].role = role;
	GoToXY(50, 11);
	cout << "Введите логин: ";
	cin >> person[0].login;
	char ch;
	bool ctrlPressed = false;

	system("cls");
	GoToXY(51, 11);
	cout << "Введите пароль: ";
	person[0].password = "";

	while (true) {
		ch = _getch();
		if (ch == 13) { // 13 - код клавиши Enter
			break;
		}
		if (ch == 8 || ch == 127) { // 8 - код клавиши Backspace, 127 - код клавиши Delete
			if (person[0].password.length() > 0) {
				person[0].password.erase(person[0].password.length() - 1);
				cout << "\b \b"; // удаляем последнюю звездочку
			}
		}
		else if (ch >= 32 && ch <= 126 && ch != 0) { // игнорируем клавиши F1-F12
			if (ctrlPressed) { // проверяем, была ли нажата клавиша Ctrl
				if (ch == 'c' || ch == 'C' || ch == 'v' || ch == 'V') { // проверяем, была ли нажата клавиша C или V
					continue; // игнорируем клавиши сочетания
				}
			}
			person[0].password += ch;
			cout << '*';
		}
		else if (ch == -32) { // игнорируем коды направлений стрелок
			ch = _getch(); // считываем второй байт кода клавиши
			if (ch == 72 || ch == 75 || ch == 77 || ch == 80) { // проверяем, является ли второй байт кодом стрелки
				continue; // игнорируем стрелки
			}
		}
		else if (ch == 3 || ch == 22 || ch == 24) { // игнорируем клавиши сочетания Ctrl+C, Ctrl+V, Ctrl+X
			ctrlPressed = true;
		}
		else {
			ctrlPressed = false;
		}
	}
	bool isCorrect = 0;

	while (inf >> person[1].login) {
		int num = inf.tellp();
		inf.seekp(num + 2);
		getline(inf, person[1].password);
		inf >> person[1].role;
		inf >> person[1].isActive;
		inf >> person[1].keyWord;
		if (person[0].login == person[1].login && EncryptionIN(person[0].password, person[1].password, person[1].keyWord) && person[0].role == person[1].role && person[1].isActive != 0)
			isCorrect = 1;
	}
	inf.close();

	if (isCorrect == 1)
		switch (role)
		{
		case 1: {
			system("cls");
			GoToXY(47, 11);
			cout << "Добро пожаловать в систему!" << endl;
			GoToXY(45, 12);
			cout << "Вы вошли от имени администратора." << endl;
			BackBlack();
			system("pause");
			role = 1;
		}
			  break;
		case 2: {
			system("cls");
			GoToXY(47, 11);
			cout << "Добро пожаловать в систему!" << endl;
			GoToXY(45, 12);
			cout << "Вы вошли от имени конкурсанта." << endl;
			BackBlack();
			system("pause");
			role = 2;
		}
			  break;
		case 3: {
			system("cls");
			GoToXY(47, 11);
			cout << "Добро пожаловать в систему!" << endl;
			GoToXY(45, 12);
			cout << "Вы вошли от имени пользователя." << endl;
			BackBlack();
			system("pause");
			role = 3;
		}
			  break;
			  return 0;
		}
	else {
		if (person[1].isActive == 0) {
			system("cls");
			GoToXY(50, 11);
			cout << "Данный аккаунт заблокирован." << endl;
			BackBlack();
			system("pause");
		}
		system("cls");
		GoToXY(50, 12);
		cout << "Авторизация не удалась." << endl;
		BackBlack();
		system("pause");
		return 0;
	}
}
void Registration(int& role, bool& isCorrect) {
	int numOfTimes = 0;
	info person[2];
	bool isCheck = 0;
	while (numOfTimes != 3) {
		GoToXY(48, 11);
		White();
		cout << "Введите имя пользователя: ";
		string ch;
		ch = getchar();
		getline(cin, person[0].login);
		if (ch != "\n")
			person[0].login.insert(0, ch);
		isCheck = 0;
		if (role == 3)
			person[0].role = role;
		else person[0].role = 2;

		for (int i = 0; i < vectInf.size() && isCheck == 0; i++) {
			if (vectInf[i].login == person[0].login)
				isCheck = 1;
		}
		if (size(person[0].login) >= 1)
			if (isCheck == 1) {
				numOfTimes++;
				system("cls");
				White();
				GoToXY(48, 11);
				cout << "Введённое имя уже занято." << endl;
				GoToXY(46, 12);
				cout << "Оставшееся количество попыток: " << 3 - numOfTimes << endl << endl;
				_getch();
				system("cls");
			}
			else if (person[0].login.find(' ') != string::npos) {
				GoToXY(45, 12);
				cout << "Логин не должен содержать пробелов." << endl;
				_getch();
				system("cls");
			}
			else
			{

				while (true) {
					char ch;
					bool ctrlPressed = false;

					//system("cls");

					for (int i = 0; i < 2; i++) {
						if (i == 0) {
							system("cls");
							GoToXY(51, 11);
							cout << "Введите пaроль: ";
							person[i].password = "";
						}
						else {
							GoToXY(51, 12);
							cout << "Повторите пaроль: ";
							person[i].password = "";
						}


						while (true) {
							ch = _getch();
							if (ch == 13) { // 13 - код клавиши Enter
								break;
							}
							if (ch == 8 || ch == 127) { // 8 - код клавиши Backspace, 127 - код клавиши Delete
								if (person[i].password.length() > 0) {
									person[i].password.erase(person[i].password.length() - 1);
									cout << "\b \b"; // удаляем последнюю звездочку
								}
							}
							else if (ch >= 32 && ch <= 126 && ch != 0) { // игнорируем клавиши F1-F12
								if (ctrlPressed) { // проверяем, была ли нажата клавиша Ctrl
									if (ch == 'c' || ch == 'C' || ch == 'v' || ch == 'V') { // проверяем, была ли нажата клавиша C или V
										continue; // игнорируем клавиши сочетания
									}
								}
								person[i].password += ch;
								cout << '*';
							}
							else if (ch == -32) { // игнорируем коды направлений стрелок
								ch = _getch(); // считываем второй байт кода клавиши
								if (ch == 72 || ch == 75 || ch == 77 || ch == 80) { // проверяем, является ли второй байт кодом стрелки
									continue; // игнорируем стрелки
								}
							}
							else if (ch == 3 || ch == 22 || ch == 24) { // игнорируем клавиши сочетания Ctrl+C, Ctrl+V, Ctrl+X
								ctrlPressed = true;
							}
							else {
								ctrlPressed = false;
							}
						}
					}

					if (person[0].password != person[1].password) {
						GoToXY(51, 13);
						cout << "Пaроли не совпадают." << endl;
						_getch();
						system("cls");
					}
					else if (person[0].password.size() < 8) {
						GoToXY(40, 12);
						cout << "Пароль должен содержать больше 8 символов." << endl;
						_getch();
						system("cls");
					}
					else if (person[0].password.find(' ') != string::npos) {
						GoToXY(45, 12);
						cout << "Пароль не должен содержать пробелов." << endl;
						_getch();
						system("cls");
					}
					else break;
				}
				int a;


				if (role == 3) {
					a = 3;
					system("cls");
					GoToXY(49, 11);
					cout << "Регистрация прошла успешно." << endl;
					_getch();
					system("cls");
					isCorrect = 1;
				}
				else {
					a = 2;
					system("cls");
					GoToXY(44, 11);
					cout << "Пользователь успешно добавлен в систему." << endl;
					_getch();
					system("cls");
				}
				person[1].login = person[0].login;
				person[1].keyWord = RandString();
				person[1].password = EncryptionOUT(person[0].password, person[1].keyWord);
				person[1].role = a;
				person[1].isActive = 1;
				vectInf.push_back(person[1]);
				numOfTimes = 3;
			}
	}
}
void Apply() {
	ApplyCont cont;
	bool isCorrect;
	int x, y = 7;
	GoToXY(46, y);
	cout << "Пожалуйста, введите ваши данные: " << endl;
	y += 2;
	GoToXY(50, y++);
	cout << "ФИО: ";
	string a;
	a = getchar();
	getline(cin, cont.name);
	if (a != "\n")
		cont.name.insert(0, a);

	do {
		GoToXY(50, y);
		cout << "Возраст: ";
		isCorrect = 1;
		cin >> cont.year;
		if (cont.year <= 0 || cont.year >= 100) {
			GoToXY(50, y + 1);
			cout << "Возраст введен некорректно." << endl;
			GoToXY(50, y + 1);
			cout << "Повторите попытку." << endl;
			isCorrect = 0;
		}
	} while (isCorrect == 0);
	y++;
	GoToXY(50, y++);
	cout << "Страна: ";
	getchar();
	getline(cin, cont.country);
	GoToXY(50, y++);
	cout << "Музыкальный инструмент: ";
	getline(cin, cont.musicInst);

	vectApply.push_back(cont);
	system("cls");
	GoToXY(40, y);
	cout << "Заявление на участие в конкурсе успешно подано." << endl << endl;
	_getch();
}


void UnBlockAccount() {
	int position;
	char choice_ch;
	info person[2];
	string choice_s;
	bool isCheck = 0, isCorrect = 0;
	system("cls");
	int y = 3, x = 50;
	White();
	GoToXY(x, y++);
	cout << "________________________________________" << endl;
	GoToXY(x, y++);
	cout << "  Логин                       Роль" << endl;
	y++;

	for (int i = 0; i < vectInf.size() - 1; i++) {
		string role;
		GoToXY(x, y++);
		if (vectInf[i].role == 2)
			role = "Конкурсант";
		else if (vectInf[i].role == 3)
			role = "Пользователь";
		else role = "Администратор";
		cout << setw(27) << left << vectInf[i].login << setw(12) << left << role << setw(1) << endl;
	}
	GoToXY(x, y++);
	cout << "________________________________________" << endl;
	GoToXY(x, y++);
	cout << "Введите имя пользователя: ";
	cin >> person[0].login;
	isCheck = 0;
	for (int i = 0; i < vectInf.size() && isCheck == 0; i++)
		if (vectInf[i].login == person[0].login) {
			isCheck = 1;
			position = i;
		}
	if (isCheck == 1) {
		if (vectInf[position].role == 1) {
			GoToXY(35, y++);
			cout << "Данная операция не может быть проведена с администратором." << endl;
			_getch();
		}
		else if (vectInf[position].isActive == 1) {
			GoToXY(x, y++);
			cout << "Аккаунт " << person[0].login << " не заблокирован." << endl;
			isCorrect = 1;
			_getch();
		}
		else
		{
			vectInf[position].isActive = 0;
			GoToXY(x, y++);
			cout << "Аккаунт " << person[0].login << " упешно разблокирован." << endl;
			isCorrect = 1;
			_getch();
		}
	}
	else {
		GoToXY(x, y++);
		cout << "Аккаунт " << person[0].login << " отсутствует" << endl;
		_getch();
		system("cls");
	}
}
void BlockAccount() {
	int position;
	char choice_ch;
	info person[2];
	string choice_s;
	bool isCheck = 0, isCorrect = 0;
	system("cls");
	int y = 3, x = 50;
	White();
	GoToXY(x, y++);
	cout << "________________________________________" << endl;
	GoToXY(x, y++);
	cout << "  Логин                       Роль" << endl;
	y++;

	for (int i = 0; i < vectInf.size() - 1; i++) {
		string role;
		GoToXY(x, y++);
		if (vectInf[i].role == 2)
			role = "Конкурсант";
		else if (vectInf[i].role == 3)
			role = "Пользователь";
		else role = "Администратор";
		cout << setw(27) << left << vectInf[i].login << setw(12) << left << role << setw(1) << endl;
	}
	GoToXY(x, y++);
	cout << "________________________________________" << endl;
	GoToXY(x, y++);
	cout << "Введите имя пользователя: ";
	cin >> person[0].login;
	isCheck = 0;
	for (int i = 0; i < vectInf.size() && isCheck == 0; i++)
		if (vectInf[i].login == person[0].login) {
			isCheck = 1;
			position = i;
		}
	if (isCheck == 1) {
		if (vectInf[position].role == 1) {
			GoToXY(35, y++);
			cout << "Данная операция не может быть проведена с администратором." << endl;
			_getch();
		}
		else if (vectInf[position].isActive == 0) {
			GoToXY(x, y++);
			cout << "Аккаунт " << person[0].login << " уже заблокирован." << endl;
			isCorrect = 1;
			_getch();
		}
		else
		{
			vectInf[position].isActive = 0;
			GoToXY(x, y++);
			cout << "Аккаунт " << person[0].login << " упешно заблокирован." << endl;
			isCorrect = 1;
			_getch();
		}
	}
	else {
		GoToXY(x, y++);
		cout << "Аккаунт " << person[0].login << " отсутствует" << endl;
		_getch();
		system("cls");
	}
}
int ManagementAccount() {
	int position;
	char choice_ch;
	info person[2];
	string choice_s;
	bool isCheck = 0, isCorrect = 0;
	string menu[] = { "Заблокировать аккаунт", "Разблокировать аккаунт", "Зарегистрировать конкурсанта", "Назад" };
	int active_menu = 0;
	while (isCorrect == 0) {
		system("cls");
		White();
		int x = 50, y = 10;
		GoToXY(x, y);
		cout << "Меню сортировки" << endl;
		Grey(); GoToXY(x - 4, y); cout << ">"; GoToXY(x + 19, y); cout << "<";
		x = 50, y = 12;
		for (int i = 0; i < size(menu); i++) {
			if (i == active_menu) {
				GoToXY(x - 4, y);
				LightRed();
				cout << ">";
			}
			else White();
			GoToXY(x, y++);
			cout << menu[i] << endl;
		}
		GoToXY(x, y++);

		char ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case UP: {
			if (active_menu <= 0)
				active_menu = size(menu);
			--active_menu;
		}
			   break;
		case DOWN: {
			++active_menu;
			if (active_menu >= size(menu))
				active_menu = 0;
		}
				 break;
		case ENTER:
			switch (active_menu)
			{
			case 0:
				system("cls");
				BlockAccount();
				break;
			case 1: {
				system("cls");
				UnBlockAccount();
			}
				  break;
			case 2: {
				int role = 1;
				system("cls");
				Registration(role, isCorrect);
				system("cls");
				return 0;

				break;
			}
				  break;
			case 3: {
				BackBlack();
				system("cls");
				return 0;
			}
				  break;
			}
		}
	}
}




int OutCont() {
	int x = 14, y = 1;
	GoToXY(x, y++);
	cout << "________________________________________________________________________________________________" << endl;
	GoToXY(x, y++);
	cout << " ФИО                                 Возраст  Страна             Инструмент      Место  Рейтинг " << endl;
	GoToXY(x, y++);
	for (int i = 0; i < vectCont.size(); i++)
	{
		GoToXY(x, y++);
		cout << " " << setw(35) << left << vectCont[i].name << " " << setw(8) << left << vectCont[i].year
			<< " " << setw(18) << left << vectCont[i].country << " " << setw(15) << left << vectCont[i].musicInst
			<< " " << setw(6) << left << vectCont[i].place << " " << setw(9) << left << vectCont[i].rating << " " << endl;
	}
	GoToXY(x, y++);
	cout << "________________________________________________________________________________________________" << endl;
	return y;
}
void SetRating() {
	infCont cont;
	bool isCorrect = 0;
	int num, y;
	system("cls");
	y = OutCont();
	GoToXY(40, y++);
	cout << "Введите ФИО конкурсанта: ";
	string a;
	a = getchar();
	getline(cin, cont.name);
	if (a != "\n")
		cont.name.insert(0, a);

	for (int i = 0; i < vectCont.size() && isCorrect == 0; i++)
		if (vectCont[i].name == cont.name) {
			isCorrect = 1;
			num = i;
		}
	if (isCorrect == 1) {
		bool isOK = 0;
		while (isOK == 0) {
			system("cls");
			GoToXY(50, 11);
			cout << "Введите рейтинг (1/10): ";
			cin >> cont.rating;
			if (cont.rating < 1 || cont.rating>10)
			{
				GoToXY(52, 13);
				cout << "Рейтинг введет неверно. " << endl;
				GoToXY(45, 14);
				cout << "Рейтинг не может быть ниже 1 и выше 10." << endl;
				_getch();
			}
			else {
				if (vectCont[num].rating == 0)
					vectCont[num].rating = cont.rating;
				else
					vectCont[num].rating = (vectCont[num].rating + cont.rating) / 2;
				system("cls");
				GoToXY(50, 11);
				cout << "Рейтинг выставлен." << endl;
				isOK = 1;
			}
		}
	}
	else {
		GoToXY(48, 12);
		system("cls");
		cout << "Данный конкурсант не найден." << endl;
	}
}
void FindCont() {
	string cont_name;
	string a;
	bool first = 1;
	int length = 75;
	int numOfResult = 0;
	GoToXY(55, 7);
	cout << "Поиск конкурсанта" << endl;
	GoToXY(50, 12);
	cout << "Введите строку для поиска: ";

	a = getchar();
	if (a != "\n")
		cont_name.insert(0, a);
	getline(cin, cont_name);

	system("cls");
	int x = 14, y = 1;
	for (int i = 0; i < vectCont.size(); i++)
	{
		if (vectCont[i].name.find(cont_name) != string::npos)
		{
			if (first == 1)
			{
				GoToXY(x, y++);
				cout << "________________________________________________________________________________________________" << endl;
				GoToXY(x, y++);
				cout << " ФИО                                 Возраст  Страна             Инструмент      Место  Рейтинг " << endl;
				GoToXY(x, y++);
				first = 0;
			}
			GoToXY(x, y++);
			cout << " " << setw(35) << left << vectCont[i].name << " " << setw(8) << left << vectCont[i].year
				<< " " << setw(18) << left << vectCont[i].country << " " << setw(15) << left << vectCont[i].musicInst
				<< " " << setw(6) << left << vectCont[i].place << " " << setw(9) << left << vectCont[i].rating << " " << endl;
			numOfResult++;
		}
	}
	if (numOfResult == 0) {
		GoToXY(45, 9);
		cout << "По вашему запросу ничего не найдено" << endl;
	}
	else {
		GoToXY(x, y++);
		cout << "________________________________________________________________________________________________" << endl;
	}
	getchar();
	/*GoToXY(38, 5);
	cout << "Информация о конкурсанте(ах) с ФИО: " << cont_name << endl;
	int x = 50, y = 7, count = 0;
	for (int i = 0; i < vectCont.size(); i++) {
		if (vectCont[i].name == cont_name) {
			count++;
			GoToXY(x - 3, y);
			cout << "№" << count;
			GoToXY(x, y++);
			cout << "ФИО: " << vectCont[i].name;
			GoToXY(x, y++);
			cout << "Возраст: " << vectCont[i].year;
			GoToXY(x, y++);
			cout << "Страна: " << vectCont[i].country;
			GoToXY(x, y++);
			cout << "Инструмент: " << vectCont[i].musicInst;
			GoToXY(x, y++);
			cout << "Место: " << vectCont[i].place;
			GoToXY(x, y++);
			cout << "Рейтинг: " << vectCont[i].rating;

			y++;
		}
	}
	if (count == 0) {
		GoToXY(48, 8);
		cout << "Данные о конкурсанте отсутствуют" << endl;
	}*/

}


//SORTING
void SortByAge() {
	for (int i = 0; i < vectCont.size(); i++)
		for (int j = 0; j < vectCont.size() - 1; j++) {
			if (vectCont[j].year > vectCont[i].year)
				swap(vectCont[i], vectCont[j]);
		}

}
void SortByRating() {
	for (int i = 0; i < vectCont.size(); i++)
		for (int j = 0; j < vectCont.size() - 1; j++) {
			if (vectCont[j].rating < vectCont[i].rating)
				swap(vectCont[i], vectCont[j]);
		}

}
void SortByInstrument() {
	for (int i = 0; i < vectCont.size(); i++)
		for (int j = 0; j < vectCont.size() - 1; j++) {
			if (vectCont[j].musicInst > vectCont[i].musicInst)
				swap(vectCont[i], vectCont[j]);
		}
}
void SortByName() {
	for (int i = 0; i < vectCont.size(); i++)
		for (int j = 0; j < vectCont.size() - 1; j++) {
			if (vectCont[j].name > vectCont[i].name)
				swap(vectCont[i], vectCont[j]);
		}
}
void SortByCountry() {
	for (int i = 0; i < vectCont.size(); i++)
		for (int j = 0; j < vectCont.size() - 1; j++) {
			if (vectCont[j].country > vectCont[i].country)
				swap(vectCont[i], vectCont[j]);
		}
}
void SortByPlace() {
	for (int i = 0; i < vectCont.size(); i++)
		for (int j = 0; j < vectCont.size() - 1; j++) {
			if (vectCont[j].place > vectCont[i].place)
				swap(vectCont[i], vectCont[j]);
		}
}
int Sort() {
	bool isCorrect = 0;
	string menu[] = { "Сортировать по возрасту", "Сортировать по рейтингу", "Сортировать по инструменту" , "Сортировать по имени" , "Сортировать по стране", "Сортировать по месту", "Назад" };
	int active_menu = 0;
	while (isCorrect == 0) {
		system("cls");
		White();
		int x = 50, y = 10;
		GoToXY(x, y);
		cout << "Меню сортировки" << endl;
		Grey(); GoToXY(x - 4, y); cout << ">"; GoToXY(x + 19, y); cout << "<";
		x = 50, y = 12;
		for (int i = 0; i < size(menu); i++) {
			if (i == active_menu) {
				if (i == active_menu) {
					GoToXY(x - 4, y);
					LightRed();
					cout << ">";
				}
			}
			else White();
			GoToXY(x, y++);
			cout << menu[i] << endl;
		}
		GoToXY(x, y++);

		char ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case UP: {
			if (active_menu <= 0)
				active_menu = size(menu);
			--active_menu;
		}
			   break;
		case DOWN: {
			++active_menu;
			if (active_menu >= size(menu))
				active_menu = 0;
		}
				 break;
		case ENTER:
			isCorrect = 1;
			switch (active_menu)
			{
			case 0:
				SortByAge();
				system("cls");
				OutCont();
				_getch();
				break;
			case 1: {
				SortByRating();
				system("cls");
				OutCont();
				_getch();
			}
				  break;
			case 2:
				SortByInstrument();
				system("cls");
				OutCont();
				_getch();
				break;
			case 3:
				SortByName();
				system("cls");
				OutCont();
				_getch();
				break;
			case 4:
				SortByCountry();
				system("cls");
				OutCont();
				_getch();
				break;
			case 5:
				SortByPlace();
				system("cls");
				OutCont();
				_getch();
				break;
			case 6: {
				White();
				system("cls");
				return 0;
			}
				  break;
			}
			break;
		}
	}
	system("cls");
}
void WinnersByAge() {
	SortByAge();
	int x = 14, y = 1;
	GoToXY(x, y++);
	cout << "________________________________________________________________________________________________" << endl;
	GoToXY(x, y++);
	cout << " ФИО                                 Возраст  Страна             Инструмент      Место  Рейтинг " << endl;
	GoToXY(x, y++);
	for (int i = 0; i < vectCont.size(); i++)
	{
		if (vectCont[i].place >= 1 && vectCont[i].place <= 3 && vectCont[i].year < 12) {
			GoToXY(x, y++);
			cout << " " << setw(35) << left << vectCont[i].name << " " << setw(8) << left << vectCont[i].year
				<< " " << setw(18) << left << vectCont[i].country << " " << setw(15) << left << vectCont[i].musicInst
				<< " " << setw(6) << left << vectCont[i].place << " " << setw(9) << left << vectCont[i].rating << " " << endl;
		}
	}
	GoToXY(x, y++);
	cout << "________________________________________________________________________________________________" << endl;
}
void WinnersByInst() {

	SortByInstrument();
	int x = 14, y = 0, j = 0, num = 0;

	for (int i = 0; i < vectCont.size(); i++)
		for (int j = 0; j < vectCont.size() - 1; j++) {
			if (vectCont[j].place > vectCont[i].place && vectCont[i].musicInst == vectCont[j].musicInst)
				swap(vectCont[i], vectCont[j]);
		}
	bool count = 1;

	for (int i = 0; i < vectCont.size(); i++) {
		num = 0;
		if (count == 1 && vectCont[i].place <= 3)
		{
			y += 2;
			GoToXY(x, y++);
			cout << "Музыкальный инструмент: " << vectCont[i].musicInst << endl;
			GoToXY(x, y++);
			cout << "_____________________________________________________" << endl;
			GoToXY(x, y++);
			cout << " ФИО                                 Возраст  Место  " << endl;

			for (j = i; j < vectCont.size() && vectCont[j].place <= 3 && vectCont[i].musicInst == vectCont[j].musicInst; j++) {
				GoToXY(x, y++);
				cout << " " << setw(35) << left << vectCont[j].name
					<< " " << setw(8) << left << vectCont[j].year
					<< " " << setw(6) << left << vectCont[j].place << " " << endl;
				num++;
			}
			GoToXY(x, y++);
			cout << "_____________________________________________________" << endl;
			num--;
		}

		if (vectCont[i].musicInst != vectCont[i + 1].musicInst || vectCont[i].musicInst != vectCont[i - 1].musicInst)
			count = 1;
		else count = 0;
		i += num;
	}
}
/////////////////////////////////////////////////

int list() {
	bool isCorrect = 0;
	string menu[] = { "Первые три места по классу инструментов", "Самые молодые победители конкурса", "Назад" };
	int active_menu = 0;
	while (isCorrect == 0) {
		system("cls");
		White();
		int x = 50, y = 10;
		GoToXY(x, y);
		cout << "Меню списка" << endl;
		Grey(); GoToXY(x - 4, y); cout << ">"; GoToXY(x + 15, y); cout << "<";
		x = 50, y = 12;
		for (int i = 0; i < size(menu); i++) {
			if (i == active_menu) {
				GoToXY(x - 4, y);
				LightRed();
				cout << ">";
			}
			else White();
			GoToXY(x, y++);
			cout << menu[i] << endl;
		}
		GoToXY(x, y++);

		char ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case UP: {
			if (active_menu <= 0)
				active_menu = size(menu);
			--active_menu;
		}
			   break;
		case DOWN: {
			++active_menu;
			if (active_menu >= size(menu))
				active_menu = 0;
		}
				 break;
		case ENTER:
			switch (active_menu)
			{
			case 0:
				system("cls");
				WinnersByInst();
				_getch();
				system("cls");
				break;
			case 1: {
				system("cls");
				WinnersByAge();
				_getch();
				system("cls");
			}
				  break;
			case 2: {
				White();
				system("cls");
				return 0;
			}
			}
			break;
		}
	}
}


int ApplicationManagement() {
	if (vectApply.size() == 0) {
		GoToXY(55, 11);
		cout << "Заявления отсутствуют";
		_getch();
		return 0;
	}
	fstream newCont;
	bool isCorrect = 0, isOK = 0, isAccept = 0;
	string menu[] = { "Принять", "Отклонить" };
	int active_menu = 0;

	newCont.open("newContest.txt", fstream::app);
	for (int i = 0; i < vectApply.size() && isOK == 0; i++) {

		GoToXY(56, 5);
		cout << "ЗАЯВЛЕНИЕ №" << i + 1 << endl;
		GoToXY(37, 6);
		Grey();
		cout << "(для остановки управлением заявками нажмите ESC)" << endl;
		White();
		int x = 50, y = 11;
		GoToXY(x, y++);
		cout << "ФИО: " << vectApply[i].name << endl;
		GoToXY(x, y++);
		cout << "Возраст: " << vectApply[i].year << endl;
		GoToXY(x, y++);
		cout << "Страна: " << vectApply[i].country << endl;
		GoToXY(x, y++);
		cout << "Музыкальный инструмент: " << vectApply[i].musicInst << endl;

		isAccept = 0;
		isCorrect = 0;
		while (isCorrect == 0) {
			x = 33, y = 20;
			for (int i = 0; i < size(menu); i++) {
				if (i == active_menu && i == 1)
					LightRed();
				else
					if (i == active_menu && i == 0)
						Green();
					else White();
				if (i == size(menu) - 1)
					GoToXY(x += 47, y);
				else GoToXY(x, y);
				cout << menu[i] << endl;
			}
			White();
			GoToXY(x, y++);

			char ch = _getch();
			if (ch == -32) ch = _getch();
			switch (ch)
			{
			case ESC: {
				isCorrect = 1;
				isOK = 1;
			}
					break;
			case LEFT: {
				if (active_menu > 0)
					--active_menu;
			}
					 break;
			case RIGHT: {
				if (active_menu < size(menu) - 1)
					++active_menu;
			}
					  break;
			case ENTER:
				switch (active_menu)
				{
				case 0:
					system("cls");
					GoToXY(55, 11);
					cout << "Заявление принято";
					isCorrect = 1;
					isAccept = 1;
					_getch();
					system("cls");
					break;
				case 1: {
					system("cls");
					GoToXY(55, 11);
					cout << "Заявление отклонено";
					isCorrect = 1;
					_getch();
					system("cls");
				}
					  break;
				}
				break;
			}
		}

		if (isAccept == 1)
			newCont << vectApply[i].year << endl << vectApply[i].name << endl << vectApply[i].country << endl << vectApply[i].musicInst << endl;
		if (isOK != 1)
			vectApply.erase(vectApply.begin() + i);
		i--;
	}
	newCont.close();
}

//MENU
void menuAdmin(int& role) {
	bool isCorrect = 0;
	string menu[] = { "Добавить конкурсанта", "Управление учётными записями",
		"Вывести список участников", "Управлять заявками на участие",  "Сортировать конкурсантов" , "Поиск конкурсанта" , "Выйти из учетной записи" };
	int active_menu = 0;
	while (isCorrect == 0) {
		system("cls");
		White();
		int x = 50, y = 10;
		GoToXY(x, y);
		cout << "Меню администратора" << endl;
		Grey(); GoToXY(x - 4, y); cout << ">"; GoToXY(x + 23, y); cout << "<";
		x = 50, y = 12;
		for (int i = 0; i < size(menu); i++) {
			if (i == active_menu) {
				if (i == size(menu) - 1)
					GoToXY(x - 4, y + 2);
				else
					GoToXY(x - 4, y);
				LightRed();
				cout << ">";
			}
			else White();
			if (i == size(menu) - 1)
				GoToXY(x, y += 2);
			else
				GoToXY(x, y++);
			cout << menu[i] << endl;
		}
		GoToXY(x, y++);

		char ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case UP: {
			if (active_menu <= 0)
				active_menu = size(menu);
			--active_menu;
		}
			   break;
		case DOWN: {
			++active_menu;
			if (active_menu >= size(menu))
				active_menu = 0;
		}
				 break;
		case ENTER:
			switch (active_menu)
			{
			case 0: {
				system("cls");
				AddContest();
				_getch();
				system("cls");
			}
				  break;
			case 1: {
				system("cls");
				ManagementAccount();
				system("cls");
			}
				  break;
			case 2: {
				system("cls");
				OutCont();
				_getch();
				system("cls");
			}
				  break;
			case 3: {
				system("cls");
				ApplicationManagement();
				system("cls");
			}
				  break;
			case 4: {
				system("cls");
				Sort();
			}
				  break;
			case 5: {
				system("cls");
				FindCont();
				_getch();
				system("cls");
			}
				  break;
			case 6: {
				BackBlack();
				system("cls");
				isCorrect = 1;
			}
				  break;
			}
			break;
		}
	}
}
bool menuAthor(int& role) {


	string choice_s;
	bool isCorrect = 0;
	if (role == 3) {
		string menu[] = { "Авторизироваться", "Регистрация", "Назад" };
		int active_menu = 0;
		while (isCorrect == 0) {
			system("cls");
			White();
			int x = 50, y = 10;
			GoToXY(x, y);
			cout << "Меню авторизации" << endl;
			Grey(); GoToXY(x - 4, y); cout << ">"; GoToXY(x + 20, y); cout << "<";
			x = 50, y = 12;
			for (int i = 0; i < size(menu); i++) {
				if (i == active_menu) {
					GoToXY(x - 4, y);
					LightRed();
					cout << ">";
				}
				else White();
				GoToXY(x, y++);
				cout << menu[i] << endl;
			}
			GoToXY(x, y++);

			char ch = _getch();
			if (ch == -32) ch = _getch();
			switch (ch)
			{
			case UP: {
				if (active_menu <= 0)
					active_menu = size(menu);
				--active_menu;
			}
				   break;
			case DOWN: {
				++active_menu;
				if (active_menu >= size(menu))
					active_menu = 0;
			}
					 break;
			case ENTER:
				switch (active_menu)
				{
				case 0:
					system("cls");
					isCorrect = Authorization(role);
					_getch();
					system("cls");
					break;
				case 1: {
					system("cls");
					Registration(role, isCorrect);
					system("cls");
				}
					  break;
				case 2: {
					White();
					system("cls");
					return 0;
				}
				}
				break;
			}
		}
	}
	else {
		string menu[] = { "Авторизироваться", "Назад" };
		int active_menu = 0;
		while (isCorrect == 0) {
			system("cls");
			White();
			int x = 50, y = 10;
			GoToXY(x, y);
			cout << "Меню авторизации" << endl;
			Grey(); GoToXY(x - 4, y); cout << ">"; GoToXY(x + 20, y); cout << "<";
			x = 50, y = 12;
			for (int i = 0; i < size(menu); i++) {
				if (i == active_menu) {
					GoToXY(x - 4, y);
					LightRed();
					cout << ">";
				}
				else White();
				GoToXY(x, y++);
				cout << menu[i] << endl;
			}
			GoToXY(x, y++);

			char ch = _getch();
			if (ch == -32) ch = _getch();
			switch (ch)
			{
			case UP: {
				if (active_menu <= 0)
					active_menu = size(menu);
				--active_menu;
			}
				   break;
			case DOWN: {
				++active_menu;
				if (active_menu >= size(menu))
					active_menu = 0;
			}
					 break;
			case ENTER:
				switch (active_menu)
				{
				case 0:
					system("cls");
					isCorrect = Authorization(role);
					system("cls");
					break;
				case 1: {
					White();
					system("cls");
					return 0;
				}
				}
				break;
			}
		}
	}
}
void menuUser(int& role) {

	string choice_s;
	bool isCorrect = 0;
	string menu[] = { "Вывести список участников", "Выставить рейтинг конкурсанту", "Сортировка конкурсантов" , "Поиск конкурсанта",
		"Список по параметру" ,"Выйти из учетной записи" };
	int active_menu = 0;
	while (isCorrect == 0) {
		system("cls");
		White();
		int x = 50, y = 10;
		GoToXY(x, y);
		cout << "Меню пользователя" << endl;
		Grey(); GoToXY(x - 4, y); cout << ">"; GoToXY(x + 20, y); cout << "<";
		x = 50, y = 12;
		for (int i = 0; i < size(menu); i++) {
			if (i == active_menu) {
				if (i == size(menu) - 1)
					GoToXY(x - 4, y + 2);
				else
					GoToXY(x - 4, y);
				LightRed();
				cout << ">";
			}
			else White();
			if (i == size(menu) - 1)
				GoToXY(x, y += 2);
			else
				GoToXY(x, y++);
			cout << menu[i] << endl;
		}
		GoToXY(x, y++);

		char ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case UP: {
			if (active_menu <= 0)
				active_menu = size(menu);
			--active_menu;
		}
			   break;
		case DOWN: {
			++active_menu;
			if (active_menu >= size(menu))
				active_menu = 0;
		}
				 break;
		case ENTER:
			switch (active_menu)
			{
			case 0:
				system("cls");
				OutCont();
				_getch();
				system("cls");
				break;
			case 1: {
				system("cls");
				SetRating();
				_getch();
				system("cls");
			}
				  break;
			case 2:
				system("cls");
				Sort();
				break;

			case 3: {
				system("cls");
				FindCont();
				_getch();
				system("cls");
			}
				  break;
			case 4: {
				system("cls");
				list();
				system("cls");
			}
				  break;
			case 5: {
				BackBlack();
				system("cls");
				isCorrect = 1;
			}
				  break;
			}
			break;
		}
	}
}
void menuContest() {
	string choice_s;
	bool isCorrect = 0;
	string menu[] = { "Подать заявку на участие", "Вывести список участников", "Сортировка конкурсантов" , "Поиск конкурсанта" ,
		"Список по параметру" ,"Выйти из учетной записи" };
	int active_menu = 0;
	while (isCorrect == 0) {
		system("cls");
		White();
		int x = 50, y = 10;
		GoToXY(x, y);
		cout << "Меню конкурсанта" << endl;
		Grey(); GoToXY(x - 4, y); cout << ">"; GoToXY(x + 19, y); cout << "<";
		x = 50, y = 12;
		for (int i = 0; i < size(menu); i++) {
			if (i == active_menu) {
				if (i == size(menu) - 1)
					GoToXY(x - 4, y + 2);
				else
					GoToXY(x - 4, y);
				LightRed();
				cout << ">";
			}
			else White();
			if (i == size(menu) - 1)
				GoToXY(x, y += 2);
			else
				GoToXY(x, y++);
			cout << menu[i] << endl;
		}
		GoToXY(x, y++);

		char ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case UP: {
			if (active_menu <= 0)
				active_menu = size(menu);
			--active_menu;
		}
			   break;
		case DOWN: {
			++active_menu;
			if (active_menu >= size(menu))
				active_menu = 0;
		}
				 break;
		case ENTER:
			switch (active_menu)
			{
			case 0:
				system("cls");
				Apply();
				system("cls");
				break;
			case 1: {
				system("cls");
				OutCont();
				_getch();
				system("cls");
			}
				  break;
			case 2: {
				system("cls");
				Sort();
			}
				  break;
			case 3: {
				system("cls");
				FindCont();
				_getch();
				system("cls");
			}
				  break;
			case 4: {
				system("cls");
				list();
				system("cls");
			}
				  break;
			case 5: {
				BackBlack();
				system("cls");
				isCorrect = 1;
			}
				  break;
			}
			break;
		}
	}
}
/////////////////////////////////////////////////



//OVERWRITING INFORMATION
void OverwriteInfo() {
	fstream inf;

	inf.open("inf.txt", fstream::out);
	for (int i = 0; i < vectInf.size(); i++) {
		if (i != 0)
			inf << endl;
		inf << vectInf[i].login << endl << vectInf[i].password
			<< endl << vectInf[i].role << endl
			<< vectInf[i].isActive << endl << vectInf[i].keyWord;
	}
	inf.close();
}
void OverwriteCont() {
	fstream cont;

	cont.open("contest.txt", fstream::out);
	for (int i = 0; i < vectCont.size(); i++) {
		if (i != 0)
			cont << endl;
		cont << vectCont[i].year << endl << vectCont[i].name
			<< endl << vectCont[i].country << endl
			<< vectCont[i].musicInst << endl << vectCont[i].place
			<< endl << vectCont[i].rating;
	}
	cont.close();
}
void OverwriteApplyCont() {
	fstream apply;

	apply.open("statement.txt", fstream::out);
	for (int i = 0; i < vectApply.size(); i++) {
		if (i != 0)
			apply << endl;
		apply << vectApply[i].year << endl
			<< vectApply[i].name << endl
			<< vectApply[i].country << endl
			<< vectApply[i].musicInst;
	}
	apply.close();
}
/////////////////////////////////////////////////



int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	SetConsoleTitle(L"Музыкальный конкурс");
	ConsoleCursorVisible(false, 100);

	readContest();
	ReadAppluCont();
	readInf();

	int role;
	string role_s;
	bool isCorrect = 0;
	int size_inf = 1;

	string choice_s;
	string menu[] = { "Администатор", "Конкурсант", "Пользователь" };
	int active_menu = 0;


	while (isCorrect == 0) {
		system("cls");
		White();
		GoToXY(38, 3);
		cout << " Добро пожаловать в музыкальное приложение " << endl;
		GoToXY(38, 4);
		cout << "          Пожалуйста, выберите роль         " << endl;
		GoToXY(38, 5);
		Grey();
		cout << "  (Для выхода из приложения нажмите ESC) " << endl;
		GoToXY(48, 11);
		White();
		cout << "    Главное меню    " << endl;
		GoToXY(48, 11); Grey(); cout << ">";
		GoToXY(68, 11); cout << "<";
		White();
		int x = 52, y = 13;
		for (int i = 0; i < size(menu); i++) {
			if (i == active_menu) {
				GoToXY(x - 4, y);
				LightRed();
				cout << ">";
			}
			else White();
			GoToXY(x, y++);
			cout << menu[i] << endl;
		}
		GoToXY(x, y++);
		char ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case ESC:
			isCorrect = 1;
			system("cls");
			break;
		case UP: {
			if (active_menu <= 0)
				active_menu = size(menu);
			--active_menu;
		}
			   break;
		case DOWN: {
			++active_menu;
			if (active_menu >= size(menu))
				active_menu = 0;
		}
				 break;
		case ENTER:
			switch (active_menu)
			{
			case 0:
				role = 1;
				system("cls");
				if (menuAthor(role) == 0)
					break;
				else {
					system("cls");
					menuAdmin(role);
					break;
				}
				break;
			case 1: {
				role = 2;
				system("cls");
				if (menuAthor(role) == 0)
					break;
				else {
					system("cls");
					menuContest();
					break;
				}
			}
			case 2: {
				role = 3;
				system("cls");
				if (menuAthor(role) == 0)
					break;
				else {
					system("cls");
					menuUser(role);
					break;
				}
			}
				  break;
			case 3: {
				BackBlack();
				system("cls");
				isCorrect = 1;
			}
			}
			break;
		}
	}
	PlayMusic();
	system("cls");
	Grey();
	GoToXY(50, 11);
	cout << "Работа программы завершена" << endl;
	White();
	GoToXY(39, 14);
	cout << "Спасибо, что воспользовались нашим приложением!" << endl;
	BackBlack();
	OverwriteInfo();
	OverwriteCont();
	OverwriteApplyCont();
}