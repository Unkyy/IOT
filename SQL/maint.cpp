
#include <iostream>
#include <cstdlib>
#include "req_sql.h"
#include <stdlib.h>

int main(){

	req_sql test ("127.0.0.1","test","test","maison");
	//test.select("test");
 	test.update("test", "120", 2);
	return 0;
}

