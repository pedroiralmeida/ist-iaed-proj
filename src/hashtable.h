int hash(char *flycode);
int hash_r_code(char *r_code);
void insert_hashtable(Flight f);
Flight *getflight(char flycode[], Date date);
bool find_and_delete_reserv(r_node **r_lst, char r_code[]);
void find_reserv_to_delete(char r_code[], bool *found);
void delete_hflight(char flycode[]);
void delete_flights(char flycode[], bool *found);