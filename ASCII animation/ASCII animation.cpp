//#define _WIN32_WINNT 0x0502
#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <clocale>
#define KEY_PRESSED  0x8000
#define KEY_SWITCHED 0x0001
using namespace std;


void SizeWindow(const int X, const int Y)
{
	HWND hwnd = GetConsoleWindow();
	if (hwnd != NULL) { SetWindowPos(hwnd, 0, 0, 0, X, Y, SWP_SHOWWINDOW | SWP_NOMOVE); }
}
void OutFrame(const vector<string>& Frame, const int TimeFrame)
{
	for (int i = 0; i < Frame.size(); i++)
	{
		system("CLS");
		cout << "Press BACKSPACE, for close animation\n";
		cout << Frame[i];
		Sleep(TimeFrame);
		if (GetKeyState(VK_BACK) & KEY_PRESSED) break;
	}
}
void FillFrame(vector<string>& Frames, int number)
{
	//рабочий но для работы ctrl-c ctrl-v
	//основное редактирование текста будет в блокноте
	int x;
	string str = "";
	cout << "To finish editing frame, type 'END' in the next line\nDraw your frame N" << number + 1 << ":\n";
	string key = "END";
	while (true)
	{
		//if (GetKeyState(VK_END)& KEY_PRESSED) break;
		size_t found = str.find(key); //вернет -1 если ненайдет
		if (found != string::npos) // пока не находит key, то пропускаем
		{
			str.replace(found - 1, key.length() + 1, "");
			break;
		}
		int x = getchar();
		str += (char)x;
	}
	Frames[number] = str;
}

int main()
{
	const vector<string> actions = { "create_animation","open_animation","save_animation","show_animation","exit" };
	vector<string> Frames; //вектор кадров
	unsigned FrameSpeed = 0;
	while (true) {
		string str;
		system("CLS");
		cout << "select an action:\n";

		for (int i = 0; i < actions.size(); i++)
		{
			cout << "\t" << i + 1 << " or " << actions[i] + "\n";
		}
		cin >> str;

		if (str == actions[0] or str == to_string(1)) {
			system("CLS");
			int FramesCount;
			cout << "<" + actions[0] + ">\nFrame speed: ";
			cin >> FrameSpeed;
			cout << "\nFrames count: ";
			cin >> FramesCount;
			Frames.resize(FramesCount);
			for (int i = 0; i < Frames.size(); i++)
			{
				FillFrame(Frames, i);
			}
		}
		else if (str == actions[1] or str == to_string(2))
		{
			system("CLS");
			string filename;
			cout << "<" + actions[1] + ">\nEnter the file name like as 'anim'. (Have been saved in folder 'animations'\n>";
			cin >> filename;
			ifstream ifn;
			ifn.open("animations\\" + filename + ".txt"); // только чтение
			if (ifn.is_open())
			{
				Frames.clear();
				string temp;
				string frame;
				getline(ifn, temp);
				FrameSpeed = stoi(temp);
				while (getline(ifn, temp)) {
					if (!(temp.find("END") == string::npos))//если нашел END
					{
						Frames.push_back(frame);
						frame = "";
					}
					else
					{
						frame += "\n" + temp;
					}
				}
			}
			else {
				cout << "File cannot be opened";
			}
			ifn.close();

		}
		else if (str == actions[2] or str == to_string(3)) {
			if (!Frames.empty())
			{
				system("CLS");
				string filename;
				cout << "<" + actions[2] + ">\nEnter the file name like as 'anim'. (Have been saved in folder 'animations'\n>";
				cin >> filename;
				ofstream ofn;
				ofn.open("animations\\" + filename + ".txt"); // только запись
				if (ofn.is_open())
				{
					//запись vector в TXT
					ofn << FrameSpeed;
					for (string frame : Frames) {
						ofn << frame + "\nEND";
					}
					cout << "All animation have been saved!\n";
				}
				else {
					cout << "File cannot be opened";
				}
				ofn.close();
			}
			else cout << "There is no open animation right now!\n";
		}
		else if (str == actions[3] or str == to_string(4))
		{
			OutFrame(Frames, FrameSpeed);
		}
		if (str == actions[4] or str == to_string(5)) break;
	}
	return 0;
}

