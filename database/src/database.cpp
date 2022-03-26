#include <database.hpp>
#include <iostream>
#include <sqlite3.h>
#include <vector>
#include <map>
#include <set>
using namespace std;




struct Data_v
{
	int sisze ;
	vector<map<string, string>>data ;
};





static int callback(void* data, int argc, char** argv, char** azColName)
{
    int i;
    fprintf(stderr, "%s: ", (const char*)data);
    for (i = 0; i < argc; i++) {
        printf("%s = %s  ", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}
 




static int callback1(void *data, int argc, char** argv, char** azColName)
{
    int i;
	struct Data_v *get_ans = (struct Data_v*)data ;
	get_ans->sisze++;
	map<string, string> temp1 ;
	string temp2,temp3 ;
    for (i = 0; i < argc; i++) 
    {
        // printf("%s = %s  ", azColName[i], argv[i] ? argv[i] : "NULL");

		temp2 = azColName[i];
		temp3 = argv[i] ? argv[i] : "NULL";
		temp1[temp2] = temp3;
    }
	get_ans->data.push_back(temp1);
    // printf("\n");
	
    return 0;
}
 



// void Database::updateEmployeeLogin(std::string employee_name, std::string time) 
void Database::updateEmployeeLogin(std::string employee_name, std::string time,std::string date)
{
    string name = employee_name;
    sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open("Db1test", &DB);
	if (exit) {
		std::cout << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
		return ;
	}
	else
		std::cout << "Opened Database Successfully!" << std::endl;


    string query = "";

    string insert_1 = "INSERT INTO Emp_login_Info VALUES(";
    string insert_name = name;
    string insert_time = time;
    string insert_date = date;

    char* messaggeError =NULL;

    string sql = insert_1+"'"+insert_name+ "','"+insert_time+"',NULL,'"+insert_date+"',NULL);";
    cout<<"\nSQL : "<<" "<<sql<<endl ;
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
    std::string string_message;
    if (messaggeError==NULL)
    {
        string_message=="";
        // cout<<"DEBUG1;";
    }
    else
    {
        string_message = messaggeError;
    }
        

    cout<<"\nOutput of Execution: "<<string_message <<endl ;

    if (exit != SQLITE_OK)
        cout << "Error in Insertion" << endl;
    else {
        cout << "Operation OK!" << endl;
    }
	sqlite3_close(DB);
    // return return_val;

}

// void Database::updateEmployeeLogout(std::string employee_name, std::string time) 
void Database::updateEmployeeLogout(string name, std::string time,string date) 
{
    sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open("Db1test", &DB);
	if (exit) {
		std::cout << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
		return ;
	}
	else
		std::cout << "Opened Database Successfully!" << std::endl;

    string query = "";

// UPDATE Emp_Login_Info 
// SET Logout_T = "19:00" , Date_val_logout="2022-03-11"
// WHERE (Emp_Name="Abhinav Garg" AND Logout_T is NULL AND Date_val_logout is NULL ) ;



    string insert_1 = "UPDATE Emp_Login_Info SET ";
    string emp_name = name;
    string logout_time = time;
    string Date_val_logout = date;
    char* messaggeError =NULL;

    string sql = insert_1+"Logout_T = '"+logout_time+ "',Date_val_logout='"+Date_val_logout+"' WHERE (Emp_Name = '"+emp_name +"' AND Logout_T is NULL AND Date_val_logout is NULL ) ;";
    cout<<"\nSQL : "<<" "<<sql<<endl ;
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);



    std::string string_message;
    if (messaggeError==NULL)
    {
        string_message=="";
        // cout<<"DEBUG1;";
    }
    else
    {
        string_message = messaggeError;
    }
        

    cout<<"\nOutput: "<<string_message <<endl ;
    if (exit != SQLITE_OK)
        cout << "Error in Insertion" << endl;
    else {
        cout << "Operation OK!" << endl;
    }
	sqlite3_close(DB);

}

AttendanceRecord Database::getEmployeeAttendance(std::string employee_name, std::string date) 
{
    sqlite3* DB;
    std::list<std::pair<std::string, std::string>> ans1 ;
	int exit = 0;
	exit = sqlite3_open("Db1test", &DB);

	if (exit) {
		std::cout << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
		// return (-1);
	}
	else
		std::cout << "Opened Database Successfully!" << std::endl;

    string query = "";
    query = "SELECT Login_T,Logout_T FROM Emp_Login_Info WHERE (Emp_Name = '"+employee_name+"' AND Date_val_login='"+date+"' );";
	struct Data_v *get_ans = new Data_v() ;
    get_ans->sisze = 0;
    // sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
    char* messaggeError =NULL;

    cout<<endl<<"SQL Query :"<<query<<endl;
    exit = sqlite3_exec(DB, query.c_str(), callback1, get_ans, &messaggeError);



    std::string string_message;
    if (messaggeError==NULL)
    {
        string_message=="";
        // cout<<"DEBUG1;";
    }
    else
    {
        string_message = messaggeError;
    }
        
    cout<<endl ;    
	for (auto i1: get_ans->data )
	{	
        pair<std::string, std::string> temp1 = make_pair(i1["Login_T"],i1["Logout_T"]);
        ans1.push_back(temp1);
	}
    cout<<"\nOutput Message "<<string_message<<endl;
    sqlite3_close(DB);
    return ans1 ;


}

ItemUpdateResults Database::addNewItem(Item new_item,long long int stock) 
{
    sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open("Db1test", &DB);

	if (exit) {
		std::cout << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
		// return (-1);
	}
	else
		std::cout << "Opened Database Successfully!" << std::endl;

    string query = "";
    string insert_1 = "INSERT INTO Item_Info VALUES(";
    string insert_id = to_string(new_item.item_id);
    string insert_name = new_item.item_name;
    string insert_price = to_string(new_item.price);
    string stock_val = to_string(stock);
    // string 

    char* messaggeError =NULL;

    string sql = insert_1+insert_id+ ",'"+insert_name+"',"+insert_price+","+stock_val +");";

	// string sql("INSERT INTO Item_Info VALUES(5, 'Doritos' ,30 ,12);"
    //            "INSERT INTO Item_Info VALUES(6, 'Oreos' ,30,11 );"
    //            "INSERT INTO Item_Info VALUES(7, 'Oreos' ,10 ,13);");

    struct Data_v *get_ans = new Data_v() ;
    get_ans->sisze = 0;
    cout<<endl<<"SQL Query :"<<sql<<endl;
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
	// exit = sqlite3_exec(DB, sql.c_str(), callback1, get_ans, &messaggeError);


    string match = "UNIQUE constraint failed: Item_Info.ID";
    ItemUpdateResults return_val = ItemUpdateResults::kDoesNotExist;
    std::string string_message;
    if (messaggeError==NULL)
    {
        string_message=="";
        // cout<<"DEBUG1;";
    }
    else
    {
        string_message = messaggeError;
    }
        


    if (exit != SQLITE_OK)
        cout << "Error in Insertion" << endl;
    else {
        cout << "Operation OK!" << endl;
    }


    cout<<endl<<"Exn Output Message "<<string_message <<endl;

    // // if id exist three cases : if kExists or kExistsWithDiffName 
    // if(strcmp(messaggeError,"UNIQUE constraint failed: Item_Info.ID")==0)
    if (string_message.compare(match)==0)
    {        
        return_val = ItemUpdateResults::kExists; 

        query = "SELECT Item_Info.name,Item_Info.stock FROM Item_Info Where Item_Info.ID = "+insert_id +";";
        cout<<endl<<"SQL Query :"<<query<<endl;

    	exit = sqlite3_exec(DB, query.c_str(), callback1, get_ans, &messaggeError);
        cout<<endl;
        string temp4_name="",temp5_stock="" ;
        for (auto i1: get_ans->data ) //select data from query
        {	
            temp4_name = i1["name"] ;
            temp5_stock = i1["stock"];
        }

        // compare name and table data 
        if (temp4_name.compare(insert_name)!=0)
        {
            //Different name
            return_val = ItemUpdateResults::kExistsWithDiffName; 
        }      
    }
	sqlite3_close(DB);
    return return_val;

}

ItemUpdateResults Database::updateStock(Item new_item, long long int diff) 
{
     sqlite3* DB;
	int exit = 0;
    long long int sto_1 ;
	exit = sqlite3_open("Db1test", &DB);

	if (exit) {
		std::cout << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
		// return (-1);
	}
	else
		std::cout << "Opened Database Successfully!" << std::endl;

    string current_id = to_string(new_item.item_id);
    string current_name = new_item.item_name;
    string current_price = to_string(new_item.price);
    string stock_diff = to_string(diff);

    char* messaggeError =NULL;

    string query = "SELECT * FROM Item_Info Where Item_Info.ID = "+current_id +";";

    struct Data_v *get_ans = new Data_v() ;
    get_ans->sisze = 0;

    exit = sqlite3_exec(DB, query.c_str(), callback1, get_ans, &messaggeError);

    if (exit != SQLITE_OK)
        cout << "Search Query Failed" << endl;
    else {
        cout << "Operation OK!" << endl;
    }


    std::string string_message;
    if (messaggeError==NULL)
    {
        string_message=="";
        // cout<<"DEBUG1;";
    }
    else
    {
        string_message = messaggeError;
    }
        


    cout<<"\nOutput Message "<<string_message<<endl;

    string temp1_id="" ,temp2_name="",temp3_price="",temp4_stock="" ;

	for (auto i1: get_ans->data )
	{	
        temp1_id = i1["ID"] ;
        temp2_name = i1["name"];
        temp3_price = i1["price"] ;
        temp4_stock = i1["stock"];
		// cout<<endl;
	}
    // cout<<" "<<temp1_id<<" "<<temp2_name<<" "<<temp3_price<<" "<<temp4_stock;

    ItemUpdateResults return_val = ItemUpdateResults::kDoesNotExist;

    if (temp1_id=="")
    {
        //Data is not included in DataBase
        return_val = ItemUpdateResults::kDoesNotExist;
        //no data 
           	sqlite3_close(DB);
            return return_val ;

    }
    else
    {
              // compare name and table data 
        if (temp2_name.compare(current_name)!=0)
        {
            //Different name
            return_val = ItemUpdateResults::kExistsWithDiffName; 
        	sqlite3_close(DB);
            return return_val ;

        }
        else if(temp4_stock>stock_diff)
        {
            // stock not available 
            return_val = ItemUpdateResults::kStockNegative; 
           	sqlite3_close(DB);
            return return_val ;

        }
        else
        {
            //update value 
            // UPDATE Employee_Info SET Emp_Name = "Sandeep Reddy" WHERE Emp_Id = 2;
            sto_1 = stoi(temp4_stock);
            sto_1 = sto_1+diff ; //new stock value
            query = "UPDATE Item_Info SET stock = "+to_string(sto_1) +" WHERE ID = "+temp1_id +";";
            // "UPDATE Employee_Info SET Emp_Name = "Sandeep Reddy" WHERE Emp_Id = 2;

            cout<<"\nSql Query "<<query<<endl;

        	exit = sqlite3_exec(DB, query.c_str(), NULL, 0, &messaggeError);


                if (exit != SQLITE_OK)
                cout << "Search Query Failed" << endl;
                else {
                    cout << "Operation OK!" << endl;
                }

                    if (messaggeError==NULL)
                    {
                        string_message=="";
                        // cout<<"DEBUG1;";
                    }
                    else
                    {
                        string_message = messaggeError;
                    }
        
            cout<<" \n Updated Stock Value "<<sto_1<<endl;
            cout<<" \n Output Message"<< string_message<<endl;


            return_val = ItemUpdateResults::kExists;
        	sqlite3_close(DB);
            return return_val ;

        }
    }

	sqlite3_close(DB);
    return return_val;


}

void Database::updateItemsSold(Item item, std::string date, long long int quantity) 
{

    sqlite3* DB;
	int exit = 0;
    long long int sto_1 ;
	exit = sqlite3_open("Db1test", &DB);

	if (exit) {
		std::cout << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
		// return (-1);
	}
	else
		std::cout << "Opened Database Successfully!" << std::endl;


    char* messaggeError =NULL;
    string insert_1 = "INSERT INTO Sold_by_date VALUES(";
    // string item_id_1 = to_string(Item_id);
    string item_id_1 = to_string(item.item_id);

    string quan_tity = to_string(quantity);

    // INSERT INTO Sold_by_date VALUES(2,24,"2022-03-07");


    string query  = insert_1+item_id_1+","+quan_tity+","+"\""+date+"\");" ;
    cout<<"\n SQLQuery: "<<query<<endl ;
    // struct Data_v *get_ans = new Data_v() ;
    // get_ans->sisze = 0;


	exit = sqlite3_exec(DB, query.c_str(), NULL, 0, &messaggeError);
    // exit = sqlite3_exec(DB, query.c_str(), callback1, get_ans, &messaggeError);

    if (exit != SQLITE_OK)
        cout << "Search Query Failed" << endl;
    else {
        cout << "Operation OK!" << endl;
    }


    std::string string_message;
    if (messaggeError==NULL)
    {
        string_message=="";
        // cout<<"DEBUG1;";
    }
    else
    {
        string_message = messaggeError;
    }
        


    cout<<"\nOutput Message "<<string_message<<endl;
    string temp1 = "UNIQUE constraint failed: Sold_by_date.Item_Id, Sold_by_date.Date_val";
    if (temp1.compare(string_message)==0)
    {
        cout<<endl<<"Data of same ID and Date Already exists in Database";
        sqlite3_close(DB);

        return ;
    }
    

    //Keeping only 30 old records of date
    //select oldest date if data length is larger than 30 

     query  = "SELECT Date_val FROM Sold_by_date ";
    // insert_1+item_id_1+","+quan_tity+","+"\""+date+"\");" ;

    set<string> s1 ;
    // set<string,compartor_1> s1 ;

    struct Data_v *get_ans = new Data_v() ;
    get_ans->sisze = 0;


    exit = sqlite3_exec(DB, query.c_str(), callback1, get_ans, &messaggeError);

    if (exit != SQLITE_OK)
        cout << "Search Query Failed" << endl;
    else {
        cout << "Operation OK!" << endl;
    }



    if (messaggeError==NULL)
    {
        string_message=="";
        // cout<<"DEBUG1;";
    }
    else
    {
        string_message = messaggeError;
    }
        


    cout<<"\nOutput Message "<<string_message<<endl;

    // sqlite3_exec(DB, query.c_str(), callback1, NULL, NULL);
    string temp1_date="" ;

	for (auto i1: get_ans->data )
	{	
        temp1_date = i1["Date_val"] ;
        s1.insert(temp1_date);
	}

    
    cout<<"Number of Dates in Database "<<s1.size();
    cout<<endl<<"Oldest Date in Database "<<*s1.begin();

    // if size increase more than 31 days 
    if (s1.size()>30)
    {
        string oldest_Date = *s1.begin();
        query = "DELETE FROM Sold_by_date WHERE Date_val = ";
        query = query+"\""+oldest_Date+"\";";
        //remove data from database 
        cout<<"\nSql Query : "<<query<<endl;

	    exit = sqlite3_exec(DB, query.c_str(), NULL, 0, &messaggeError);


            if (exit != SQLITE_OK)
                cout << "Search Query Failed" << endl;
            else {
                cout << "Operation OK!" << endl;
            }


            if (messaggeError==NULL)
            {
                string_message=="";
                // cout<<"DEBUG1;";
            }
            else
            {
                string_message = messaggeError;
            }
                
            cout<<"\nOutput Message "<<string_message<<endl;


    }
    // cout<<" "<<s1.size();
    // cout<<endl<<*s1.begin();
    sqlite3_close(DB);
}

long long int Database::getItemsSold(Item item, std::string date) 
{
       sqlite3* DB;
	int exit = 0;
    long long int Item_id = item.item_id;
    long long int sto_1 ;
	exit = sqlite3_open("Db1test", &DB);
    string query ;
	if (exit) {
		std::cout << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
		// return (-1);
	}
	else
		std::cout << "Opened Database Successfully!" << std::endl;


    char* messaggeError =NULL;
    struct Data_v *get_ans = new Data_v() ;
    get_ans->sisze = 0;
    query = "SELECT Sold_by_date.Sold_quan FROM Sold_by_date WHERE Sold_by_date.Item_Id = "+to_string(Item_id)+ " AND Sold_by_date.Date_val = \"" +date +"\";";

    cout<<endl<<"Sql Query :"<<query<<endl;
    // cout<<get_ans->sisze<<endl;
    
    exit = sqlite3_exec(DB, query.c_str(), callback1, get_ans, &messaggeError);
    if (get_ans->sisze==0)
    {
        cout<<"\n No such Data is present in Database";
        sqlite3_close(DB);
        return -1;

    }
    string quantity_1 = "";
    for (auto i1: get_ans->data )
	{	
        quantity_1 = i1["Sold_quan"] ;
		cout<<endl<<quantity_1<<endl;
	}


    std::string string_message;
    if (messaggeError==NULL)
    {
        string_message=="";
        // cout<<"DEBUG1;";
    }
    else
    {
        string_message = messaggeError;
    }
        


    cout<<"\nOutput Message "<<string_message<<endl;
    sqlite3_close(DB);
    long long int val = stoll(quantity_1);
    return val ;
}
