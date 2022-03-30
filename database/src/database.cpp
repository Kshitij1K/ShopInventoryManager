// #include <database.hpp>
#include <iostream>
#include <sqlite3.h>
#include <vector>
#include <map>
#include <set>
using namespace std;




//for getting attendance data
struct Data_v
{
	int sisze ;
	vector<map<string, string>>data ;
};

//for getting Item_Info
struct Data_for_Item
{
	int sisze ;
    // list<std::pair<Item, long long int>> ItemStocks;
    ItemStocks data1;

};

//for getting Item_Info
struct Data_for_Predict
{
	int sisze ;
    // typedef std::list<Predict_data_type> Predict_record;
    Predict_record data1;

};

//getting Item_id
struct Data_Item_List
{
	int sisze ;
    vector<string>data ;
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
 

static int callback2_getting_Item_data(void *data, int argc, char** argv, char** azColName)
{
    int i;
	struct Data_for_Item *get_ans = (struct Data_for_Item*)data ;
	get_ans->sisze++;

    list<std::pair<Item, long long int>> var1;

    vector<pair<string,string>> temp1;
    Item t1 ;

// struct Item {
//   long long int item_id;
//   std::string item_name;
//   float selling_price;
//   float buying_price;
//   float holding_price;
// };

    long long int stock ;
	string temp2,temp3 ;
    for (i = 0; i < argc; i++) 
    {
        // printf("%s = %s ", azColName[i], argv[i] ? argv[i] : "NULL");

		temp2 = azColName[i];
		temp3 = argv[i] ? argv[i] : "NULL";
        if(temp2.compare("ID")==0)
        {
            t1.item_id = stoll(temp3);
        }
        else if(temp2.compare("name")==0)
        {
            t1.item_name = temp3;
        }
        
        else if(temp2.compare("price")==0)
        {
            if(temp3.compare("NULL")!=0)
            t1.selling_price = stof(temp3);
            else 
            t1.selling_price = 0;
        }
        else if(temp2.compare("stock")==0)
        {
            stock = stoll(temp3);
        }
        else if(temp2.compare("Holding_value")==0)
        {
            
            if(temp3.compare("NULL")!=0)
            t1.holding_price = stof(temp3);
            else 
            t1.holding_price = 0;
        }
        else if(temp2.compare("Buying_value")==0)
        {
                        
            if(temp3.compare("NULL")!=0)
            t1.buying_price = stof(temp3);
            else 
            t1.buying_price = 0;
        }
            
        
        
		// temp1[temp2] = temp3;
    }
    get_ans->data1.push_back({t1,stock});
	// get_ans->data.push_back(temp1);
    // printf("\n");
	
    return 0;
}



static int callback3_getting_Predict_data(void *data, int argc, char** argv, char** azColName)
{
    int i;
	struct Data_for_Predict *get_ans = (struct Data_for_Predict*)data ;
	get_ans->sisze++;



// struct Predict_data_type
// {
//     long long int item_id;
//     double Smoothed_error;
//     double Forecast;
//     double MADt;
//     double T;
// };
// typedef std::list<Predict_data_type> Predict_record;


// struct Data_for_Predict
// {
// 	int sisze ;
//     // list<std::pair<Item, long long int>> ItemStocks;
//     Predict_record data1;

// };

    Predict_data_type t1 ;

	string temp2,temp3 ;
    for (i = 0; i < argc; i++) 
    {
        printf("%s = %s ", azColName[i], argv[i] ? argv[i] : "NULL");

		temp2 = azColName[i];
		temp3 = argv[i] ? argv[i] : "NULL";
        if(temp2.compare("Item_Id")==0)
        {
            t1.item_id = stoll(temp3);
        }
        else if(temp2.compare("Smoothed_Error")==0)
        {
            if(temp3.compare("NULL")!=0)
            t1.Smoothed_error = stof(temp3);
            else 
            t1.Smoothed_error = 0;
        }
        
        else if(temp2.compare("Forecast")==0)
        {
            if(temp3.compare("NULL")!=0)
            t1.Forecast = stof(temp3);
            else 
            t1.Forecast = 0;
        }

        else if(temp2.compare("MADt")==0)
        {
            
            if(temp3.compare("NULL")!=0)
            t1.MADt = stof(temp3);
            else 
            t1.MADt = 0;
        }
        else if(temp2.compare("T")==0)
        {
                        
            if(temp3.compare("NULL")!=0)
            t1.T = stof(temp3);
            else 
            t1.T = 0;
        }
     
		// temp1[temp2] = temp3;
    }
    get_ans->data1.push_back(t1);
    printf("\n");
    return 0;
}



static int callback4_getting_Item_ID(void *data, int argc, char** argv, char** azColName)
{
    int i;
    // Data_Item_List
	struct Data_Item_List *get_ans = (struct Data_Item_List*)data ;
	get_ans->sisze++;
;

	string temp2,temp3 ;
    for (i = 0; i < argc; i++) 
    {
        printf("%s = %s ", azColName[i], argv[i] ? argv[i] : "NULL");

		temp2 = azColName[i];
		temp3 = argv[i] ? argv[i] : "NULL";
       
		// temp1[temp2] = temp3;
    }
    
    get_ans->data.push_back(temp3);
    printf("\n");
    return 0;
}













sqlite3* Database::establish_connection()
{
    sqlite3* DB;
	int exit = 0;
	// exit = sqlite3_open("Db1test", &DB);
    exit = sqlite3_open(this->databse_var.c_str(),&DB);

	if (exit) {
		std::cout << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
		// return (-1);
	}
	else
		std::cout << "Opened Database Successfully!" << std::endl;

    return DB;
}









//   Predict_record retrieve_predict_data_basis_of_id(long long int); //search on basis of item_id

Predict_record Database:: retrieve_predict_data_basis_of_name(string name) //search on basis of item name
{
         //connection establised
    sqlite3* DB;
	int exit = 0;
	// exit = sqlite3_open("Db1test", &DB);
    exit = sqlite3_open(this->databse_var.c_str(),&DB);
	if (exit) {
		std::cout << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
	}
	else
		std::cout << "Opened Database Successfully!" << std::endl;




















// struct Data_Item_List
// {
// 	int sisze ;
//     vector<string>data ;
// };

//     string id_val = to_string(id);
    string query = "";
    query = "SELECT ID FROM Item_Info WHERE name = '"+name + "';";
    cout<<endl<<"SQL Query :"<<query<<endl;
    struct Data_Item_List *get_ans = new Data_Item_List() ;
    get_ans->sisze = 0;
    char* messaggeError =NULL;
    exit = sqlite3_exec(DB, query.c_str(), callback4_getting_Item_ID, get_ans, &messaggeError);


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
    vector<string>id_list = get_ans->data ;

    string tuple_ids = "(";
    for (auto in_id : id_list)
    {
        tuple_ids+=in_id;
        tuple_ids+=",";
    }
    
    tuple_ids = tuple_ids.substr(0,tuple_ids.size()-1);
    tuple_ids+=")";
    // cout<<tuple_ids<<endl;

    free(get_ans);



    query = "SELECT * FROM Predict_Table WHERE Item_Id IN "+tuple_ids + ";";

	struct Data_for_Predict *get_ans1 = new Data_for_Predict() ;
    get_ans1->sisze = 0;



// // struct Predict_data_type
// // {
// //     long long int item_id;
// //     double Smoothed_error;
// //     double Forecast;
// //     double MADt;
// //     double T;
// // };
// // typedef std::list<Predict_data_type> Predict_record;


// // struct Data_for_Predict
// // {
// // 	int sisze ;
// //     // list<std::pair<Item, long long int>> ItemStocks;
// //     Predict_record data1;

// // };
    cout<<endl<<"SQL Query :"<<query<<endl;
    exit = sqlite3_exec(DB, query.c_str(), callback3_getting_Predict_data, get_ans1, &messaggeError);
    if (messaggeError==NULL)
    {
        string_message=="";
//         // cout<<"DEBUG1;";
    }
    else
    {
        string_message = messaggeError;
    }
        
    cout<<endl ;    
    Predict_record return_val1 = get_ans1->data1 ;
    cout<<"\nOutput Message "<<string_message<<endl;
    free(get_ans1);
    sqlite3_close(DB);
    return return_val1;
}



Predict_record Database:: retrieve_predict_data_basis_of_id(long long int id) //search on basis of item id
{
        //connection establised
    sqlite3* DB;
	int exit = 0;
	// exit = sqlite3_open("Db1test", &DB);
    exit = sqlite3_open(this->databse_var.c_str(),&DB);
	if (exit) {
		std::cout << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
	}
	else
		std::cout << "Opened Database Successfully!" << std::endl;





















    string id_val = to_string(id);
    string query = "";
    query = "SELECT * FROM Predict_Table WHERE Item_Id = "+id_val + ";";

	struct Data_for_Predict *get_ans = new Data_for_Predict() ;
    get_ans->sisze = 0;
    char* messaggeError =NULL;



// struct Predict_data_type
// {
//     long long int item_id;
//     double Smoothed_error;
//     double Forecast;
//     double MADt;
//     double T;
// };
// typedef std::list<Predict_data_type> Predict_record;


// struct Data_for_Predict
// {
// 	int sisze ;
//     // list<std::pair<Item, long long int>> ItemStocks;
//     Predict_record data1;

// };
    cout<<endl<<"SQL Query :"<<query<<endl;
    exit = sqlite3_exec(DB, query.c_str(), callback3_getting_Predict_data, get_ans, &messaggeError);
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
    Predict_record return_val1 = get_ans->data1 ;
    cout<<"\nOutput Message "<<string_message<<endl;
    free(get_ans);
    sqlite3_close(DB);
    return return_val1;
}





// void Database::updateEmployeeLogin(std::string employee_name, std::string time) 
void Database::updateEmployeeLogin(std::string employee_name, std::string time,std::string date)
{

    //connection establised
    sqlite3* DB;
	int exit = 0;
	// exit = sqlite3_open("Db1test", &DB);
    exit = sqlite3_open(this->databse_var.c_str(),&DB);
	if (exit) {
		std::cout << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
		return ;
	}
	else
		std::cout << "Opened Database Successfully!" << std::endl;







    string name = employee_name;
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
    //connection establised
    sqlite3* DB;
	int exit = 0;
	// exit = sqlite3_open("Db1test", &DB);
    exit = sqlite3_open(this->databse_var.c_str(),&DB);
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
	int exit = 0;
	// exit = sqlite3_open("Db1test", &DB);
    exit = sqlite3_open(this->databse_var.c_str(),&DB);

	if (exit) {
		std::cout << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
		// return (-1);
	}
	else
		std::cout << "Opened Database Successfully!" << std::endl;



    std::list<std::pair<std::string, std::string>> ans1 ;
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
    //connection establised
    sqlite3* DB;
	int exit = 0;
	// exit = sqlite3_open("Db1test", &DB);
    exit = sqlite3_open(this->databse_var.c_str(),&DB);
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
    string insert_price = to_string(new_item.selling_price);
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
    //connection establised
     sqlite3* DB;
	int exit = 0;
    long long int sto_1 ;
	// exit = sqlite3_open("Db1test", &DB);
    exit = sqlite3_open(this->databse_var.c_str(),&DB);
	if (exit) {
		std::cout << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
		// return (-1);
	}
	else
		std::cout << "Opened Database Successfully!" << std::endl;








    string current_id = to_string(new_item.item_id);
    string current_name = new_item.item_name;
    string current_price = to_string(new_item.selling_price);
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

    //connection establised
    sqlite3* DB;
	int exit = 0;
    long long int sto_1 ;
	// exit = sqlite3_open("Db1test", &DB);
    exit = sqlite3_open(this->databse_var.c_str(),&DB);

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
    //connection establised
    sqlite3* DB;
	int exit = 0;
    long long int sto_1 ;
	// exit = sqlite3_open("Db1test", &DB);
    exit = sqlite3_open(this->databse_var.c_str(),&DB);
    string query ;
	if (exit) {
		std::cout << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
		// return (-1);
	}
	else
		std::cout << "Opened Database Successfully!" << std::endl;







    long long int Item_id = item.item_id;
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


ItemStocks Database:: getAllItemStocks()
{

        //connection establised
    sqlite3* DB;
	int exit = 0;
    long long int sto_1 ;
	// exit = sqlite3_open("Db1test", &DB);
    exit = sqlite3_open(this->databse_var.c_str(),&DB);
    string query ;
	if (exit) {
		std::cout << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
		// return (-1);
	}
	else
		std::cout << "Opened Database Successfully!" << std::endl;



//     struct Item {
//   long long int item_id;
//   std::string item_name;
//   float selling_price;
//   float buying_price;
//   float holding_price;
// };




    // typedef std::list<std::pair<Item, long long int>> ItemStocks;

    ItemStocks ans1;
       char* messaggeError =NULL;
    struct Data_for_Item *get_ans = new Data_for_Item() ;
    get_ans->sisze = 0;
    query = "SELECT * FROM Item_Info;";

    cout<<endl<<"Sql Query :"<<query<<endl;
    // cout<<get_ans->sisze<<endl;
    
    exit = sqlite3_exec(DB, query.c_str(), callback2_getting_Item_data, get_ans, &messaggeError);
    if (get_ans->sisze==0)
    {
        cout<<"\n No such Data is present in Database";
        sqlite3_close(DB);
        // return -1;

    }
    // string quantity_1 = "";
    // for (auto i1: get_ans->data )
	// {	
    //     quantity_1 = i1["Sold_quan"] ;
	// 	cout<<endl<<quantity_1<<endl;
	// }


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
        
    ans1 = get_ans->data1;
    free(get_ans);
    cout<<"\nOutput Message "<<string_message<<endl;
    sqlite3_close(DB);
    return ans1 ;
}
































//testing




// int main(int argc, char const *argv[])
// {
//     Database d1 ;
//     // AttendanceRecord ans = d1.getEmployeeAttendance("Sandeep Reddy","2022-03-09");

//     // for (auto x : ans)
//     // {
//     //     cout<<"\n"<<x.first<<" "<<x.second ;
//     // }






//     // ItemStocks a1 = d1.getAllItemStocks();

//     // for (auto x : a1)
//     // {
//     //     cout<<"\n"<<x.first.item_id<<" "<<x.first.item_name<<" "<<x.first.selling_price<<" "<<x.second<<" "<<x.first.holding_price <<" "<<x.first.buying_price ;   
//     // }
    
//     // Predict_record a2 = d1.retrieve_predict_data_basis_of_id(4);
//     // for (auto x :a2)
//     // {
//     //     cout<<x.item_id<<" "<<x.Smoothed_error<<" "<<x.Forecast<<" "<<x.MADt<<" "<<" "<<x.T<<endl;
//     // }
    
//     Predict_record a2 = d1.retrieve_predict_data_basis_of_name("Maggi");
//     for (auto x :a2)
//     {
//         cout<<x.item_id<<" "<<x.Smoothed_error<<" "<<x.Forecast<<" "<<x.MADt<<" "<<" "<<x.T<<endl;
//     }
//     return 0;
// }




