#include <vector>
#include <sstream>
#include <iostream>
#include <assert.h>
using namespace std;


struct Question {

	int qid,askerid,askedid;
	string question_text, answer_text;
	bool showuser ;

};

struct User {
	string username, name, email, password;
	
		int userid;
		bool AQ;
};

vector<User>users;
vector<Question>questions;

void second_menu(User u);
void first_menu();
void Login();
void Signup(vector<User>& users);



void first_menu()
{
	int choice;
	cout << "Menu:\n\t\t1)LogIn:\n\t\t2)SignUp:\nenter number in range 1 - 2:\n";
	cin >> choice;

	if (choice == 1)
		Login();
	else if (choice == 2)
		Signup(users);
	else
	{
		cout << "\nInvalid choice..Try again";
		first_menu();
	}

}

void Login()
{
	User u;
	string username, password;
	cout << "\nEnter user name & Password:\t";
	cin >> username >> password;
	

	for (int i = 0; i < users.size(); i++)
	{
		if (users[i].username == username && users[i].password == password)
		{
			u = users[i];
			second_menu(u);
		}
	}

	cout << "Wrong user name or password"<<endl;
	first_menu ();
}

void Signup(vector<User>&users)
{
	User u;

	cout << "Enter user id:";
	cin >> u.userid;

	cout << "Enter username (nospaces):";
	cin >> u.username;

	cout << "Enter passward:";
	cin >> u.password;

	cout << "Enter name (nospaces):";
	cin>>u.name;

	cout << "Enter E-mail:";
	cin >> u.email;

	cout << "Allow Anonymous questions? ( 0 - 1 ): ";
	cin >> u.AQ;


	users.push_back(u);

		second_menu( u);
}

void print_questions_to_me(User u)
{
	for (auto q : questions)
	{
		if (q.askedid == u.userid)
		{

			cout << "Question ID: " << q.qid;
			
			if(q.showuser==true)
			cout<<" from user ID " << q.askerid;
			
			cout<<"\t Question: " << q.question_text << endl;
			  cout << "Answer: " << q.answer_text<<endl;

		}
	}
}

void print_questions_from_me(User u)
{
	for (auto q : questions)
	{
		if (q.askerid == u.userid)
		{
			cout << "Question ID:" << q.qid;
			
			if (q.showuser == true)
				cout << " !AQ";
			
			cout << " to user ID:" << q.askedid;
			cout<<"\t Question:" << q.question_text << endl;
			cout << "Answer: " << q.answer_text<<endl;
		}
	}

}


void Answer_question(User u)
{
	int choice;
	string answer;
	cout << "Enter Question id or -1 to cancle: ";
		cin >> choice;
		
		if (choice == -1)
			second_menu(u);

		else
		{
			for (int i = 0; i < questions.size(); i++)
			{
				if (questions[i].qid == choice && u.userid==questions[i].askedid)
				{
					if (questions[i].answer_text != "")
						cout << "Warning: Question is already answered..will be updated.\n";

					cout << "Enter Answer: ";
					
					getline(cin, answer); //to avoid last enter
					getline(cin, answer);

					questions[i].answer_text = answer;

					second_menu(u);
				}
			}
		}

		cout << "This question doesn`t exist.";
		second_menu(u);
}

void Delete_question(User u)
{
	int choice;
	cout<< "Enter Question id or -1 to cancle: ";
	cin >> choice;

	if (choice == -1)
		second_menu(u);


	else
	{
		for (auto it = questions.begin(); it != questions.end(); it++)
		{
			if ((*it).qid == choice && u.userid == (*it).askedid)
			{
				questions.erase(it);
				second_menu(u);
			}
			
		}
	}

	cout << "This question doesn`t exist.";
	second_menu(u);
}

void List_system_users()
{
	for (auto u : users)
		cout << "ID: " << u.userid << "\t\tName: " << u.name << endl;

}

void List_feed()
{
	for (auto q : questions)
	{
		if (q.answer_text != "") {
			cout << "Question ID: " << q.qid;


			if (q.showuser == true)
				cout << " from user: " << q.askerid;


			cout << " to user: " << q.askedid;
			cout << "\tQuestion: " << q.question_text << endl;
			cout << "Answer: " << q.answer_text << endl;
		}
	}
}

void Ask_question(User u)
{
	Question q;
	int choice1,choice2;
	string question;
	bool exist = false,repeated=false;
	cout << "Enter user ID or -1 to cancle: ";
	cin >> choice1;
	if (choice1 == -1)
		second_menu(u);

	else
		for (int i = 0; i < users.size(); i++)
		{
			if (choice1 == users[i].userid)
			{
				if (users[i].AQ == false)
					q.showuser = true;
				else
					q.showuser = false;

				exist = true;
				cout << "Enter question ID: ";

				cin >> choice2;
				for (int j = 0; j < questions.size(); j++)
				{
					if (choice2 == questions[j].qid)
					{
						repeated = true;
						break;
					}
				}

				if (repeated)
				{
					cout << "This question already exists.";
					break;
				}

				q.askedid = choice1;
				q.askerid = u.userid;
				q.qid = choice2;
				cout << "Enter Question text: ";

				getline(cin, question);//to avoid last enter
				getline(cin, question);

					q.question_text = question;
				
				
					questions.push_back(q);
					break;
			}
		}

	if(!exist)
	cout << "This user doesn`t exist.";
	

}

void second_menu(User u)
{
	int choice;
	cout << "\nMenu:\n\t\t";
	cout << "1: Print questions to me";
	cout << "\n\t\t2: Print questions from me";
	cout << "\n\t\t3: Answer question";
	cout << "\n\t\t4: Delete question";
	cout << "\n\t\t5: Ask question";
	cout << "\n\t\t6: List system users";
	cout << "\n\t\t7: feed";
	cout << "\n\t\t8: Logout";

	while (true) {
		cout << "\n Enter number in range 1 - 8 :";
		cin >> choice;

		if (choice == 8)
		{
			cout << "\n You have been logged out\n";
			first_menu();
		}

		else if (choice == 1)
			print_questions_to_me(u);

		else if (choice == 2)
			print_questions_from_me(u);

		else if (choice == 3)
			Answer_question(u);

		else if (choice == 4)
			Delete_question(u);

		else if (choice == 5)
			Ask_question(u);

		else if (choice == 6)
			List_system_users();

		else if (choice == 7)
			List_feed();

		else
		{
			cout << "Invalid choice..Try again";
			second_menu(u);
		}

	}
}

void AskFmSystem() {
	first_menu();
}


int main()
{
	AskFmSystem();

	return 0;
}