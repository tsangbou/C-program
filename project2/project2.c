#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/shm.h>

 
typedef struct  //struct to contain all items and amount left in store
{
	int number;
    	char *name;
} Entry;


void buyItem(int itemNum, Entry *item, int amount){
	//share memory access	
	itemNum = itemNum - 1;
	
	//check if there is enough items to buy that amount
	if(item[itemNum].number<amount){
		printf("Not enough in stock to buy\n");
	}
	
	else{
		printf("%s - %i \n", item[itemNum].name, item[itemNum].number);
		item[itemNum].number = item[itemNum].number - amount;
		printf("%s - %i \n", item[itemNum].name, item[itemNum].number);
	}	
}
	
void stockItem(int itemNum, Entry *item, int amount){
	itemNum = itemNum - 1;
	printf("%s - %i \n", item[itemNum].name, item[itemNum].number);
	item[itemNum].number = item[itemNum].number + amount;
	printf("%s - %i \n", item[itemNum].name, item[itemNum].number);
}
	
 
int main()
{
	int user;
	int buy;
	int amountBuy;
	int stock;
	int amountStock;
	int inStore=1;
	char checkout;

	int shmid;
	key_t key;
	char *shm;

	key = 1111;	

	FILE *file = fopen("inventory_input.txt", "r");
   	int entryCount;
   	fscanf(file,"%i", &entryCount);
   	Entry *entries = malloc(sizeof(Entry) * entryCount);
	//allocate memory for amount of items in the store	

	int i;
	for(i=0;i<entryCount;i++)
	//for all items place the name and amount in each struct
	{
		entries[i].name = malloc(32);
		fscanf(file, "%s", entries[i].name);
		//printf("%i. %s - %i\n" , i+1 , entries[i].name , entries[i].number);

	}
   	
	fclose(file);
	//close file
	

	/*create shared memory object
	//if created access memory
	shmid = shmget(key ,sizeof(Entry) * entryCount, O_CREAT | 0666);
	Entry *test = shmat(shmid,NULL,0);	
		
	if(shmid<0){
		perror("shmget");
		exit(1);
	}
	//shm = shmat(shmid,NULL,0);
	if(shm==(char *) -1)
        {
                perror("shmat");
                exit(1);
        }
*/
	


	while(inStore==1){

	//ask if you are a clerk or customer
	printf("Welcome to Uncle Trapspringer and Fizban the Fabulous's Potion Shop\n");
	printf("1. Clerk\n2. Customer\nWhat are you? \n");
	
	scanf("%i", &user);
	
	if(user==1){
		printf("The shop has been busy! Should we restock?\n");
	}
	if(user==2){
		printf("Behold our selection of items!\n");
	}

	for(i=0;i<entryCount;i++){
		printf("%i. %s - %i\n" , i+1 , entries[i].name , entries[i].number);
	}


	while(user==2){
		printf("Select the item you wish to buy then amount you want.\n");
		scanf("%i %i",&buy, &amountBuy);
		buyItem(buy,entries,amountBuy);
		user = 0;
	}

	while(user==1){
		printf("Select the item you wish to restock, then the amount you want to add.\n");
		scanf("%i %i",&stock,&amountStock);
		stockItem(stock,entries,amountStock);
		user = 0;
	}




		printf("Would you like to continue shopping? (y/n)\n");
		scanf("%s",&checkout);
		if(checkout=='y'){
		}
		else{
			
			printf("Thanks for stopping at Uncle Trapspringer and Fizban the Fabulous's Potion Shop!\n");
			inStore=0;

		}

	}

	for(i=0;i<entryCount;i++){
		free(entries[i].name);
	}
	free(entries);
 
   

	return 0;
}
