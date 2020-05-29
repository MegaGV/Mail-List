#include <windows.h>
#include "Mail_List.h"
#include "Contacts.h"


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Contacts_list* list = new Contacts_list("test.txt");
	//Contacts_list* list = new Contacts_list("test2.txt");
	Maillist::Application::Run(gcnew Maillist::Mail_List(list));
	return 0;
}

