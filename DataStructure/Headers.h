#pragma once
#include <string>
using namespace std;
#include <iostream>
#include <vector>
#include <set>





class Posts {
public:
	string body;
	string date;
	int id;
	vector<string>comments;

};

class USER {
public:
	int User_ID;
	string F_Name;
	string L_Name;
	//string Day,Year,Month;
	string DateOfBirth;
	string Password;
	string Email;
	string Gender;
	vector <Posts>User_Posts;
	set<int> LikedPosts;
public:
	USER();
	USER(int id, string f_Name, string l_Name, string Date_Birth,string gender, string email, string password) {
		User_ID = id;
		F_Name = f_Name;
		L_Name = l_Name;
		DateOfBirth = Date_Birth;
		Password = password;
		Email = email;
		Gender = gender;
	}
	void edit_profile(string f_Name, string l_Name, string Date_Birth, string email, string gender);
	void Change_Password(string NewPassword);
	void Create_Post(Posts NewPost);
	void Delete_Post(int index);
	void Edit_Post(int index, Posts New_Edit);
	void View_User_Posts();
	void USER::View(int mainID,char & c);
	void View_Other_Users_Posts(USER user , int mainID, char & c);
};


class GraphType {
public:
	int numVertices;
	int maxVertices;
	vector<USER>vertices; // dynamic array of vertices 3la 7asab no3hom eh
	vector<vector<int> > edges;
	bool* marks; // array of boolean checking if marked or not
public:
	GraphType(int maxV) {
		numVertices = 0; // lesa mafesh ay vertices 
		maxVertices = maxV; // el max eli d5lto da 
		edges.resize(maxV);
		for (int i = 0; i < maxV; i++)
			edges[i].resize(maxV); // w coloumns bel 3dd da 
		marks = new bool[maxV]; // w array el marked kman b nfs el 3dd
	}
	~GraphType() {
		vertices.erase(vertices.begin(), vertices.end()); // awl 7aga hms7 array el vertices 
		edges.erase(edges.begin(), edges.end());
		delete[] marks; // ams7 el marked 
	}
	void AddVertex(USER vertex);
	int IndexIs(USER vertex);
	int numOfUsers();
	void ListAll();
	string VertexFromIndex(int index);
	void RemoveVertex(USER vertex);
	void AddEdge(USER fromVertex, USER toVertex);
	void RemoveEdge(USER fromVertex, USER toVertex);
	bool IfFriend(USER fromVertex, USER toVertex);
	void ListFriends(USER vertex);
	bool IfUserexist(string email, string password);
	void ViewUserwithName(USER user, string name);
	USER ReturnUser(string email);
	int countEdged(USER vertex);
	USER UserFromIndex(int index);
	bool is_mail_valid(string email);
	bool is_password_valid(string pass);
};



class Admin{
public:
	string password;

	void GetMostPopular(GraphType & g);

	void GetLeastPopular(GraphType & g);

	void getMostInteractiveUser(GraphType & g);

	void getLeastInteractiveUser(GraphType & g);

	void GetMostLikedPostOfUser(GraphType & g,USER & user);

	void GetLeastLikedPostOfUser(GraphType & g,USER & user);

	void ViewALLUsers(GraphType & g);

    void MostUserHavePosts(GraphType & g);

   void LeastUserHavePosts(GraphType & g);

	void MostLikedPostInGraph(GraphType & g);
	void LeastLikedPostInGraph(GraphType & g);
   
	void Statictics(GraphType & g);
};