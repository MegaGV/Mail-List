#pragma once

#include "Contacts.h"
#include <msclr\marshal_cppstd.h>

namespace Maillist {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Mail_List 摘要
	/// </summary>
	public ref class Mail_List : public System::Windows::Forms::Form
	{
	public:
		Contacts_list* list;
	public:
		ArrayList^ AL = gcnew ArrayList();
	public:
		Mail_List(Contacts_list* list) : list(list)
		{
			InitializeComponent();
			initial_contacts();
		}

		void initial_contacts() {//sort, then clear the form's listbox, finally add contact to the box.
			list->sort_byname();
			this->content_contacts->Items->Clear();
			this->phone_box->Items->Clear();
			for (int i = 0; i < list->size(); i++) {
				String ^str(gcnew System::String(list->get_name(i).c_str()));
				this->content_contacts->Items->Add(str);
			}

			this->nameBox->ResetText();
			this->emailBox->ResetText();
			this->searchBox->ResetText();
		}

		void initial_phone() {//when check the contact. its phone will be added to the listbox
			for (int i = 0; i < list->phone_size(content_contacts->SelectedIndex); i++) {
				String ^str(gcnew System::String(list->get_phone(content_contacts->SelectedIndex, i).c_str()));
				this->phone_box->Items->Add(str);
			}
		}

		void changepage(const int& page) {//there are three pages, use this function to change form controls
			if (page == 1) {
				this->Contact_panel->Visible = false;
				this->btn_search->Visible = true;
				this->btn_new->Visible = true;
				this->btn_save->Visible = false;
				this->nav->Visible = true;
				this->btn_modify->Visible = false;
				initial_contacts();
			}
			else if (page == 2) {
				this->Contact_panel->Visible = true;
				this->btn_search->Visible = false;
				this->btn_new->Visible = false;
				this->btn_save->Visible = true;
				this->nav->Visible = false;
			}
			else if (page == 3) {
				this->Contact_panel->Visible = true;
				this->btn_search->Visible = false;
				this->btn_new->Visible = false;
				this->btn_modify->Visible = true;
				this->btn_del->Visible = true;
				this->nav->Visible = false;
				initial_phone();
			}
		}

		bool check_info() { // when saving a contact, conofirm the information ,if all are right then it can be saved. 
			if (this->nameBox->Text->Length == 0) {
				MessageBox::Show(this, "名字不能为空");
				return false;
			}
			std::string stdemail = msclr::interop::marshal_as<std::string>(emailBox->Text->ToString());
			if (!list->isemail(stdemail)) {
				MessageBox::Show(this, "邮箱有误");
				return false;
			}
			for (int i = 0; i < phone_box->Items->Count; i++) {
				std::string num = msclr::interop::marshal_as<std::string>(phone_box->Items[i]->ToString());
				if (!list->isnum(num)) {
					MessageBox::Show(this, "电话号码有误");
					return false;
				}
			}
			return true;
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~Mail_List()
		{
			list->~Contacts_list();//call the list's deconstructor to save information
			if (components)
			{
				delete components;
			}
		}
	//all form controls
	private: System::Windows::Forms::Label^  title;
	private: System::Windows::Forms::Button^  btn_new;
	private: System::Windows::Forms::SplitContainer^  Form;
	private: System::Windows::Forms::Button^  btn_back;
	private: System::Windows::Forms::ListBox^  content_contacts;
	private: System::Windows::Forms::TextBox^  searchBox;
	private: System::Windows::Forms::Button^  btn_search;
	private: System::Windows::Forms::Button^  btn_save;
	private: System::Windows::Forms::Panel^  Contact_panel;
	private: System::Windows::Forms::TextBox^  nameBox;
	private: System::Windows::Forms::Label^  name_title;
	private: System::Windows::Forms::Label^  email_title;
	private: System::Windows::Forms::TextBox^  emailBox;
	private: System::Windows::Forms::Label^  phone_title;
	private: System::Windows::Forms::Panel^  nav;
	private: System::Windows::Forms::Label^  label27;
	private: System::Windows::Forms::Label^  label26;
	private: System::Windows::Forms::Label^  label25;
	private: System::Windows::Forms::Label^  label24;
	private: System::Windows::Forms::Label^  label23;
	private: System::Windows::Forms::Label^  label22;
	private: System::Windows::Forms::Label^  label21;
	private: System::Windows::Forms::Label^  label20;
	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  btn_new_phone;
	private: System::Windows::Forms::Button^  btn_del;
	private: System::Windows::Forms::Button^  btn_modify;
	private: System::Windows::Forms::ListBox^  phone_box;
	private: System::Windows::Forms::Button^  btn_del_phone;
	private:
	
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要修改
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->title = (gcnew System::Windows::Forms::Label());
			this->btn_new = (gcnew System::Windows::Forms::Button());
			this->Form = (gcnew System::Windows::Forms::SplitContainer());
			this->btn_save = (gcnew System::Windows::Forms::Button());
			this->btn_modify = (gcnew System::Windows::Forms::Button());
			this->btn_back = (gcnew System::Windows::Forms::Button());
			this->nav = (gcnew System::Windows::Forms::Panel());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->btn_search = (gcnew System::Windows::Forms::Button());
			this->Contact_panel = (gcnew System::Windows::Forms::Panel());
			this->btn_del_phone = (gcnew System::Windows::Forms::Button());
			this->phone_box = (gcnew System::Windows::Forms::ListBox());
			this->btn_del = (gcnew System::Windows::Forms::Button());
			this->btn_new_phone = (gcnew System::Windows::Forms::Button());
			this->phone_title = (gcnew System::Windows::Forms::Label());
			this->emailBox = (gcnew System::Windows::Forms::TextBox());
			this->email_title = (gcnew System::Windows::Forms::Label());
			this->nameBox = (gcnew System::Windows::Forms::TextBox());
			this->name_title = (gcnew System::Windows::Forms::Label());
			this->searchBox = (gcnew System::Windows::Forms::TextBox());
			this->content_contacts = (gcnew System::Windows::Forms::ListBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Form))->BeginInit();
			this->Form->Panel1->SuspendLayout();
			this->Form->Panel2->SuspendLayout();
			this->Form->SuspendLayout();
			this->nav->SuspendLayout();
			this->Contact_panel->SuspendLayout();
			this->SuspendLayout();
			// 
			// title
			// 
			this->title->AutoSize = true;
			this->title->Font = (gcnew System::Drawing::Font(L"宋体", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->title->Location = System::Drawing::Point(121, 20);
			this->title->Name = L"title";
			this->title->Size = System::Drawing::Size(137, 40);
			this->title->TabIndex = 0;
			this->title->Text = L"联系人";
			// 
			// btn_new
			// 
			this->btn_new->Location = System::Drawing::Point(278, 20);
			this->btn_new->Name = L"btn_new";
			this->btn_new->Size = System::Drawing::Size(90, 40);
			this->btn_new->TabIndex = 1;
			this->btn_new->Text = L"新建";
			this->btn_new->UseVisualStyleBackColor = true;
			this->btn_new->Click += gcnew System::EventHandler(this, &Mail_List::btn_new_Click);
			// 
			// Form
			// 
			this->Form->Location = System::Drawing::Point(0, 0);
			this->Form->Name = L"Form";
			this->Form->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// Form.Panel1
			// 
			this->Form->Panel1->Controls->Add(this->btn_save);
			this->Form->Panel1->Controls->Add(this->btn_modify);
			this->Form->Panel1->Controls->Add(this->btn_new);
			this->Form->Panel1->Controls->Add(this->btn_back);
			this->Form->Panel1->Controls->Add(this->title);
			// 
			// Form.Panel2
			// 
			this->Form->Panel2->Controls->Add(this->nav);
			this->Form->Panel2->Controls->Add(this->btn_search);
			this->Form->Panel2->Controls->Add(this->Contact_panel);
			this->Form->Panel2->Controls->Add(this->searchBox);
			this->Form->Panel2->Controls->Add(this->content_contacts);
			this->Form->Size = System::Drawing::Size(380, 700);
			this->Form->SplitterDistance = 71;
			this->Form->TabIndex = 3;
			// 
			// btn_save
			// 
			this->btn_save->Location = System::Drawing::Point(279, 20);
			this->btn_save->Name = L"btn_save";
			this->btn_save->Size = System::Drawing::Size(89, 40);
			this->btn_save->TabIndex = 3;
			this->btn_save->Text = L"保存";
			this->btn_save->UseVisualStyleBackColor = true;
			this->btn_save->Visible = false;
			this->btn_save->Click += gcnew System::EventHandler(this, &Mail_List::btn_save_Click);
			// 
			// btn_modify
			// 
			this->btn_modify->Location = System::Drawing::Point(278, 20);
			this->btn_modify->Name = L"btn_modify";
			this->btn_modify->Size = System::Drawing::Size(89, 40);
			this->btn_modify->TabIndex = 5;
			this->btn_modify->Text = L"保存修改";
			this->btn_modify->UseVisualStyleBackColor = true;
			this->btn_modify->Visible = false;
			this->btn_modify->Click += gcnew System::EventHandler(this, &Mail_List::btn_modify_Click);
			// 
			// btn_back
			// 
			this->btn_back->Location = System::Drawing::Point(12, 20);
			this->btn_back->Name = L"btn_back";
			this->btn_back->Size = System::Drawing::Size(90, 40);
			this->btn_back->TabIndex = 2;
			this->btn_back->Text = L"返回";
			this->btn_back->UseVisualStyleBackColor = true;
			this->btn_back->Click += gcnew System::EventHandler(this, &Mail_List::btn_back_Click);
			// 
			// nav
			// 
			this->nav->BackColor = System::Drawing::SystemColors::Window;
			this->nav->Controls->Add(this->label27);
			this->nav->Controls->Add(this->label26);
			this->nav->Controls->Add(this->label25);
			this->nav->Controls->Add(this->label24);
			this->nav->Controls->Add(this->label23);
			this->nav->Controls->Add(this->label22);
			this->nav->Controls->Add(this->label21);
			this->nav->Controls->Add(this->label20);
			this->nav->Controls->Add(this->label19);
			this->nav->Controls->Add(this->label18);
			this->nav->Controls->Add(this->label17);
			this->nav->Controls->Add(this->label16);
			this->nav->Controls->Add(this->label15);
			this->nav->Controls->Add(this->label14);
			this->nav->Controls->Add(this->label13);
			this->nav->Controls->Add(this->label12);
			this->nav->Controls->Add(this->label11);
			this->nav->Controls->Add(this->label10);
			this->nav->Controls->Add(this->label9);
			this->nav->Controls->Add(this->label8);
			this->nav->Controls->Add(this->label7);
			this->nav->Controls->Add(this->label6);
			this->nav->Controls->Add(this->label5);
			this->nav->Controls->Add(this->label4);
			this->nav->Controls->Add(this->label3);
			this->nav->Controls->Add(this->label2);
			this->nav->Controls->Add(this->label1);
			this->nav->Location = System::Drawing::Point(337, 56);
			this->nav->Name = L"nav";
			this->nav->Size = System::Drawing::Size(31, 550);
			this->nav->TabIndex = 3;
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->Location = System::Drawing::Point(6, 520);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(15, 15);
			this->label27->TabIndex = 26;
			this->label27->Text = L"Z";
			this->label27->Click += gcnew System::EventHandler(this, &Mail_List::label27_Click);
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Location = System::Drawing::Point(6, 500);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(15, 15);
			this->label26->TabIndex = 25;
			this->label26->Text = L"Y";
			this->label26->Click += gcnew System::EventHandler(this, &Mail_List::label26_Click);
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Location = System::Drawing::Point(6, 480);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(15, 15);
			this->label25->TabIndex = 24;
			this->label25->Text = L"X";
			this->label25->Click += gcnew System::EventHandler(this, &Mail_List::label25_Click);
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Location = System::Drawing::Point(6, 460);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(15, 15);
			this->label24->TabIndex = 23;
			this->label24->Text = L"W";
			this->label24->Click += gcnew System::EventHandler(this, &Mail_List::label24_Click);
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Location = System::Drawing::Point(6, 440);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(15, 15);
			this->label23->TabIndex = 22;
			this->label23->Text = L"V";
			this->label23->Click += gcnew System::EventHandler(this, &Mail_List::label23_Click);
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Location = System::Drawing::Point(6, 420);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(15, 15);
			this->label22->TabIndex = 21;
			this->label22->Text = L"U";
			this->label22->Click += gcnew System::EventHandler(this, &Mail_List::label22_Click);
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Location = System::Drawing::Point(6, 400);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(15, 15);
			this->label21->TabIndex = 20;
			this->label21->Text = L"T";
			this->label21->Click += gcnew System::EventHandler(this, &Mail_List::label21_Click);
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(6, 380);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(15, 15);
			this->label20->TabIndex = 19;
			this->label20->Text = L"S";
			this->label20->Click += gcnew System::EventHandler(this, &Mail_List::label20_Click);
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(6, 360);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(15, 15);
			this->label19->TabIndex = 18;
			this->label19->Text = L"R";
			this->label19->Click += gcnew System::EventHandler(this, &Mail_List::label19_Click);
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(6, 340);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(15, 15);
			this->label18->TabIndex = 17;
			this->label18->Text = L"Q";
			this->label18->Click += gcnew System::EventHandler(this, &Mail_List::label18_Click);
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(6, 320);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(15, 15);
			this->label17->TabIndex = 16;
			this->label17->Text = L"P";
			this->label17->Click += gcnew System::EventHandler(this, &Mail_List::label17_Click);
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(6, 300);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(15, 15);
			this->label16->TabIndex = 15;
			this->label16->Text = L"O";
			this->label16->Click += gcnew System::EventHandler(this, &Mail_List::label16_Click);
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(6, 280);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(15, 15);
			this->label15->TabIndex = 14;
			this->label15->Text = L"N";
			this->label15->Click += gcnew System::EventHandler(this, &Mail_List::label15_Click);
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(6, 260);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(15, 15);
			this->label14->TabIndex = 13;
			this->label14->Text = L"M";
			this->label14->Click += gcnew System::EventHandler(this, &Mail_List::label14_Click);
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(6, 240);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(15, 15);
			this->label13->TabIndex = 12;
			this->label13->Text = L"L";
			this->label13->Click += gcnew System::EventHandler(this, &Mail_List::label13_Click);
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(6, 220);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(15, 15);
			this->label12->TabIndex = 11;
			this->label12->Text = L"K";
			this->label12->Click += gcnew System::EventHandler(this, &Mail_List::label12_Click);
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(6, 200);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(15, 15);
			this->label11->TabIndex = 10;
			this->label11->Text = L"J";
			this->label11->Click += gcnew System::EventHandler(this, &Mail_List::label11_Click);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(6, 180);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(15, 15);
			this->label10->TabIndex = 9;
			this->label10->Text = L"I";
			this->label10->Click += gcnew System::EventHandler(this, &Mail_List::label10_Click);
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(6, 160);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(15, 15);
			this->label9->TabIndex = 8;
			this->label9->Text = L"H";
			this->label9->Click += gcnew System::EventHandler(this, &Mail_List::label9_Click);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(6, 140);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(15, 15);
			this->label8->TabIndex = 7;
			this->label8->Text = L"G";
			this->label8->Click += gcnew System::EventHandler(this, &Mail_List::label8_Click);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(6, 120);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(15, 15);
			this->label7->TabIndex = 6;
			this->label7->Text = L"F";
			this->label7->Click += gcnew System::EventHandler(this, &Mail_List::label7_Click);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(6, 100);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(15, 15);
			this->label6->TabIndex = 5;
			this->label6->Text = L"E";
			this->label6->Click += gcnew System::EventHandler(this, &Mail_List::label6_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(6, 80);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(15, 15);
			this->label5->TabIndex = 4;
			this->label5->Text = L"D";
			this->label5->Click += gcnew System::EventHandler(this, &Mail_List::label5_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(6, 60);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(15, 15);
			this->label4->TabIndex = 3;
			this->label4->Text = L"C";
			this->label4->Click += gcnew System::EventHandler(this, &Mail_List::label4_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(6, 40);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(15, 15);
			this->label3->TabIndex = 2;
			this->label3->Text = L"B";
			this->label3->Click += gcnew System::EventHandler(this, &Mail_List::label3_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(6, 20);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(15, 15);
			this->label2->TabIndex = 1;
			this->label2->Text = L"A";
			this->label2->Click += gcnew System::EventHandler(this, &Mail_List::label2_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(6, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(15, 15);
			this->label1->TabIndex = 0;
			this->label1->Text = L"#";
			this->label1->Click += gcnew System::EventHandler(this, &Mail_List::label1_Click);
			// 
			// btn_search
			// 
			this->btn_search->Location = System::Drawing::Point(12, 18);
			this->btn_search->Name = L"btn_search";
			this->btn_search->Size = System::Drawing::Size(75, 25);
			this->btn_search->TabIndex = 2;
			this->btn_search->Text = L"搜索";
			this->btn_search->UseVisualStyleBackColor = true;
			this->btn_search->Click += gcnew System::EventHandler(this, &Mail_List::btn_search_Click);
			// 
			// Contact_panel
			// 
			this->Contact_panel->Controls->Add(this->btn_del_phone);
			this->Contact_panel->Controls->Add(this->phone_box);
			this->Contact_panel->Controls->Add(this->btn_del);
			this->Contact_panel->Controls->Add(this->btn_new_phone);
			this->Contact_panel->Controls->Add(this->phone_title);
			this->Contact_panel->Controls->Add(this->emailBox);
			this->Contact_panel->Controls->Add(this->email_title);
			this->Contact_panel->Controls->Add(this->nameBox);
			this->Contact_panel->Controls->Add(this->name_title);
			this->Contact_panel->Location = System::Drawing::Point(1, 3);
			this->Contact_panel->Name = L"Contact_panel";
			this->Contact_panel->Size = System::Drawing::Size(376, 621);
			this->Contact_panel->TabIndex = 4;
			this->Contact_panel->Visible = false;
			// 
			// btn_del_phone
			// 
			this->btn_del_phone->Location = System::Drawing::Point(9, 203);
			this->btn_del_phone->Name = L"btn_del_phone";
			this->btn_del_phone->Size = System::Drawing::Size(89, 42);
			this->btn_del_phone->TabIndex = 8;
			this->btn_del_phone->Text = L"删除电话";
			this->btn_del_phone->UseVisualStyleBackColor = true;
			this->btn_del_phone->Click += gcnew System::EventHandler(this, &Mail_List::btn_del_phone_Click);
			// 
			// phone_box
			// 
			this->phone_box->Font = (gcnew System::Drawing::Font(L"宋体", 10));
			this->phone_box->FormattingEnabled = true;
			this->phone_box->ItemHeight = 17;
			this->phone_box->Location = System::Drawing::Point(104, 117);
			this->phone_box->Name = L"phone_box";
			this->phone_box->Size = System::Drawing::Size(228, 140);
			this->phone_box->TabIndex = 7;
			this->phone_box->DoubleClick += gcnew System::EventHandler(this, &Mail_List::phone_box_DoubleClick);
			// 
			// btn_del
			// 
			this->btn_del->ForeColor = System::Drawing::Color::Red;
			this->btn_del->Location = System::Drawing::Point(14, 581);
			this->btn_del->Name = L"btn_del";
			this->btn_del->Size = System::Drawing::Size(75, 28);
			this->btn_del->TabIndex = 6;
			this->btn_del->Text = L"删除";
			this->btn_del->UseVisualStyleBackColor = true;
			this->btn_del->Visible = false;
			this->btn_del->Click += gcnew System::EventHandler(this, &Mail_List::btn_del_Click);
			// 
			// btn_new_phone
			// 
			this->btn_new_phone->Location = System::Drawing::Point(9, 157);
			this->btn_new_phone->Name = L"btn_new_phone";
			this->btn_new_phone->Size = System::Drawing::Size(89, 42);
			this->btn_new_phone->TabIndex = 5;
			this->btn_new_phone->Text = L"添加电话";
			this->btn_new_phone->UseVisualStyleBackColor = true;
			this->btn_new_phone->Click += gcnew System::EventHandler(this, &Mail_List::btn_new_phone_Click);
			// 
			// phone_title
			// 
			this->phone_title->AutoSize = true;
			this->phone_title->Location = System::Drawing::Point(40, 117);
			this->phone_title->Name = L"phone_title";
			this->phone_title->Size = System::Drawing::Size(37, 15);
			this->phone_title->TabIndex = 4;
			this->phone_title->Text = L"电话";
			// 
			// emailBox
			// 
			this->emailBox->Location = System::Drawing::Point(104, 68);
			this->emailBox->Name = L"emailBox";
			this->emailBox->Size = System::Drawing::Size(229, 25);
			this->emailBox->TabIndex = 3;
			// 
			// email_title
			// 
			this->email_title->AutoSize = true;
			this->email_title->Location = System::Drawing::Point(37, 71);
			this->email_title->Name = L"email_title";
			this->email_title->Size = System::Drawing::Size(37, 15);
			this->email_title->TabIndex = 2;
			this->email_title->Text = L"邮箱";
			// 
			// nameBox
			// 
			this->nameBox->Location = System::Drawing::Point(104, 28);
			this->nameBox->Name = L"nameBox";
			this->nameBox->Size = System::Drawing::Size(229, 25);
			this->nameBox->TabIndex = 1;
			// 
			// name_title
			// 
			this->name_title->AutoSize = true;
			this->name_title->Location = System::Drawing::Point(37, 31);
			this->name_title->Name = L"name_title";
			this->name_title->Size = System::Drawing::Size(37, 15);
			this->name_title->TabIndex = 0;
			this->name_title->Text = L"姓名";
			// 
			// searchBox
			// 
			this->searchBox->Location = System::Drawing::Point(99, 18);
			this->searchBox->Name = L"searchBox";
			this->searchBox->Size = System::Drawing::Size(269, 25);
			this->searchBox->TabIndex = 1;
			// 
			// content_contacts
			// 
			this->content_contacts->Font = (gcnew System::Drawing::Font(L"宋体", 15));
			this->content_contacts->FormattingEnabled = true;
			this->content_contacts->ItemHeight = 25;
			this->content_contacts->Location = System::Drawing::Point(12, 54);
			this->content_contacts->Name = L"content_contacts";
			this->content_contacts->Size = System::Drawing::Size(356, 554);
			this->content_contacts->TabIndex = 0;
			this->content_contacts->DoubleClick += gcnew System::EventHandler(this, &Mail_List::content_contacts_DoubleClick);
			// 
			// Mail_List
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(380, 700);
			this->Controls->Add(this->Form);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"Mail_List";
			this->Text = L"Mail_List";
			this->Form->Panel1->ResumeLayout(false);
			this->Form->Panel1->PerformLayout();
			this->Form->Panel2->ResumeLayout(false);
			this->Form->Panel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Form))->EndInit();
			this->Form->ResumeLayout(false);
			this->nav->ResumeLayout(false);
			this->nav->PerformLayout();
			this->Contact_panel->ResumeLayout(false);
			this->Contact_panel->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
private: System::Void btn_new_Click(System::Object^  sender, System::EventArgs^  e) {
	changepage(2);
}
private: System::Void btn_back_Click(System::Object^  sender, System::EventArgs^  e) {
	changepage(1);
}
private: System::Void btn_search_Click(System::Object^  sender, System::EventArgs^  e) {
	//transform the input to std::string and use Contact_list's function to search
	std::string stdsearch = msclr::interop::marshal_as<std::string>(searchBox->Text->ToString());
	std::vector<int> result = list->search(stdsearch);

	this->content_contacts->Items->Clear();
	for (int i = 0; i < result.size(); i++) {
		String ^str(gcnew System::String(list->get_name(result[i]).c_str()));
		this->content_contacts->Items->Add(str);
	}
}
private: System::Void btn_save_Click(System::Object^  sender, System::EventArgs^  e) {
	if (check_info()) {//if the information is right, add the new contact and update the form
		std::string stdemail = msclr::interop::marshal_as<std::string>(emailBox->Text->ToString());
		std::string stdname = msclr::interop::marshal_as<std::string>(nameBox->Text->ToString());
		if (stdemail != "")
			list->add(stdname, stdemail);
		else
			list->add(stdname);
		for (int i = 0; i < phone_box->Items->Count; i++) {
			std::string num = msclr::interop::marshal_as<std::string>(phone_box->Items[i]->ToString());
			list->add_phone(list->size() - 1, num);
		}
		MessageBox::Show(this, "新建联系人成功");
		changepage(1);
	}
}
private: System::Void phone_box_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
	if (phone_box->SelectedIndex != -1) {//when doubleClick can modify the phone exist
		phone_box->Items[phone_box->SelectedIndex] = Microsoft::VisualBasic::Interaction::InputBox("", "修改电话号码", phone_box->Items[phone_box->SelectedIndex]->ToString(), 0, 0);
	}
}
private: System::Void btn_del_phone_Click(System::Object^  sender, System::EventArgs^  e) {
	if (phone_box->SelectedIndex != -1)//used to delete selected phone 
		this->phone_box->Items->RemoveAt(phone_box->SelectedIndex);
}
private: System::Void btn_new_phone_Click(System::Object^  sender, System::EventArgs^  e) {
	String^ s = Microsoft::VisualBasic::Interaction::InputBox("", "新增电话号码", "", 0, 0);
	if(s != "")//if the phone is changed to empty, then it will not be saved.
		phone_box->Items->Add (s);
}
private: System::Void btn_del_Click(System::Object^  sender, System::EventArgs^  e) {//used to delete the contact, then the form will be upadated.
	System::Windows::Forms::DialogResult dr = MessageBox::Show("确定要删除此联系人吗？", "", MessageBoxButtons::OKCancel);
	if (dr == System::Windows::Forms::DialogResult::OK) {
		list->del(content_contacts->SelectedIndex);
		changepage(1);
	}
}
private: System::Void content_contacts_DoubleClick(System::Object^  sender, System::EventArgs^  e) {//when doubleclick a contact, can modify and check its information
	String ^sname(gcnew System::String(list->get_name(content_contacts->SelectedIndex).c_str()));
	this->nameBox->Text = sname;
	String ^semail(gcnew System::String(list->get_email(content_contacts->SelectedIndex).c_str()));
	this->emailBox->Text = semail;

	changepage(3);
}
private: System::Void btn_modify_Click(System::Object^  sender, System::EventArgs^  e) {
	if (check_info()) {
		std::string stdemail = msclr::interop::marshal_as<std::string>(emailBox->Text->ToString());
		std::string stdname = msclr::interop::marshal_as<std::string>(nameBox->Text->ToString());
		list->set_name(content_contacts->SelectedIndex, stdname);
		list->set_email(content_contacts->SelectedIndex, stdemail);
		while (list->phone_size(content_contacts->SelectedIndex)) {
			list->del_phone(content_contacts->SelectedIndex, 0);
		}
		for (int i = 0; i < phone_box->Items->Count; i++) {
			std::string num = msclr::interop::marshal_as<std::string>(phone_box->Items[i]->ToString());
			list->add_phone(content_contacts->SelectedIndex, num);
		}

		MessageBox::Show(this, "保存成功");
		changepage(1);
	}
}

//
// follows are used for nav labels to find their position.
//
private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
	if (content_contacts->Items->Count >= 0)
		content_contacts->SelectedIndex = 0;
}
private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
	content_contacts->SelectedIndex = list->jump_bynav("阿");
}
private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
	content_contacts->SelectedIndex = list->jump_bynav("八");
}
private: System::Void label4_Click(System::Object^  sender, System::EventArgs^  e) {
	content_contacts->SelectedIndex = list->jump_bynav("嚓");
}
private: System::Void label5_Click(System::Object^  sender, System::EventArgs^  e) {
	content_contacts->SelectedIndex = list->jump_bynav("搭");
}
private: System::Void label6_Click(System::Object^  sender, System::EventArgs^  e) {
	content_contacts->SelectedIndex = list->jump_bynav("婀");
}
private: System::Void label7_Click(System::Object^  sender, System::EventArgs^  e) {
	content_contacts->SelectedIndex = list->jump_bynav("发");
}
private: System::Void label8_Click(System::Object^  sender, System::EventArgs^  e) {
	content_contacts->SelectedIndex = list->jump_bynav("伽");
}
private: System::Void label9_Click(System::Object^  sender, System::EventArgs^  e) {
	content_contacts->SelectedIndex = list->jump_bynav("哈");
}
private: System::Void label10_Click(System::Object^  sender, System::EventArgs^  e) {
	content_contacts->SelectedIndex = list->jump_bynav("哈");//I
}
private: System::Void label11_Click(System::Object^  sender, System::EventArgs^  e) {
	content_contacts->SelectedIndex = list->jump_bynav("机");
}
private: System::Void label12_Click(System::Object^  sender, System::EventArgs^  e) {
	content_contacts->SelectedIndex = list->jump_bynav("咖");
}
private: System::Void label13_Click(System::Object^  sender, System::EventArgs^  e) {
	content_contacts->SelectedIndex = list->jump_bynav("拉");
}
private: System::Void label14_Click(System::Object^  sender, System::EventArgs^  e) {
	content_contacts->SelectedIndex = list->jump_bynav("妈");
}
private: System::Void label15_Click(System::Object^  sender, System::EventArgs^  e) {
	content_contacts->SelectedIndex = list->jump_bynav("拿");
}
private: System::Void label16_Click(System::Object^  sender, System::EventArgs^  e) {
	content_contacts->SelectedIndex = list->jump_bynav("噢");
}
private: System::Void label17_Click(System::Object^  sender, System::EventArgs^  e) {
	content_contacts->SelectedIndex = list->jump_bynav("趴");
}
private: System::Void label18_Click(System::Object^  sender, System::EventArgs^  e) {
	content_contacts->SelectedIndex = list->jump_bynav("七");
}
private: System::Void label19_Click(System::Object^  sender, System::EventArgs^  e) {
	content_contacts->SelectedIndex = list->jump_bynav("然");
}
private: System::Void label20_Click(System::Object^  sender, System::EventArgs^  e) {
	content_contacts->SelectedIndex = list->jump_bynav("撒");
}
private: System::Void label21_Click(System::Object^  sender, System::EventArgs^  e) {
	content_contacts->SelectedIndex = list->jump_bynav("他");
}
private: System::Void label22_Click(System::Object^  sender, System::EventArgs^  e) {
	content_contacts->SelectedIndex = list->jump_bynav("他");//U
}
private: System::Void label23_Click(System::Object^  sender, System::EventArgs^  e) {
	content_contacts->SelectedIndex = list->jump_bynav("他");//V
}
private: System::Void label24_Click(System::Object^  sender, System::EventArgs^  e) {
	content_contacts->SelectedIndex = list->jump_bynav("挖");
}
private: System::Void label25_Click(System::Object^  sender, System::EventArgs^  e) {
	content_contacts->SelectedIndex = list->jump_bynav("西");
}
private: System::Void label26_Click(System::Object^  sender, System::EventArgs^  e) {
	content_contacts->SelectedIndex = list->jump_bynav("呀");
}
private: System::Void label27_Click(System::Object^  sender, System::EventArgs^  e) {
	content_contacts->SelectedIndex = list->jump_bynav("匝");
}
};
}
