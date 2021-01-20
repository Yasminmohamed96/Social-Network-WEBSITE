#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include<list>
#include "Headers.h"
#include<tinyxml2.h>
#include <cstdlib>
#include <conio.h>
#include<map>
#include<set>
#include <algorithm>
#include <functional>

const int unfriend = 0;
const int friends = 1;
int COUNT = 0;
int P_ID=0;
int FLAG=0;
using namespace std;
using namespace tinyxml2;
	
XMLDocument xmlDoc;
XMLNode * pUser = xmlDoc.NewElement("USER");
XMLElement *pFriends=xmlDoc.NewElement("Friends");
XMLElement *pLikedPosts=xmlDoc.NewElement("LikedPosts");
XMLDocument AdminXML;
XMLDocument newTemp;
XMLDocument temp;
void saveXML(int iduser)
{

	string id=to_string(iduser)+".xml";
	const char * idch = id.c_str();
	xmlDoc.SaveFile(idch);
}

void saveXMLtemp(int iduser)
{

	string id=to_string(iduser)+".xml";
	const char * idch = id.c_str();
	temp.SaveFile(idch);
}

void saveXMLNewtemp(int iduser)
{

	string id=to_string(iduser)+".xml";
	const char * idch = id.c_str();
	newTemp.SaveFile(idch);
}
int GraphType::numOfUsers() {
	return numVertices;
}
void GraphType::ListAll() {
	for (int i = 0; i<numVertices; i++)
		std::cout <<"               "<< vertices[i].F_Name << " " << vertices[i].L_Name << endl;
}

// corosponding to add friend 
void GraphType::AddVertex(USER vertex) {

	vertices.push_back( vertex); // 3la hasab dorha eh fel trteb 
	for (int i = 0; i < numVertices; i++) {
		edges[numVertices][i] = unfriend; // lesa kol el col bt3tha bel zeros 
		edges[i][numVertices] = unfriend; // wel rows kman b zeros 
	}
	numVertices++; // increase counter of users in graph 

}



int GraphType::IndexIs(USER vertex)
// ana hadelo vertex mo3yna ygble el index bt3ha fel matrix 
{
	int index = 0;

	while (!(vertex.Email == vertices[index].Email))
		index++;
	return index;
}

string GraphType::VertexFromIndex(int index) {
	return vertices[index].F_Name+ " "+vertices[index].L_Name;
}
USER GraphType::UserFromIndex(int index) {
	return vertices[index];
}

//corosponding to remove user (admin only)
void GraphType::RemoveVertex(USER vertex)
{
	int rowToDelete = IndexIs(vertex);
	for (int i = 0; i < numVertices; i++) {
		if (i == rowToDelete)
			edges.erase(edges.begin() + rowToDelete);
	}
	numVertices--;
}

void GraphType::AddEdge(USER fromVertex, USER toVertex)
{  // hb3tlo el etnen eli 3wza ma benhom friendship 
	int row;
	int col;
	row = IndexIs(fromVertex);
	col = IndexIs(toVertex);
	edges[row][col] = friends;
}

void GraphType::RemoveEdge(USER fromVertex, USER toVertex)
{  // hb3tlo el etnen eli 3wza ma benhom friendship 
	int row;
	int col;
	row = IndexIs(fromVertex);
	col = IndexIs(toVertex);
	edges[row][col] = unfriend;
}


bool GraphType::IfFriend(USER fromVertex, USER toVertex)
{   // byshof hal had w had friends wla la 
	int row;
	int col;
	row = IndexIs(fromVertex);
	col = IndexIs(toVertex);
	if (edges[row][col])
		return true;
	else
		return false;
}

// List friends of one vertex 
void GraphType::ListFriends(USER vertex) {
	int row = IndexIs(vertex);
	for (int i = 0; i<edges.size(); i++)
	{
		if (edges[row][i] == 1)
			std::cout <<"               "<<VertexFromIndex(i) << endl;
	}

}

bool GraphType::IfUserexist(string email, string password) {
	for (int i = 0; i < numVertices; i++)
	{
		if (vertices[i].Email == email)
			if (vertices[i].Password == password)
				return true;
			else
			{
				std::cout << "               Password is incorrect !               " << endl;
			}
	}
	return false;

}

USER GraphType::ReturnUser(string email) {
	for (int i = 0; i < numVertices; i++)
	{
		if (vertices[i].Email == email)
			return vertices[i];

	}
}



void GraphType::ViewUserwithName(USER user, string name) {


	for (int i = 0; i < numVertices; i++)
	{
		if (vertices[i].F_Name == name)
		{
			cout <<"               First Search Result : "<< vertices[i].F_Name << " " << vertices[i].L_Name << endl;
redirect:			cout << "               To Add " << vertices[i].F_Name << " " << vertices[i].L_Name << "  As a Friend Type add  \n               If You want to browse next type next " << endl;
					cout << "               To view Profile of" << vertices[i].F_Name << vertices[i].L_Name << " type view" << endl
			  << "               To Exit Type Exit"<<endl
			  << "               To remove Your Friend Type remove"<<endl;
			string action;
			cin >> action;
			if (action == "add") {

				if(IfFriend(user,vertices[i]))
				{ cout<<"               You Are Already Friends !               "<<endl;
				goto redirect;
				
				}
				else {
								AddEdge(user, vertices[i]);
				if (FLAG)
				
				{ 
				string verticesID=to_string(vertices[i].User_ID);
				const char * idnew = verticesID.c_str();
				XMLElement *Pid=xmlDoc.NewElement("ID");
				Pid->SetText(idnew);
				pFriends->InsertEndChild(Pid);
				pUser->InsertEndChild(pFriends);
				saveXML(user.User_ID);
				}

				else {
				string tempID=to_string(user.User_ID)+".xml";
				const char * tempid = tempID.c_str();
				newTemp.LoadFile(tempid);
				XMLNode * pos = newTemp.FirstChildElement("USER")->FirstChildElement("Friends");
				XMLElement *Pidtemp=newTemp.NewElement("ID");
				  

				Pidtemp->SetText(vertices[i].User_ID);
				pos->InsertEndChild(Pidtemp);
				saveXMLNewtemp(user.User_ID);
				}
				//Saving the id of logged in user 3nd vertices[i]
				string tempID=to_string(vertices[i].User_ID)+".xml";
				const char * tempid = tempID.c_str();
				temp.LoadFile(tempid);
				XMLNode * pos = temp.FirstChildElement("USER")->FirstChildElement("Friends");
				XMLElement *Pidtemp=temp.NewElement("ID");
				Pidtemp->SetText(user.User_ID);
				pos->InsertEndChild(Pidtemp);
				saveXMLtemp(vertices[i].User_ID);
				cout<<"               Congratulations ! You are Friends with  "<<vertices[i].F_Name<< " " <<vertices[i].L_Name<<" !" <<endl;				
				goto redirect;
				}

			}
			else if(action == "view") {
				if(vertices[i].User_Posts.size()==0)
					cout<<"               This Profile is Still Empty !"<<endl;
				else
				{   char c;
					user.View_Other_Users_Posts(vertices[i],user.User_ID,c);}
			}
			if (action == "next")
				continue;
			if(action =="remove")
			{  if(IfFriend(user,vertices[i])){
				RemoveEdge(user,vertices[i]);
				if(FLAG){
					XMLElement *check=xmlDoc.FirstChildElement("USER")->FirstChildElement("Friends")->FirstChildElement("ID");
					while (check != nullptr)
					{
						if(atoi(check->GetText())==vertices[i].User_ID){
							xmlDoc.DeleteNode(check);
							break;
						
						}
						check=check->NextSiblingElement();
					}
					saveXML(user.User_ID);
				}
				else {
				string tempID=to_string(user.User_ID)+".xml";
				const char * tempid = tempID.c_str();
				newTemp.LoadFile(tempid);
				XMLElement *check=newTemp.FirstChildElement("USER")->FirstChildElement("Friends")->FirstChildElement("ID");
					while (check != nullptr)
					{
						if(atoi(check->GetText())==vertices[i].User_ID){
							newTemp.DeleteNode(check);
							break;
						
						}
												check=check->NextSiblingElement();
					}				
					saveXMLNewtemp(user.User_ID);
				}

				cout<<"               You Removed Your Friend ! "<<endl;
				string tempID=to_string(vertices[i].User_ID)+".xml";
				const char * tempid = tempID.c_str();
				newTemp.LoadFile(tempid);
				XMLElement *check=newTemp.FirstChildElement("USER")->FirstChildElement("Friends")->FirstChildElement("ID");
					while (check != nullptr)
					{
						if(atoi(check->GetText())==user.User_ID){
							newTemp.DeleteNode(check);
							break;
						
						}

						check=check->NextSiblingElement();
					}				
					saveXMLNewtemp(vertices[i].User_ID);
					goto redirect;
			}
			else {cout<<"               You are Not Even Friends !"<<endl;}
			
			}
			if (action == "Exit")
				break;
		}

	}
}

int GraphType::countEdged(USER vertex){

	int row = IndexIs(vertex);
	int count = 0;
	for (int i = 0; i < numVertices; i++)
	{
		if (edges[row][i] == 1) {
			count++;
		}
	}
	return count;

}

USER::USER()
{
	User_ID = NULL;
	F_Name = "";
	L_Name = "";
	DateOfBirth = "";
	Password = "";
	Email = "";
	Gender = "";
	User_ID = 1;
}

void USER::edit_profile(string f_Name, string l_Name, string Date_Birth, string email, string gender)
{
	F_Name = f_Name;
	L_Name = l_Name;
	DateOfBirth = Date_Birth;
	Email = email;
	Gender = gender;
}
void USER::Change_Password(string NewPassword)
{
	Password = NewPassword;
}
void USER::Create_Post(Posts NewPost)
{
	User_Posts.push_back(NewPost);
}

void USER::Edit_Post(int index, Posts New_Edit)
{
	User_Posts[index] = New_Edit;
}
void USER::Delete_Post(int index)
{
	Posts new_edit1;
	char	Input;
	if (User_Posts.size() > 2) {
		 User_Posts.erase(User_Posts.begin()+index); 
	}
	else if (User_Posts.size() == 1)
	{
		User_Posts.resize(0);
	}
	else if (User_Posts.size() == 2)
	{

		if (index == 0) { User_Posts.erase(User_Posts.begin()); }
		else if (index == 1) { User_Posts.erase(User_Posts.end()); }
		
	}
}

void USER::View_User_Posts()
{
	bool liked_post = false;
	//pUser->InsertEndChild(pLikedPosts);
	char Input = 'F';
	Posts new_edit;

	int i = 0; int flag = 0;
	//while (Input != 'X'){
		while (Input != 'X' && i < User_Posts.size()) {
			//view first post
			if (Input == 'F')
			{
				std::cout<< "               "<< User_Posts[0].body << endl;


				//check liking part
				//must know index of the current user
				for (auto j = LikedPosts.begin(); j != LikedPosts.end(); j++)
				{
					if (*j == User_Posts[0].id)
					{
						std::cout << "               You Liked this post !               " << endl;
						flag = 1;
						break;
					}
				}

				
				if (flag == 0) { cout << "               To Like this post ENter L" << endl; }
				cout << "               To Edit YOUR post Enter E" << endl
					<< "               To delete you post Enter D" << endl
				    << "               To Exit Enter X" << endl;
				if (i != User_Posts.size() - 1) { cout << "               To see the Next post Enter N" << endl; }
				if (flag == 1)
				{
					cout << "               To unlike the post Enter d" << endl;
				}

				std::cin >> Input;

				if (Input == 'L')
				{
						string postID=to_string(User_Posts[i].id);
						const char * post_ID = postID.c_str();
			if(FLAG){
			XMLElement *pID=xmlDoc.NewElement("ID");
			pID->SetText(post_ID);
			pLikedPosts->InsertEndChild(pID);
			pUser->LinkEndChild(pLikedPosts);
			saveXML(User_ID);}
			else{
				string tempID=to_string(User_ID)+".xml";
				const char * tempid = tempID.c_str();
				newTemp.LoadFile(tempid);
				XMLNode * pos = newTemp.FirstChildElement("USER")->FirstChildElement("LikedPosts");
				XMLElement *Pidtemp=newTemp.NewElement("ID");
				Pidtemp->SetText(User_Posts[i].id);
				pos->InsertEndChild(Pidtemp);
				saveXMLNewtemp(User_ID);
			
			}
				LikedPosts.insert(P_ID);
				cout << "               you liked this post !               " << endl;
					flag = 1;
				}

				else if (Input == 'E')
				{
					
						string tempID=to_string(User_ID)+".xml";
								const char * tempid = tempID.c_str();
								temp.LoadFile(tempid);	
					XMLNode * Post = temp.FirstChildElement("USER")->FirstChildElement("Posts")->FirstChildElement("Post");
					std::cout << "               please type the edit you want :" << endl;
					string pbody;
					cin.ignore(256, '\n');
					getline(cin,pbody );
					while (Post != nullptr)
					{
						if(atoi(Post->FirstChildElement("ID")->GetText())== User_Posts[i].id)
						{Post->FirstChildElement("Body")->SetText(pbody.c_str());
							break;
						}
						Post=Post->NextSiblingElement();
					}
					pbody = new_edit.body;
					Edit_Post(i, new_edit);
					saveXMLtemp(User_ID);
					std::cout << "               Your Post Has been edited !" << endl;
				}
				//if this is your post you can delete it
				else if (Input == 'D')
				{   	string tempID=to_string(User_ID)+".xml";
						const char * tempid = tempID.c_str();
						temp.LoadFile(tempid);	
					XMLNode * Post = temp.FirstChildElement("USER")->FirstChildElement("Posts")->FirstChildElement("Post");
					while (Post != nullptr)
					{
						if(atoi(Post->FirstChildElement("ID")->GetText())== User_Posts[i].id)
						{   temp.DeleteNode(Post);

								
							break;
						}
						Post=Post->NextSiblingElement();
					}

					saveXMLtemp(User_ID);
					
					
					
					Delete_Post(i);
					std::cout << "               Your Post Has been Deleted !" << endl;
					//i--;
				}
				else if (Input == 'd')
				{
					string tempID=to_string(User_ID)+".xml";
						const char * tempid = tempID.c_str();
						temp.LoadFile(tempid);	
						XMLElement * Post = temp.FirstChildElement("USER")->FirstChildElement("LikedPosts")->FirstChildElement("ID");
					while (Post != nullptr)
					{
						if(atoi(Post->GetText())== User_Posts[i].id)
						{temp.DeleteNode(Post->FirstChildElement("ID"));
						break;
						} 
						Post=Post->NextSiblingElement();
					}

					saveXMLtemp(User_ID);	
					LikedPosts.erase(User_Posts[0].id);
					std::cout << "               You unliked this post !               " << endl;
					flag = 0;
				}

				else if (Input == 'N') {
					i++;
				}
				else if (Input == 'X')
				{
					break;
				}

			}

			if ((User_Posts.size()) != 0) {
				flag = 0;
				std::cout <<"               "<< User_Posts[i].body << endl;


				//check liking part
				//must know index of the current user
				for (auto j = LikedPosts.begin(); j != LikedPosts.end(); j++)
				{
					if (*j == User_Posts[i].id)
					{
						std::cout << "               You Liked this post !               " << endl;;
						flag = 1;
						break;
					}
				}

				if (flag == 0) { cout << "               To Like this post ENter L" << endl; }
				cout << "               To Edit YOUR post Enter E" << endl
					<< "               To delete you post Enter D" << endl
				    << "               To Exit Enter X" << endl;
				if (i != User_Posts.size() - 1) { cout << "               To see the Next post Enter N" << endl; }
				if (flag == 1)
				{
				 	cout << "               To unlike the post Enter d" << endl;
				}

				cin >> Input;

				if (Input == 'L')
				{
						string postID=to_string(User_Posts[i].id);
						const char * post_ID = postID.c_str();
			if(FLAG){
			XMLElement *pID=xmlDoc.NewElement("ID");
			pID->SetText(post_ID);
			pLikedPosts->InsertEndChild(pID);
			pUser->LinkEndChild(pLikedPosts);
			saveXML(User_ID);}
			else{
				string tempID=to_string(User_ID)+".xml";
				const char * tempid = tempID.c_str();
				newTemp.LoadFile(tempid);
				XMLNode * pos = newTemp.FirstChildElement("USER")->FirstChildElement("LikedPosts");
				XMLElement *Pidtemp=newTemp.NewElement("ID");
				Pidtemp->SetText(User_Posts[i].id);
				pos->InsertEndChild(Pidtemp);
				saveXMLNewtemp(User_ID);
			
			}
				LikedPosts.insert(P_ID);
				cout << "               you liked this post !               " << endl;
					flag = 1;
				}


				//if this is your post you can edit it
				else if (Input == 'E')
				{   								string tempID=to_string(User_ID)+".xml";
								const char * tempid = tempID.c_str();
								temp.LoadFile(tempid);	
					XMLNode * Post = temp.FirstChildElement("USER")->FirstChildElement("Posts")->FirstChildElement("Post");
					std::cout << "               please type the edit you want :" << endl;
					string pbody;
					cin.ignore(256, '\n');
					getline(cin,pbody );
					while (Post != nullptr)
					{
						if(atoi(Post->FirstChildElement("ID")->GetText())== User_Posts[i].id)
						{Post->FirstChildElement("Body")->SetText(pbody.c_str());
							break;
						}
						Post=Post->NextSiblingElement();
					}
					Edit_Post(i, new_edit);
					saveXMLtemp(User_ID);
					std::cout << "               Your Post Has been edited !               " << endl;
				}
				//if this is your post you can delete it
				else if (Input == 'D')
				{string tempID=to_string(User_ID)+".xml";
						const char * tempid = tempID.c_str();
						temp.LoadFile(tempid);	
					XMLNode * Post = temp.FirstChildElement("USER")->FirstChildElement("Posts")->FirstChildElement("Post");
					while (Post != nullptr)
					{
						if(atoi(Post->FirstChildElement("ID")->GetText())== User_Posts[i].id)
						{   temp.DeleteNode(Post);

								
							break;
						}
						Post=Post->NextSiblingElement();
					}

					saveXMLtemp(User_ID);
					
					
					
					Delete_Post(i);
					std::cout << "               Your Post Has been Deleted !               " << endl;
					i--;
				}
				else if (Input == 'd')
				{
					string tempID=to_string(User_ID)+".xml";
						const char * tempid = tempID.c_str();
						temp.LoadFile(tempid);	
						XMLElement * Post = temp.FirstChildElement("USER")->FirstChildElement("LikedPosts")->FirstChildElement("ID");
					while (Post != nullptr)
					{
						if(atoi(Post->GetText())== User_Posts[i].id)
						{temp.DeleteNode(Post->FirstChildElement("ID"));
						break;
						} 
						Post=Post->NextSiblingElement();
					}

					saveXMLtemp(User_ID);
					LikedPosts.erase(User_Posts[i].id);
					std::cout << "               You unliked this post !               " << endl;
					flag = 0;
				}
				else if (Input == 'N') {
					i++;
				}

				if (Input != 'N')
					i++;
				else if (Input == 'X')
				{
					break;
				}
			}
		}
	}

void USER::View(int mainID, char & c)
{
	char Input = 'F';
	Posts new_edit;
	int i = 0; int flag = 0;
		while ((Input != 'n' ||Input != 'X') && i < User_Posts.size()){
			//view first post
			if (Input == 'F')
			{
			    cout <<"               "<<F_Name<<" "<<L_Name<<" : "<<User_Posts[0].body << endl;
				cout<<"               "<<User_Posts[i].date<<endl;
				//check liking part
				//must know index of the current user
				for (auto j = LikedPosts.begin(); j != LikedPosts.end(); j++)
				{
					if (*j == User_Posts[i].id)
					{
						std::cout << "               You Liked this post !" << endl;
						flag = 1;
						break;
					}
				}
				
				if (flag == 0) { cout << "               To Like this post ENter L" << endl; }

				cout<<"               to view posts of next users  enter n"<<endl<< "               to Exit Enter X" << endl;

				if (i != User_Posts.size() - 1) { cout << "               To see the Next post Enter N" << endl; }
				if (flag == 1)
				{
					cout << "               To unlike the post Enter d" << endl;
				}
				std::cin >> Input;
				c=Input;
				if (Input == 'L')
				{
						string postID=to_string(User_Posts[i].id);
						const char * post_ID = postID.c_str();
			if(FLAG){
			XMLElement *pID=xmlDoc.NewElement("ID");
			pID->SetText(post_ID);
			pLikedPosts->InsertEndChild(pID);
			pUser->LinkEndChild(pLikedPosts);
			saveXML(mainID);}
			else{
				string tempID=to_string(mainID)+".xml";
				const char * tempid = tempID.c_str();
				newTemp.LoadFile(tempid);
				XMLNode * pos = newTemp.FirstChildElement("USER")->FirstChildElement("LikedPosts");
				XMLElement *Pidtemp=newTemp.NewElement("ID");
				Pidtemp->SetText(User_Posts[i].id);
				pos->InsertEndChild(Pidtemp);
				saveXMLNewtemp(mainID);
			
			}
			LikedPosts.insert(P_ID);
				cout << "               you liked this post !               " << endl;
					flag = 1;
				}
				else if (Input == 'd')
				{
					string tempID=to_string(mainID)+".xml";
						const char * tempid = tempID.c_str();
						temp.LoadFile(tempid);	
						XMLElement * Post = temp.FirstChildElement("USER")->FirstChildElement("LikedPosts")->FirstChildElement("ID");
					while (Post != nullptr)
					{
						if(atoi(Post->GetText())== User_Posts[i].id)
						{temp.DeleteNode(Post);
						break;
						} 
						Post=Post->NextSiblingElement();
					}

					saveXMLtemp(mainID);
					LikedPosts.erase(User_Posts[i].id);
					std::cout << "               You unliked this post !               " << endl;
					flag = 0;
				}

				else if (Input == 'N') {
					i++;
				}
				else if(Input == 'n' || Input == 'X'){break;}
				else if (Input != 'N' )
					i++;
				
			}

			if ((User_Posts.size()) != 0) {
				cout <<"               " <<F_Name<<" "<<L_Name<<" : "<<User_Posts[i].body << endl;
				cout<<"               " <<User_Posts[i].date<<endl;
				//check liking part
				//must know index of the current user
				for (auto j = LikedPosts.begin(); j != LikedPosts.end(); j++)
				{
					if (*j == User_Posts[i].id)
					{
						std::cout << "               You Liked this post !               " << endl;
						flag = 1;
						break;
					}
				}


				if (flag == 0) { cout << "               To Like this post ENter L" << endl; }
				cout<<"               To Unlike This Post Enter d"<<endl;
				cout<<"               To view posts of next user enter n"<<endl<< "               to Exit Enter X" << endl;
				if (i != User_Posts.size() - 1) { cout << "               To see the Next post Enter N" << endl; }
				if (flag == 1)
				{
					cout << "               To unlike the post Enter d" << endl;
				}
				std::cin >> Input;
				c=Input;
				if (Input == 'L')
				{
			if(FLAG){ XMLElement *pID=xmlDoc.NewElement("ID");
			string postID=to_string(User_Posts[i].id);
			const char * post_ID = postID.c_str();
			pID->SetText(post_ID);
			pLikedPosts->InsertEndChild(pID);
			pUser->LinkEndChild(pLikedPosts);
			saveXML(mainID);}
			else{
				string tempID=to_string(mainID)+".xml";
				const char * tempid = tempID.c_str();
				newTemp.LoadFile(tempid);
				XMLNode * pos = newTemp.FirstChildElement("USER")->FirstChildElement("LikedPosts");
				XMLElement *Pidtemp=newTemp.NewElement("ID");
				Pidtemp->SetText(User_Posts[i].id);
				pos->InsertEndChild(Pidtemp);
				saveXMLNewtemp(mainID);
					flag = 1;
				}
				}

				else if (Input == 'd')
				{
					string tempID=to_string(mainID)+".xml";
						const char * tempid = tempID.c_str();
						temp.LoadFile(tempid);	
						XMLElement * Post = temp.FirstChildElement("USER")->FirstChildElement("LikedPosts")->FirstChildElement("ID");
					while (Post != nullptr)
					{
						if(atoi(Post->GetText())== User_Posts[i].id)
						{temp.DeleteNode(Post);
						break;
						} 
						Post=Post->NextSiblingElement();
					}

					saveXMLtemp(mainID);
					LikedPosts.erase(User_Posts[i].id);
					std::cout << "               You unliked this post !               " << endl;
					flag = 0;
				}

				else if (Input == 'N') {
					i++;
				}
				else if(Input != 'n' || Input != 'X'){break;}
				else if (Input != 'N')
					i++;
				
			}
		}
	}





void USER::View_Other_Users_Posts(USER user ,int mainID , char &c)
{

	user.View(mainID, c);

}




void Admin ::GetMostPopular(GraphType & g){

		int max=g.countEdged(g.vertices[0]);
		int index=0;
	for(int i=0; i<g.numVertices;i++){
		if(g.countEdged(g.vertices[i])>max)
		{max=g.countEdged(g.vertices[i]);
			index=i;
		}
	}
	cout<<"               "<<g.vertices[index].F_Name<<" "<<g.vertices[index].L_Name<<" Has : "<<max<<"Friends"<<endl;
	index=0;
	max=0;
}



	void Admin::GetLeastPopular(GraphType & g){
		int min=g.countEdged(g.vertices[0]);
		int index=0;
	for(int i=0; i<g.numVertices;i++){
		if(g.countEdged(g.vertices[i])<min)
		{min=g.countEdged(g.vertices[i]);
			index=i;
		}
	}
cout<<"               "<<g.vertices[index].F_Name<<" "<<g.vertices[index].L_Name<<" Has : "<<min<<"Friends"<<endl;
	}

	
	void Admin::getMostInteractiveUser(GraphType & g){
			int max=g.vertices[0].LikedPosts.size();
		int index=0;
	for(int i=0; i<g.numVertices;i++){
		if(g.vertices[i].LikedPosts.size()>max)
		{max=g.vertices[i].LikedPosts.size();
			index=i;
		}
	}
		cout<<"               "<<g.vertices[index].F_Name<<" "<<g.vertices[index].L_Name<<" Has : "<<max<<"Likes on his Friends Posts"<<endl;
		}
	
	void Admin::getLeastInteractiveUser(GraphType & g){
		int min=g.vertices[0].LikedPosts.size();
		int index=0;
	for(int i=0; i<g.numVertices;i++){
		if(g.vertices[i].LikedPosts.size()<min)
		{min=g.vertices[i].LikedPosts.size();
			index=i;
		}
	}
		cout<<"               "<<g.vertices[index].F_Name<<" "<<g.vertices[index].L_Name<<" Has : "<<min<<"Likes on his Friends Posts"<<endl;
	}

	

	void Admin:: GetMostLikedPostOfUser(GraphType & g,USER & user){
		map<int, int, std::greater<int>> sorted;
		for(int j=0;j<user.User_Posts.size();j++)
		{
			int index=0;
			int PostDesiredID=user.User_Posts[j].id;
			for(int i=0;i<g.numVertices;i++)
			{ 
				if(binary_search(g.vertices[i].LikedPosts.begin(),g.vertices[i].LikedPosts.end(),PostDesiredID))
			//if (g.vertices[i].LikedPosts.find(PostDesiredID)!= g.vertices[i].LikedPosts.end() )
			{	
				index++; 
			}
			sorted[user.User_Posts[j].id];
			sorted[user.User_Posts[j].id]=index;
		}

		}

			int in;		
		int maxindex;
			for (const auto& p : sorted)

		{	
			in=p.first;
			maxindex=p.second;
			break;
		}
		for (const auto& p : sorted)

		{	
			if(p.second>maxindex)
			{in=p.first;
			maxindex=p.second;
			}
		}
		int L=0;
		for(L;L<user.User_Posts.size();L++)
		{
			if(user.User_Posts[L].id==in)
				break;
		}
		cout<<"               "<<user.F_Name<< " "<<user.L_Name <<"Most Liked Post is : " <<user.User_Posts[L].body<<endl;
		cout<<"               The Post Date is : "<<user.User_Posts[L].date<<endl;
		cout<<"               Number of likes on this post is :"<< maxindex<<endl;
	}

	void Admin::GetLeastLikedPostOfUser(GraphType & g,USER & user){
		map<int, int, std::greater<int>> sorted;
		for(int j=0;j<user.User_Posts.size();j++)
		{
			int index=0;
			int PostDesiredID=user.User_Posts[j].id;
			for(int i=0;i<g.numVertices;i++)
			{ 
				if(binary_search(g.vertices[i].LikedPosts.begin(),g.vertices[i].LikedPosts.end(),PostDesiredID))	
			//if (g.vertices[i].LikedPosts.find(PostDesiredID)!= g.vertices[i].LikedPosts.end() )
			{	
				index++; 
			}
			sorted[user.User_Posts[j].id];
			sorted[user.User_Posts[j].id]=index;
		}

		}
		int in;
	   int maxindex;
		for (const auto& p : sorted)

		{	
			in=p.first;
			maxindex=p.second;
			break;
		}


		for (const auto& p : sorted)

		{	
			if(p.second<maxindex)
			{in=p.first;
			maxindex=p.second;
			}
		}
		int L=0;
		for(L;L<user.User_Posts.size();L++)
		{
			if(user.User_Posts[L].id==in)
				break;
		}
		cout<<"               "<<user.F_Name<< " "<<user.L_Name <<" Least Liked Post is : " <<user.User_Posts[L].body<<endl;
		cout<<"               The Post Date is : "<<user.User_Posts[L].date<<endl;
		cout<<"               Number of likes on this post is :"<< maxindex<<endl;
	}

	void Admin::ViewALLUsers(GraphType & g){
	
		for(int i=0;i<g.numVertices;i++){
		
			cout<<g.vertices[i].User_ID<<"-"<<g.vertices[i].F_Name<<" " <<g.vertices[i].L_Name<<endl;
		}	
	
	
	}


		void Admin::MostUserHavePosts(GraphType & g){
		int index=0;
		int max=g.vertices[0].User_Posts.size();
		for (int i=0;i<g.numVertices;i++){
		if(g.vertices[i].User_Posts.size()>max)
		{max=g.vertices[i].User_Posts.size();
			index=i;
		}		    
		
		}
		cout<<"               "<<g.vertices[index].F_Name<<" "<<g.vertices[index].L_Name<<" Has : "<<max<<"Posts"<<endl;
		
	
	}

		void Admin::LeastUserHavePosts(GraphType & g){
		int index=0;
		int min=g.vertices[0].User_Posts.size();
		for (int i=0;i<g.numVertices;i++){
		if(g.vertices[i].User_Posts.size()<min)
		{min=g.vertices[i].User_Posts.size();
			index=i;
		}		    
		
		}
		cout<<"               "<<g.vertices[index].F_Name<<" "<<g.vertices[index].L_Name<<" Has : "<<min<<"Posts"<<endl;
		
	
	}

		void Admin::Statictics(GraphType & g){
			int AllPosts=0;
			int AllLikes=0;
			int AllFemales=0;
			int AllMales=0;
			for(int i=0;i<g.numVertices;i++){
				AllPosts+=g.vertices[i].User_Posts.size();
				AllLikes+=g.vertices[i].LikedPosts.size();
				if(g.vertices[i].Gender=="Female"){
AllFemales++;}
				else{
				AllMales++;
				}
			}

			cout<<"There is : " << float(AllFemales)/float(g.numVertices) *100<< " % Female Users In The Network"<<endl;
			cout<<"There is : " << float(AllMales)/float(g.numVertices) *100<< " % Female Users In The Network"<<endl;
			cout<<endl;
			for(int i=0;i<g.numVertices;i++){
				cout<<g.vertices[i].F_Name<<" "<<g.vertices[i].L_Name<<" Has : "<<float(g.vertices[i].User_Posts.size())/float(AllPosts)*100<< "% OF All Posts in the Network"<<endl;
				cout<<g.vertices[i].F_Name<<" "<<g.vertices[i].L_Name<<" Has : "<<float(g.vertices[i].LikedPosts.size())/float(AllLikes)*100<< "% OF All Interactions in the Network"<<endl;
				cout<<g.vertices[i].F_Name<< " "<<g.vertices[i].L_Name<<" Has : "<<float(g.countEdged(g.vertices[i]))/float(g.numVertices) *100<<" % Of Users as his Friends in the Network"<<endl;
				cout<<endl;
			}
			
		
		}

void Admin::MostLikedPostInGraph(GraphType & g)
{
	bool v = 0;
	int desired_Post_ID = 0;
	int max_no_of_liking_users = 0;
	Posts post_exist;
	for (int q = 0; q < P_ID; q++)
	{
		for (int w = 0; w < COUNT; w++)
		{
			for (int j = 0; j < g.vertices[w].User_Posts.size(); j++)
			{
				if (g.vertices[w].User_Posts[j].id == q)
				{
					int no_of_liking_users = 0;
					for (int t = 0; t < COUNT; t++)
					{
							v = binary_search(g.vertices[t].LikedPosts.begin(), g.vertices[t].LikedPosts.end(), q);
							if (v == true)
							{
								no_of_liking_users++; v = false;
							}
					}
					if (max_no_of_liking_users < no_of_liking_users)
					{
						max_no_of_liking_users = no_of_liking_users;
						desired_Post_ID = q;
					}
				}
			}

		}
	}		
	Posts desired_Post;
	for (int w = 0; w < COUNT; w++)
	{
		for (int j = 0; j < g.vertices[w].User_Posts.size(); j++)
		{
			if (g.vertices[w].User_Posts[j].id == desired_Post_ID)
			{
				cout << "The Most Liked Post is : " << endl << g.vertices[w].User_Posts[j].body << endl
					<< "id : " << desired_Post_ID << endl
					<< "date: " << g.vertices[w].User_Posts[j].date << endl
					<< "no_of_likes : " << max_no_of_liking_users << endl
					<< "posted by : " << g.vertices[w].F_Name << " " << g.vertices[w].L_Name << endl;
				/*desired_Post.id = desired_Post_ID;
				desired_Post.body = g.vertices[w].User_Posts[j].body;
				desired_Post.date = g.vertices[w].User_Posts[j].date;
				desired_Post.comments = g.vertices[w].User_Posts[j].comments;*/
				w = COUNT;
				break;
			}
		}
	}

}



void Admin::LeastLikedPostInGraph(GraphType & g)
{
	bool v = 0;
	int desired_Post_ID = 0;
	int min_no_of_liking_users = 1000;
	for (int q = 0; q < P_ID; q++)
	{
		for (int w = 0; w < COUNT; w++)
		{
			for (int j = 0; j < g.vertices[w].User_Posts.size(); j++)
			{
				if (g.vertices[w].User_Posts[j].id == q)
				{
					int no_of_liking_users = 0;
					for (int t = 0; t < COUNT; t++)
					{
						v = binary_search(g.vertices[t].LikedPosts.begin(), g.vertices[t].LikedPosts.end(), q);
						if (v == true)
						{
							no_of_liking_users++; v = false;
						}
					}
					if (min_no_of_liking_users > no_of_liking_users)
					{
						min_no_of_liking_users = no_of_liking_users;
						desired_Post_ID = q;
					}
				}
			}
		}
	}
	Posts desired_Post;
	for (int w = 0; w < COUNT; w++)
	{
		for (int j = 0; j < g.vertices[w].User_Posts.size(); j++)
		{
			if (g.vertices[w].User_Posts[j].id == desired_Post_ID)
			{
				cout << "The Laest Liked Post is : " << endl << g.vertices[w].User_Posts[j].body << endl
					<< "id : " << desired_Post_ID << endl
					<< "date: " << g.vertices[w].User_Posts[j].date << endl
					<< "no_of_likes : " << min_no_of_liking_users << endl
					<< "posted by : " << g.vertices[w].F_Name << " " << g.vertices[w].L_Name << endl;
				w = COUNT;
				break;
			}
		}
	}

}




bool GraphType::is_mail_valid (string email)
{
	
	for (int i = 0; i < vertices.size(); i++)
	{
		if (vertices[i].Email == email)
			return true;
		
	}
	return false;
}
void load(GraphType &g, map <int,set<int>> & M,int nom_users)
{
	COUNT = 0;
	
	//for (int i = 0; i < nom_users; i++)
	for (int i = 0; i < nom_users; i++)
	{
		XMLDocument xmlDoc;
		string xml_name = to_string(i) + ".xml";
		const char* XML_NAME = xml_name.c_str();
		xmlDoc.LoadFile(XML_NAME);
		//xmlDoc.LoadFile("SavedData.xml");
		USER user(
			(atoi(xmlDoc.FirstChildElement("USER")->FirstChildElement("ID")->GetText())),
			((string)xmlDoc.FirstChildElement("USER")->FirstChildElement("FirstName")->GetText()),
			((string)xmlDoc.FirstChildElement("USER")->FirstChildElement("LastName")->GetText()),
			((string)xmlDoc.FirstChildElement("USER")->FirstChildElement("DateOfBirth")->GetText()),
			((string)xmlDoc.FirstChildElement("USER")->FirstChildElement("Gender")->GetText()),
			((string)xmlDoc.FirstChildElement("USER")->FirstChildElement("Email")->GetText()),
			((string)xmlDoc.FirstChildElement("USER")->FirstChildElement("Password")->GetText())

			);
		XMLNode * posts = xmlDoc.FirstChildElement("USER")->FirstChildElement("Posts");
		if (posts != nullptr)
		{
			XMLNode * Post = posts->FirstChildElement("Post");
			while (Post != nullptr)
			{
				Posts P;
				P.id = atoi(Post->FirstChildElement("ID")->GetText());
				P.body = (string)Post->FirstChildElement("Body")->GetText();
				P.date = (string)Post->FirstChildElement("Date")->GetText();
				user.User_Posts.push_back(P);
				P_ID++;
				Post = Post->NextSiblingElement();
			}
		}
		tinyxml2::XMLElement *levelElement1 = xmlDoc.FirstChildElement("USER")->FirstChildElement("LikedPosts");
		if (levelElement1 != nullptr){
			for (tinyxml2::XMLElement* child = levelElement1->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
			{
				user.LikedPosts.insert(atoi(child->GetText()));
			}
		}

		tinyxml2::XMLElement *levelElement2 = xmlDoc.FirstChildElement("USER")->FirstChildElement("Friends");
		if (levelElement2 != nullptr){
			for (tinyxml2::XMLElement* child2 = levelElement2->FirstChildElement(); child2 != NULL; child2 = child2->NextSiblingElement())
			{
				M[user.User_ID].insert(atoi(child2->GetText()));
				//g.AddEdge(user,(g.UserFromIndex(atoi(child->GetText()))));
			}
		}
	   g.AddVertex(user);
		COUNT++;
	}
}




int main() {
onLogout:	GraphType g(10);
    AdminXML.LoadFile( "Admin.xml" );
  int index=atoi(AdminXML.FirstChildElement("Index")->GetText());
	map <int,set<int>> MM;
	load(g,MM,index);
	// PUTTING XML INside The Data Structure 
	for (auto i =MM.begin(); i !=MM.end(); i++)
	{
		int w;
		int u;
		for (auto j=i->second.begin(); j !=i->second.end(); j++)
		{
			w=i->first;
			u=*j;
			g.AddEdge(g.UserFromIndex(w),g.UserFromIndex(u));
		}
		
	}
			char login;
			USER user;
		 xmlDoc.InsertFirstChild(pUser);
		cout << "               Welcome to Our Social Network! \n	If you are already a user: Press 1 to login \n  If You want to create an Account: Press 2 to sign up               " <<endl;
	cin >>login;

	// SIGN UP SECTION 

		if (login == '2')
		{   
			FLAG=1; // sign up 
			//ID section 
			string id=to_string(COUNT);
			const char * iduser = id.c_str();
			XMLElement *pId=xmlDoc.NewElement("ID");
			pId->SetText(iduser);
			pUser->InsertFirstChild(pId);
			//First Name section
			string f_Name;
			cout<<"               please enter your first Name : "<<endl;
			cin >> f_Name;
			const char * fName = f_Name.c_str();
			XMLElement *pfirstName=xmlDoc.NewElement("FirstName");
			pfirstName->SetText(fName);
			pUser->InsertEndChild(pfirstName);
			//Last Name section
			string l_Name;
			cout<<"               please enter your Last Name : "<<endl;
			cin >> l_Name;
			const char * lName = l_Name.c_str();
			XMLElement *plastName=xmlDoc.NewElement("LastName");
			plastName->SetText(lName);
			pUser->InsertEndChild(plastName);
			//Date of Birth
			string Date_Birth;
			cout<<"               please enter your DateOf Birth Format dd/mm/yyyy : "<<endl;
			cin >> Date_Birth;
			const char * dateBirth = Date_Birth.c_str();
			XMLElement *pdateBirth=xmlDoc.NewElement("DateOfBirth");
			pdateBirth->SetText(dateBirth);
			pUser->InsertEndChild(pdateBirth);
				
			//Gender Section
			string gender; 
			cout<<"               please enter your Gender (Male/Female) : "<<endl;
			cin >> gender;
			const char * genderchar = gender.c_str();
			XMLElement *pGender=xmlDoc.NewElement("Gender");
			pGender->SetText(genderchar);
			pUser->InsertEndChild(pGender);

			//email section
			string email;  
			cout<<"               please enter your email : "<<endl;
			cin >> email;
			const char * emailchar = email.c_str();
			XMLElement *pEmail=xmlDoc.NewElement("Email");
			pEmail->SetText(emailchar);
			pUser->InsertEndChild(pEmail);
			// PASSWORD

		 char ch;
UserPass: cout<<"               please enter your Password :"<<endl;
		 string password; 

		ch = _getch();
			while (ch != 13) {
				if (ch == '\b')
				{
					if (password.size()>0)
					password.pop_back();
					cout << "\b";
				}

				else {
					password.push_back(ch);
					cout << '*';
				}
				ch = _getch();
			}

			string confrimPassword; 
			cout<<endl<<"               please confirm Your Password : "<<endl;
		ch = _getch();
		while(ch != 13){//character 13 is enter
		confrimPassword.push_back(ch);
		cout << '*';
		ch = _getch();
		 }
			if (password == confrimPassword)
		{    //password Section
			const char * passwordchar = password.c_str();
			XMLElement *pPassword=xmlDoc.NewElement("Password");
			pPassword->SetText(passwordchar);
			pUser->InsertEndChild(pPassword);
		    USER USE(COUNT, f_Name, l_Name, Date_Birth, password, email, gender);
			COUNT++;
			
			AdminXML.FirstChildElement("Index")->SetText(COUNT);
			AdminXML.SaveFile("Admin.xml");
			cout <<endl <<"               You signed up successfully !              " << endl;
			g.AddVertex(USE);
			saveXML(USE.User_ID);
			user=USE;
		}
				else {
					cout << "Please enter your password again" << endl;
					goto UserPass;

				}
		}
	if (login == '1') {
		char ifAdmin;
cout<<"               If You want to Login as an admin: Press 1 \n	     If You want to Login as a normal user: Press 2               "<<endl;
		cin>>ifAdmin;
		if(ifAdmin=='2'){
		string email;
		string password;
		cout << "               please enter your email"<<endl;
		bool yes = false;
		do { 
			cin >> email;
			yes=g.is_mail_valid(email);
			if (yes == true) {
				cout << "               please enter your password"<<endl;
			}
			else 
			{
				cout << "please enter a vaild Email address::" << endl;
				//goto label;
			}
		}while(!yes);
loggedin: char ch;
  		ch = _getch();
			while (ch != 13) {
				
				
				if (ch == '\b')
				{
					if (password.size()>0)
					password.pop_back();
					cout << "\b";
				}

				else {
					password.push_back(ch);
					cout << '*';
				}
				ch = _getch();
			}
		if (g.IfUserexist(email, password))
		{	cout <<endl<< "               You logged in successfully !              " << endl;
		user = g.ReturnUser(email); }
		else {
		
		cout<<"               Wrong Password Please Enter again"<<endl;
				password="";
		goto loggedin;
		}
		}
		if(ifAdmin=='1'){
		 char ch;
AdminPass: 		cout<<endl<<"               Please Enter Admin password"<<endl;
		 		string password;
				ch = _getch();
			while (ch != 13) {
				
				
				if (ch == '\b')
				{
					if (password.size()>0)
					password.pop_back();
					cout << "\b";
				}

				else {
					password.push_back(ch);
					cout << '*';
				}
				ch = _getch();
			}
		if(password=="admin123"){
			cout<<endl<<"               You are logged in as An Admin !              "<<endl;}
		
		else 
			{cout<<endl<<"               Password is incorrect !              "<<endl;
		goto AdminPass;}

		string choose;
		Admin admin;
		do {
		cout<<"               To Get Most Popular user in the Network Type A" << endl
			<<"               To Get Least Popular user in the Network Type B" << endl
			<<"               To get user with Most number of Posts in the Network Type C"<<endl
			<<"               To get user with Least number of Posts in the Network Type D"<<endl
			<<"               To Get Most Liked Post of A specific user Type E" <<endl
			<<"               To Get Least Liked Post of A specific user Type F" <<endl
			<<"               To Get Most Interactive user in the Network Type G" <<endl
			<<"               To Get Least Interactive user in the Network Type H" <<endl
			<<"               To View All users in the Network Type I"<<endl
			<<"               To View General Statictics About Network Users Type J"<<endl
			<<"               To View Most Liked Post in the Graph Type K"<<endl
			<<"               To View Most Least Post in the Graph Type L"<<endl
			<<"               if you want to EXIT enter X" << endl;
		cin >> choose;
		if (choose == "A")
		{
			admin.GetMostPopular(g);
		}
		if(choose =="B"){
			admin.GetLeastPopular(g);
		}

		if(choose =="C"){
			admin.MostUserHavePosts(g);
		}
		if(choose =="D"){
			admin.LeastUserHavePosts(g);
		}	
		if(choose =="E"){
			string emailofUser;
			cout<<"               Enter The email of the person you want his most liked post"<<endl;
			cin>>emailofUser;
			USER wanted=g.ReturnUser(emailofUser);
			admin.GetMostLikedPostOfUser(g,wanted);
		}
		if(choose=="F"){
			string emailofUser;
			cout<<"               Enter The email of the person you want his Least liked post"<<endl;
			cin>>emailofUser;
;
			USER wanted=g.ReturnUser(emailofUser);
			admin.GetLeastLikedPostOfUser(g,wanted);
		}

		if(choose=="G"){

			admin.getMostInteractiveUser(g);
			
		}

		if(choose=="H"){
		
		admin.getLeastInteractiveUser(g);
		
		}

	   if(choose=="I"){
		admin.ViewALLUsers(g);
		}

	   if(choose == "J"){
		
			admin.Statictics(g);
		}
	    if (choose == "K"){
		
		admin.MostLikedPostInGraph(g);
		}

		if(choose=="L"){
			admin.LeastLikedPostInGraph(g);
		}

		}
		
		while (choose != "X");
		if (choose == "X")
		{
			goto onLogout;
		}

			

		}

		//else {cout<<"Please Enter a Valid Char !"<<endl;goto onLogout;}

	}

	
	    string decision;
		string new_password;
		XMLElement *posts=xmlDoc.NewElement("Posts");
	do {
		cout<< "               To Create new post Enter C" << endl
			<< "               To view your posts Enter P" << endl 
			<< "               To view othe people post Enter V" <<endl
			<< "               To view your Profile Information Enter info "<<endl
			<< "               To search For a Friend to Add or View Profile Press S"<<endl
			<< "               To View Your FriendList Type list"<<endl
			<< "               If you want to change your password Enter change " << endl
			<< "               If you want to edit your profile Enter edit" << endl
			<< "               If you want to logout Enter logout"<<endl
			<< "               if you want to EXIT enter X" << endl;
		    cin >> decision;
		if (decision == "C")
		{   
	
			XMLElement *post1=xmlDoc.NewElement("Post");
			XMLElement *pBody=xmlDoc.NewElement("Body");
			XMLElement *pDate=xmlDoc.NewElement("Date");
			XMLElement *PID=xmlDoc.NewElement("ID");
			P_ID++;
			Posts post;
			post.id=P_ID;
			cout << "               Please Enter your post" << endl;
			cin.ignore();
			getline(cin, post.body);
			const char * body = post.body.c_str();
			string ID =to_string(P_ID);
			const char * POSTID = ID.c_str();
			pBody->SetText(body);
			post1->InsertFirstChild(pBody);
			cout << "               Please Enter the date of your post" << endl;
			cin >> post.date;
			const char * date = post.date.c_str();
			pDate->SetText(date);
			PID->SetText(POSTID);
			post1->InsertEndChild(pDate);
			post1->InsertFirstChild(PID);
			if (FLAG){
			posts->InsertFirstChild(post1);
			pUser->LinkEndChild(posts);
			saveXML(user.User_ID);}
			else
			{
			string tempID=to_string(user.User_ID)+".xml";
			const char * tempid = tempID.c_str();
			temp.LoadFile(tempid);
			XMLNode * pos = temp.FirstChildElement("USER")->FirstChildElement("Posts");
			XMLElement *post1temp=temp.NewElement("Post");
			XMLElement *pBodytemp=temp.NewElement("Body");
			XMLElement *pDatetemp=temp.NewElement("Date");
			XMLElement *PIDtemp=temp.NewElement("ID");
			pBodytemp->SetText(body);
			post1temp->InsertFirstChild(pBodytemp);
			pDatetemp->SetText(date);
			PIDtemp->SetText(POSTID);
			post1temp->InsertEndChild(pDatetemp);
			post1temp->InsertFirstChild(PIDtemp);
			pos->InsertEndChild(post1temp);
			saveXMLtemp(user.User_ID);
			
			}
			user.Create_Post(post);
		}

		else if(decision == "info"){
			cout<<"               First Name : " <<user.F_Name<<endl;
			cout<<"               Last Name : "<<user.L_Name<<endl;
			cout<<"               Email : "<<user.Email<<endl;
			cout<<"               Gender : "<<user.Gender<<endl;
			cout<<"               Date Of Birth :"<<user.DateOfBirth<<endl;
			cout<<endl;
		}

		else if (decision == "P")
		{
		   
			user.View_User_Posts();
			GraphType g(10);
				load(g,MM,index);
		}
		else if (decision == "V")
		{   char S;
			for (int i = 0; i < g.numVertices; i++)
			{
		         char S;
				user.View_Other_Users_Posts(g.vertices[i],user.User_ID,S);
				if(S=='X')
					break;
			}
			GraphType g(10);
							load(g,MM,index);

		}
		else if (decision=="logout"){
		 cout<<"               You are currently logged out !              "<<endl;
		 goto onLogout;
		}
		else if (decision == "S"){
		cout << "               Please Enter name of your friend" << endl;
		string f_Name;
		cin >> f_Name;
		g.ViewUserwithName(user, f_Name);
		
		}
		else if(decision == "list"){
		
		g.ListFriends(user);
		cout<<"               Number of Friends You have is : "<<g.countEdged(user)<<endl;
		}
		//cout << "If you want to change your password Enter change password " << endl;
		//(cin >> decision);
		else if (decision == "change") {

			string tempID=to_string(user.User_ID)+".xml";
			const char * tempid = tempID.c_str();
			temp.LoadFile(tempid);	

			cout << "               Please enter you new Password" << endl;
			cin >> new_password;
			user.Change_Password(new_password);
			temp.FirstChildElement("USER")->FirstChildElement("Password")->SetText(new_password.c_str());
			cout << "               Your Password has been changed !               " << endl;
			saveXMLtemp(user.User_ID);
		}
		//cout << "If you want to edit your profile Enter edit profile" << endl;
	
		else if (decision == "edit")
		{
			string tempID=to_string(user.User_ID)+".xml";
			const char * tempid = tempID.c_str();
			temp.LoadFile(tempid);		
			
			string fName;
			cout<<"               please enter your first Name : "<<endl;
			cin >> fName;
			const char * PfName = fName.c_str();
			temp.FirstChildElement("USER")->FirstChildElement("FirstName")->SetText(PfName);
			string lName;
			cout<<"               please enter your Last Name : "<<endl;
			cin >> lName;
			const char * PlName = lName.c_str();
			temp.FirstChildElement("USER")->FirstChildElement("LastName")->SetText(PlName);
			string mail;
			cout<<"               please enter your email : "<<endl;
			cin >> mail;
			const char * Pmail = mail.c_str();
			temp.FirstChildElement("USER")->FirstChildElement("Email")->SetText(Pmail);
			string Date_birth; 
			cout<<"               please enter your Date of Birth in the Format dd/mm/yyyy : "<<endl;
			cin >> Date_birth;
			const char * PDate = Date_birth.c_str();
			temp.FirstChildElement("USER")->FirstChildElement("DateOfBirth")->SetText(PDate);
			string gender; 
			cout<<"               please enter your Gender(Male/Female) : "<<endl;
			cin >> gender;
			const char * PGender = gender.c_str();
			temp.FirstChildElement("USER")->FirstChildElement("Gender")->SetText(PGender);
			user.edit_profile(fName, lName, Date_birth, mail, gender);
			saveXMLtemp(user.User_ID);
			cout<<endl<<"               Your Info Has Been Updated !               "<<endl;
		}
	} while (decision != "X");
	system("pause");
	return 0;
}
