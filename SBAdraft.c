#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#define PASSWORD "guess"
#define SIZE 50
#define MARKUP 1.5
#define LIMIT 3
#define MAX_LENGTH 5

struct ItemInfo {
	int id;
	char name[SIZE];
	float cost;
	float price;
	int stock;
	float stockvalue;
	int ogstock;
	float ogstockvalue;
};

struct SaleInfo {
	int saleid;
	char customername[SIZE];
	float cost;
	int plantids[SIZE];
	int equipids[SIZE];
	float plantprice[SIZE];
	float equipprice[SIZE];
	char plantnames[SIZE][SIZE];
	char equipnames[SIZE][SIZE];
	int plantquant[SIZE];
	int equipquant[SIZE];
	int totplant;
	int totequip;
	float planttotal[SIZE];
	float equiptotal[SIZE];
	float planttotfee;
	float equiptotfee;
};

struct QueueInfo {
	int id;
	int quant;
	float owed;
	char name[SIZE];
	char itemname[SIZE];
};
void menu();
int autoid(char filename[], int start) {
	int num;
	FILE *fp;
	if ((fp = fopen(filename, "r")) == NULL) {
		if ((fp = fopen(filename, "w")) == NULL) {
			printf("\n\t\tError. Cannot open id file.");
		}

		else {	
			fprintf(fp, "%d", start);
			fclose(fp);
			return 1;
		}
	}
	fscanf(fp, "%d", &num);
	num++;
	fclose(fp);
	
    if ((fp = fopen(filename, "w")) == NULL) {
		printf("\n\t\tError. Cannot open id file.");
	}

	else {
		fprintf(fp, "%d", num);
		fclose(fp);
		return num;
	}
}

int read_id() {//function automatically generates a number to be used as the order id and increments when a new record is added 
    int i;
    FILE * fp;
	if ((fp = fopen("data\\queueid.txt", "r")) == NULL) {
        printf("Error. Cannot open id file.");
    }//end if
    
	else {
		fscanf(fp, "%d", &i) ;
		fclose(fp) ;
	}
    return i;
}//end of funtion

int decrement_id() {//function automatically generates a number to be used as the order id and increments when a new record is added
    int i;
    FILE * fp;
	if ((fp = fopen("data\\queueid.txt", "w")) == NULL) {
        printf("Error. Cannot open id file.");
    }//end if
    
	else {
		fscanf(fp, "%d", &i);
		i-=1;
		fprintf(fp, "%d", i);
		fclose(fp) ;
	}
    return i;
}//end of funtion

int size() {
	return read_id()+1;
}

bool is_empty() {
	if (read_id()==-1) {
		printf("\n\t\tQueue is empty\n");
		return true;
	}
	else
		return false;
}

float checknum(int type) {
    float num;
    while(scanf("%f", &num)!=1) {
        printf("\n\t\tInput must be a number\n");
        printf("\n\t\tPlease re-enter.\n\t\t");
        while ((getchar()) != '\n');
    }
	if (type == 0)
    	return num;
	else if (type == 1)
		return (int)num;
}

void PrintLabel(char label[], bool is_start) {
	if(!is_start)
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\n\t|===============================================================|\n");
	printf("\t%s\n", label);
	printf("\t|===============================================================|\n\n");
}

int InvalidOption(int num) {
	printf("\n\t\tInvalid option.");
	printf("\n\t\tYou chose: ");
	return num = checknum(1);
}

void MenuPause() {
	while ((getchar()) != '\n');
	while ((getchar()) != '\n');
	menu();
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void CreateRecordFile(char filename[], int queue) {//function to create a file to store plant records
	FILE *fp;//file pointer
	if	((fp = fopen(filename, "rb")) == NULL) {
		if	((fp = fopen(filename, "wb")) == NULL) 
			printf("\n\t\tCannot open the file \n");
		
		else {
			printf("\n\n\t\tRecords File created.");
            if(queue==1)
                autoid("data\\queueid.txt", -1);
		}
	}//end if
	
	else
		printf("\n\n\t\tFile already exists.");
	fclose(fp);
}//end of funtion

void ViewQueue() {//View plant records
	struct QueueInfo queue[MAX_LENGTH] = {0, 0, 0.0, "", ""};
	struct QueueInfo element = {0, 0, 0.0, "", ""};
	int i;
	FILE *fp;//file pointer
	if	((fp = fopen("data\\queuedata.bin", "rb+")) == NULL)
		printf("\n\t\tCannot open file \n");
	
	else {
        is_empty(); 
		for (i=0; i<=read_id(); i++) {
			fread(&element, sizeof(struct QueueInfo), 1, fp);
			queue[i] = element;
			printf("\n\t\tId is: %d\n", queue[i].id);
			printf("\n\t\tCustomer Name is: %s\n", queue[i].name);
			printf("\n\t\tItem Name is: %s\n", queue[i].itemname);
			printf("\n\t\tAmount ordered is: %d\n", queue[i].quant);
			printf("\n\t\tAmount owed is: $%.2f\n", queue[i].owed);
			printf("--------------------------------------------------------------------");
		}//end if
	}//
    fclose(fp);
}//end of funtion

void ViewItem(char filename[]) {//View plant records
	struct ItemInfo item = {0, "", 0.0, 0.0, 0, 0.0, 0, 0.0};
	FILE *fp;//file pointer
	if	((fp = fopen(filename, "rb+")) == NULL)
		printf("\n\t\tCannot open file \n");

	else {
		while(fread(&item, sizeof(struct ItemInfo), 1, fp) == 1) {//while fread returns 1, i.e there are records still to be read in the file
			if (item.id != 0) {
				printf("\n\t\tItem Id is: %d\n", item.id);
				printf("\n\t\tItem Name is: %s\n", item.name);
				printf("\n\t\tCost Price is: $%.2f\n", item.cost);	
				printf("\n\t\tSale Price is: $%.2f\n", item.price);
				printf("\n\t\tAmount in stock is: %d\n", item.stock);
				printf("\n\t\tValue of stock is: $%.2f\n", item.stockvalue);
				printf("--------------------------------------------------------------------");
			}
		}//end while
	}
    fclose(fp);
}//end of funtion

void ViewSale() {//View sale records
	struct SaleInfo sale = {0, "", 0.0, {0, 0, 0}, {0, 0, 0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {"", "", ""}, {"", "", ""}, {0, 0, 0}, {0, 0, 0}, 0, 0, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 0.0, 0.0};
	int i, j;
	FILE *fptrsale;//file pointer
	if	((fptrsale = fopen("data\\saledata.bin", "rb+")) == NULL)
		printf("\n\t\tCannot open file \n");
	
	else {
		while(fread(&sale, sizeof(struct SaleInfo), 1, fptrsale)==1) {
			if (sale.saleid != 0) {
				printf("\n\t\tOrder Id is: %d\n", sale.saleid);
				printf("\n\t\tCustomer Name is: %s\n", sale.customername);
				if (sale.totequip > 0) {
					printf("\n\t\tEquipment Purchased:\n");
					for(i=0;i<sale.totequip;i++) {
						printf("\n\t\t\tItem Name: %s", sale.equipnames + i);
						printf("\n\t\t\tItem Id: %d", sale.equipids[i]);
						printf("\n\t\t\tItem price: $%.2f", sale.equipprice[i]);
						printf("\n\t\t\tQuantity of Item: %d",sale.equipquant[i]);
						printf("\n\t\t\tTotal for Item: $%.2f\n",sale.equiptotal[i]);
					}	
				}
				if(sale.totplant > 0) {
					printf("\n\t\tPlants Purchased:\n");
					for(j=0;j<sale.totplant;j++) {
						printf("\n\t\t\tItem Name: %s", sale.plantnames + j);
						printf("\n\t\t\tItem Id: %d", sale.plantids[j]);
						printf("\n\t\t\tItem price: $%.2f", sale.plantprice[j]);
						printf("\n\t\t\tQuantity of Item: %d",sale.plantquant[j]);
						printf("\n\t\t\tTotal for Item: $%.2f\n",sale.planttotal[j]);
					}	
				}
				printf("\n\t\tTotal is $%.2f\n", sale.cost);
				printf("--------------------------------------------------------------------");
			}//end if
		}//end while
	}//
	fclose(fptrsale);
}//end of funtion

void Enqueue() {
	struct QueueInfo queue[MAX_LENGTH] = {0, 0, 0.0, "", ""};
	struct QueueInfo element = {0, 0, 0.0, "", ""};	
	struct ItemInfo item = {0, "", 0.0, 0.0, 0, 0.0, 0, 0.0};
	float quantf;
    FILE *fp;
	FILE *fptr;
	if	((fp = fopen("data\\queuedata.bin", "rb+")) == NULL)
		printf("\n\t\tCannot open file \n");

	else {
		if	((fptr = fopen("data\\limitemdata.bin", "rb+")) == NULL)
			printf("\n\t\tCannot open file \n");

		else {
			if (size() == MAX_LENGTH)
				printf("\n\t\tQueue is full.");
			
			else {
				fread(&item, sizeof(struct ItemInfo), 1, fptr);
				printf("\n\t\tCustomer name is: ");
				scanf(" %[^\n]s", &element.name);
				printf("\n\t\tAmount requested is: ");
				element.quant = checknum(1);

				while (element.quant > LIMIT) {
					printf("\n\t\tPlease enter a number less than %d\n", LIMIT);
					printf("\n\t\tAmount requested is: ");
					element.quant = checknum(1);
				}
				while (element.quant > item.stock) {
					printf("\n\t\tPlease enter a number less than %d\n", item.stock);
					printf("\n\t\tAmount requested is: ");
					element.quant = checknum(1);		
				}
				element.owed = element.quant * item.price;
				element.id = autoid("data\\queueid.txt", 0);
				strcpy(element.itemname, item.name);
				queue[read_id()] = element;
				item.stock -= element.quant;
				item.stockvalue = item.price*item.stock;
				
				fseek(fptr, (item.id-1) * sizeof(struct ItemInfo), SEEK_SET);//moves file pointer to the beginning of the file
				fwrite(&item, sizeof(struct ItemInfo), 1, fptr);//write record to file

				fseek(fp, (read_id()) * sizeof(struct QueueInfo), SEEK_SET);//moves file pointer to the beginning of the file
				fwrite(&queue[read_id()], sizeof(struct QueueInfo), 1, fp);//write record to file
			}
		}
	}
	fclose(fp);
	fclose(fptr);
}

void AddItem(char type[], char filename[], char mode[]) {//Add a new plant record
	struct ItemInfo item = {0, "", 0.0, 0.0, 0, 0.0, 0, 0.0};
	float cost;
	FILE * fp;//file pointer
	if	((fp = fopen(filename, mode)) == NULL)
		printf("\n\t\tCannot open file \n");
	
	else {
		printf("\n\t\tItem name is: ");
		scanf(" %[^\n]s", &item.name);
		printf("\n\t\tItem Cost Price is: ");
		cost = checknum(0);
		item.cost = cost;
		item.price = item.cost*MARKUP;
		printf("\n\t\tAmount in stock is: ");
		item.stock = checknum(1); 
		item.ogstock = item.stock;
		item.stockvalue = item.price*item.stock; 
		item.ogstockvalue = item.stockvalue;
		if(stricmp("rb+", mode) != 0)
			item.id = autoid(type, 1);
		else
			item.id = 1;
		fseek(fp, (item.id-1) * sizeof(struct ItemInfo), SEEK_SET);//moves file pointer to the beginning of the file
		fwrite(&item, sizeof(struct ItemInfo), 1, fp);//write record to file
	}//
	fclose(fp);
}//end of funtion

void AddToSale(int type, char name[], int update, char mode[], int id) {
	struct SaleInfo sale = {0, "", 0.0, {0, 0, 0}, {0, 0, 0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {"", "", ""}, {"", "", ""}, {0, 0, 0}, {0, 0, 0}, 0, 0, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 0.0, 0.0};
	struct ItemInfo plant = {0, "", 0.0, 0.0, 0, 0.0, 0, 0.0};
	struct ItemInfo equipment = {0, "", 0.0, 0.0, 0, 0.0, 0, 0.0};
	FILE *fptrsale;//file pointer
    FILE*fptrplant;
    FILE*fptrequip;
    int i = 0, j = 0, num = 0, num2 = 0, idp, ide, plantnum, equipnum;
    if	(((fptrequip = fopen("data\\equipdata.bin", "rb+")) == NULL) || ((fptrplant = fopen("data\\plantdata.bin", "rb+")) == NULL) || ((fptrsale = fopen("data\\saledata.bin", mode)) == NULL))
        printf("\n\t\tCannot open file \n");
    
    else {
        strcpy(sale.customername, name); 
        if (type == 2 || type == 3) {
            printf("\n\t\t|======================================================|\n");
            printf("\t\t|>>>>>>>>>>>>>>>>>> EQUIPMENT INFO <<<<<<<<<<<<<<<<<<<<|\n");
            printf("\t\t|======================================================|\n\n");
            ViewItem("data\\equipdata.bin");
            if(update == 1) {
                sale.cost -= sale.equiptotfee;
                sale.equiptotfee = 0;
            }
            do {
                printf("\n\n\t\tEnter id of the equipment purchased.\n\t\t");
                ide = checknum(1);
            
                fseek(fptrequip, (ide-1) * sizeof(struct ItemInfo), SEEK_SET);
                fread(&equipment, sizeof(struct ItemInfo), 1, fptrequip);//reads a block of data
                
                while(equipment.id == 0) {
                    printf("\n\n\t\tItem not found.");
                    printf("\n\t\tEnter a different id.\n\t\t");
                    ide = checknum(1);
                    
                    fseek(fptrequip, (ide-1) * sizeof(struct ItemInfo), SEEK_SET);
                    fread(&equipment, sizeof(struct ItemInfo), 1, fptrequip);
                }
                
                while(equipment.stock == 0) {
                    printf("\n\n\t\tItem out of stock.");
                    printf("\n\t\tEnter a different id.\n\t\t");
                    ide = checknum(1);
                    
                    fseek(fptrequip, (ide-1) * sizeof(struct ItemInfo), SEEK_SET);
                    fread(&equipment, sizeof(struct ItemInfo), 1, fptrequip);//reads a block of data
                }
                
                printf("\n\t\tEnter the quantity of this item that the customer purchased.\n\t\t");
                equipnum = checknum(1);
                
                while (equipnum>equipment.stock) {
                    printf("\n\t\tNot enough in stock. Please enter a value less than %d", equipment.stock);
                    printf("\n\t\tEnter the quantity of this item that the customer purchased.\n\t\t");
                    equipnum = checknum(1);
                }
                
                sale.equipquant[i] = equipnum;
                sale.equipids[i] = ide;
                strcpy(sale.equipnames[i], equipment.name);
                sale.equipprice[i] = equipment.price;
                sale.equiptotal[i] = sale.equipprice[i]*sale.equipquant[i];
                sale.equiptotfee += sale.equiptotal[i];
                sale.cost += sale.equiptotal[i];
                
                if(update==1) {
                    equipment.stock=equipment.ogstock;
                    equipment.stockvalue=equipment.ogstockvalue;								
                }
                equipment.stock -= sale.equipquant[i];
                equipment.stockvalue -= sale.equiptotal[i];
                
                fseek(fptrequip, (equipment.id-1) * sizeof(struct ItemInfo),SEEK_SET);//moves file pointer to the beginning of the file
                fwrite(&equipment, sizeof(struct ItemInfo), 1, fptrequip);//write record to file
                
                i++;
                sale.totequip++;
                printf("\n\t\tEnter -1 to stop adding items to the order. Enter 0 to continue adding items.\n\t\t");
                num = checknum(1);

                if (num == -1)
                    break;
            }
            while (num == 0);
        } 

        if (type == 1 || type == 3) {
            printf("\n\t\t|==================================================|\n");
            printf("\t\t|>>>>>>>>>>>>>>>>>> PLANT INFO <<<<<<<<<<<<<<<<<<<<|\n");
            printf("\t\t|==================================================|\n\n");
            ViewItem("data\\plantdata.bin");
            if(update==1) {
                sale.cost -= sale.planttotfee;
                sale.planttotfee = 0;                
            }
            do {
                printf("\n\n\t\tEnter id of the plant purchased.\n\t\t");
                idp = checknum(1);
                
                fseek(fptrplant, (idp-1) * sizeof(struct ItemInfo), SEEK_SET);
                fread(&plant, sizeof(struct ItemInfo), 1, fptrplant);//reads a block of data
                
                while(plant.id == 0) {
                    printf("\n\n\t\tItem not found.");
                    printf("\n\t\tEnter a different plant id.\n\t\t");
                    idp = checknum(1);
                        
                    fseek(fptrplant, (idp-1) * sizeof(struct ItemInfo), SEEK_SET);
                    fread(&plant, sizeof(struct ItemInfo), 1, fptrplant);
                }
                
                while(plant.stock == 0) {
                    printf("\n\n\t\tItem out of stock.");
                    printf("\n\t\tEnter a different plant id.\n\t\t");
                    idp = checknum(1);
                
                    fseek(fptrplant, (idp-1) * sizeof(struct ItemInfo), SEEK_SET);
                    fread(&plant, sizeof(struct ItemInfo), 1, fptrplant);
                }
                
                printf("\n\t\tEnter the quantity of this item that the customer purchased.\n\t\t");
                plantnum = checknum(1);
                
                if (plantnum>plant.stock) {
                    printf("\n\t\tNot enough in stock. Please enter a value less than %d", plant.stock);
                    printf("\n\t\tEnter the quantity of this item that the customer purchased.\n\t\t");
                    plantnum = checknum(1);
                }
                
                sale.plantquant[j] = plantnum;
                sale.plantids[j] = idp;
                strcpy(sale.plantnames[j], plant.name);
                sale.plantprice[j] = plant.price;
                sale.planttotal[j] = sale.plantprice[j]*sale.plantquant[j];
                sale.planttotfee = sale.planttotal[j];
                sale.cost += sale.planttotal[j];
                
                if(update==1) {
                    plant.stock = plant.ogstock;
                    plant.stockvalue = plant.ogstockvalue;                    
                }
                plant.stock -= sale.plantquant[j];
                plant.stockvalue -= sale.planttotal[j];
                
                fseek(fptrplant, (plant.id-1)*sizeof(struct ItemInfo),SEEK_SET);//moves file pointer to the beginning of the file
                fwrite(&plant, sizeof(struct ItemInfo), 1, fptrplant);//write record to the file
                
                j++;
                sale.totplant++;
                printf("\n\t\tEnter -1 to stop adding items to the order. Enter 0 to continue adding items.\n\t\t");
                num2 = checknum(1);
                
                if (num2 == -1)
                    break;
            }
            while (num2 == 0);
        }
    }//
    if(update!=1)
        sale.saleid = autoid("data\\saleid.txt", 1);
    else
        sale.saleid = id;
    fseek(fptrsale, (sale.saleid-1) * sizeof(struct SaleInfo),SEEK_SET);//moves file pointer to the beginning of the file
    fwrite(&sale, sizeof(struct SaleInfo), 1, fptrsale);//write record to file
    fclose(fptrsale);
    fclose(fptrequip);
    fclose(fptrplant);
}

void AddSale() {//Add a new sale record
	int choice, truth = 0;
	char name[SIZE];

	printf("\n\t\tCustomer name is: ");
	scanf(" %[^\n]s", &name);
	
	printf("\n\t\tWhat items did the customer purchase?");
	printf("\n\t\t1. Plants.\n\t\t2. Equipment.\n\t\t3. Plants and Equipment.\n\t\t");
	choice = checknum(1);
	
	while(truth != 1) {
		switch(choice) {
			case 1:
				truth = 1;
				AddToSale(1, name, 0, "ab+", 0);
			break;
			
			case 2:
				truth = 1;
				AddToSale(2, name, 0, "ab+", 0);
			break;
			
			case 3:
				truth = 1;
				AddToSale(3, name, 0, "ab+", 0);
			break;

			default:
			printf("\n\t\tInvalid option\n");
			printf("\n\t\tWhat items did the customer purchase?");
			printf("\n\t\t1. Plants.\n\t\t2. Equipment.\n\t\t3. Plants and Equipment.\n\t\t");
			choice = checknum(1);
			break;
		}
	}//end while
}//end of funtion

void SearchItem(char filename[], int action) {//Search for a plant record
    struct ItemInfo item = {0, "", 0.0, 0.0, 0, 0.0, 0, 0.0};
	struct ItemInfo delete = {0, "", 0.0, 0.0, 0, 0.0, 0, 0.0};
	int choice, truth = 0, id, found = 0, option;
	float cost;
    char name[SIZE]; 
	FILE *fp;//file pointer
	if	((fp = fopen(filename, "rb+")) == NULL)
		printf("\n\t\tCannot open file \n");

    else {
        printf("\n\t\t1. Search by name.");
        printf("\n\t\t2. Search by ID.\n\t\t");
        choice = checknum(1);
        
        while(truth != 1) {
            switch (choice) {
                case 1:
                truth = 1;
                printf("\n\t\tEnter name of the record that you want to find.\n");
                printf("\t\tYou chose: ");
                scanf(" %[^\n]s", &name);//allows spaces to be read
                
                while(fread(&item, sizeof(struct ItemInfo), 1, fp)==1) {   
                    if(stricmp(name, item.name)==0) {
					    found=1;
						break;
					}
                }
				break;
                
                case 2:
                truth = 1;
                printf("\n\t\tEnter id of the record to find.");
                printf("\n\n\t\tYou chose: ");
                id = checknum(1);
                
                fseek(fp, (id-1) * sizeof(struct ItemInfo), SEEK_SET);
                fread(&item, sizeof(struct ItemInfo), 1, fp);//reads a block of data
                
                if(item.id != 0)
                    found=1;
                break;
                    
                default:
                choice = InvalidOption(choice);
                break;
            }//end switch
        }//end while

        if(found == 1) {
			truth = 0;
            printf("\n\t\tId is: %d\n", item.id);
            printf("\n\t\tItem Name is: %s\n", item.name);
            printf("\n\t\tCost Price is: $%.2f\n", item.cost);	
            printf("\n\t\tSale Price is: $%.2f\n", item.price);
            printf("\n\t\tAmount in stock is: %d\n", item.stock);
            printf("\n\t\tValue of stock is: $%.2f\n", item.stockvalue);  
			
			if (action == 1) {
				printf("\n\t\tAre you sure you want to delete this record?\n");
				printf("\t\t1 - yes\n\t\t2 - no\n");
				printf("\n\t\tYou chose: ");
				choice = checknum(1);
				
				while(truth != 1) {
					switch (choice) {
						case 1:
						truth = 1;
						printf("\n\t\tRecord Deleted");
						fseek(fp, (item.id-1) * sizeof(struct ItemInfo), SEEK_SET);//moves file pointer to the beginning of the file
						fwrite(&delete, sizeof(struct ItemInfo), 1, fp);//deletes record by overwriting with a blank record
						break;
						
						case 2:
						truth = 1;
						break;
							
						default:
						choice = InvalidOption(choice);
						break;
					}
				}				
			}

			else if (action == 2) {
				printf("\n\t\tAre you sure you want to update this record.");
				printf("\n\t\t1 - yes\n\t\t2 - no\n");
				printf("\n\t\tYou chose: ");
				option = checknum(1);
				
				while(truth != 1) {
					switch (option) {	
						case 1:
						truth = 1;
						printf("\n\t\tNew name is: ");
						scanf(" %[^\n]s", &item.name);
						printf("\n\t\tNew Cost Price is: ");
						cost = checknum(0);
						item.cost = cost;
						item.price = item.cost*MARKUP;
						printf("\n\t\tNew Amount in stock is: ");
						item.stock = checknum(1);
						item.ogstock = item.stock;
						item.stockvalue = item.price*item.stock; 
						item.ogstockvalue = item.stockvalue;
				
						fseek(fp, (item.id-1)*sizeof(struct ItemInfo),SEEK_SET);//moves file pointer to the beginning of the file
						fwrite(&item, sizeof(struct ItemInfo), 1, fp);//write record to the file
						break;	
					
						case 2:
						truth = 1;
						break;
						
					default:
					option = InvalidOption(option);
					break;
					}//end switch
				}//end while				
			}
        }//end if
        
        else if (found == 0)
            printf("\n\t\tRecord not found.\n");
    }
    fclose(fp);
}//end of funtion


void SearchSale(int action) {//Search for a sale record
	struct SaleInfo sale = {0, "", 0.0, {0, 0, 0}, {0, 0, 0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {"", "", ""}, {"", "", ""}, {0, 0, 0}, {0, 0, 0}, 0, 0, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 0.0, 0.0};
	struct SaleInfo deletesale = {0, "", 0.0, {0, 0, 0}, {0, 0, 0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {"", "", ""}, {"", "", ""}, {0, 0, 0}, {0, 0, 0}, 0, 0, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 0.0, 0.0};
	int choice, truth = 0, found = 0, id, i=0 ,j=0, type;
    char name[SIZE]; 
	FILE *fptrsale;//file pointer
	if	((fptrsale = fopen("data\\saledata.bin", "rb+")) == NULL)
		printf("\n\t\tCannot open file \n");

    else {
        printf("\n\t\t1. Search by name.");
        printf("\n\t\t2. Search by ID.\n\t\t");
        choice = checknum(1);
        
        while(truth != 1) {
            switch (choice) {
                case 1:
                truth = 1;
                printf("\n\t\tEnter customer name of the record that you want to find.\n");
                printf("\t\tYou chose: ");
                scanf(" %[^\n]s", &name);//allows spaces to be read
                
                while(fread(&sale, sizeof(struct SaleInfo), 1, fptrsale)==1) {   
                    if(stricmp(name, sale.customername)==0) {                              
                        found=1;
                        break;
                    }
                }
                break;
                
                case 2:
                truth = 1;
                printf("\n\t\tEnter id of the record to find.");
                printf("\n\n\t\tYou chose: ");
                id = checknum(1);
                
                fseek(fptrsale, (id-1) * sizeof(struct SaleInfo), SEEK_SET);
                fread(&sale, sizeof(struct SaleInfo), 1, fptrsale);//reads a block of data
            
                if(sale.saleid != 0)
                    found=1;
                break;
                
                default:
                choice = InvalidOption(choice);
                break;
            }//end switch
        }//end while

        if (found == 1) {
			truth = 0;
            printf("\n\t\tOrder Id is: %d\n", sale.saleid);
            printf("\n\t\tCustomer Name is: %s\n", sale.customername);
            if (sale.totequip > 0) {
                printf("\n\t\tEquipment Purchased:\n");
                for(i=0;i<sale.totequip;i++) {
                    printf("\n\t\t\tItem Name: %s", sale.equipnames + i);
                    printf("\n\t\t\tItem Id: %d", sale.equipids[i]);
                    printf("\n\t\t\tItem price: $%.2f", sale.equipprice[i]);
                    printf("\n\t\t\tQuantity of Item: %d",sale.equipquant[i]);
                    printf("\n\t\t\tTotal for Item: $%.2f\n",sale.equiptotal[i]);
                }	
            }
            
            if(sale.totplant > 0) {
                printf("\n\t\tPlants Purchased:\n");
                for(j=0;j<sale.totplant;j++)
                {
                    printf("\n\t\t\tItem Name: %s", sale.plantnames + j);
                    printf("\n\t\t\tItem Id: %d", sale.plantids[j]);
                    printf("\n\t\t\tItem price: $%.2f", sale.plantprice[j]);
                    printf("\n\t\t\tQuantity of Item: %d",sale.plantquant[j]);
                    printf("\n\t\t\tTotal for Item: $%.2f\n",sale.planttotal[j]);
                }	
            }
            printf("\n\t\tTotal is $%.2f\n", sale.cost);	

			if (action == 1) {
				printf("\n\t\tAre you sure you want to delete this record?\n");
				printf("\t\t1 - yes\n\t\t2 - no\n");
				printf("\n\t\tYou chose: ");
				choice = checknum(1);
				
				while(truth != 1) {
					switch (choice) {
						case 1:
						truth = 1;
						printf("\n\t\tRecord Deleted");
						fseek(fptrsale, (sale.saleid-1) * sizeof(struct SaleInfo),SEEK_SET);//moves file pointer to the beginning of the file
						fwrite(&deletesale, sizeof(struct SaleInfo), 1, fptrsale);//write record to file
						break;
						
						case 2:
						truth = 1;
						break;
						
						default:
						choice = InvalidOption(choice);
						break;
					}//end switch	
				}//end while
			}

			else if (action == 2) {
				printf("\n\t\tAre you sure you want to update this record?\n");
				printf("\t\t1 - yes\n\t\t2 - no\n");
				printf("\n\t\tYou chose: ");
				choice = checknum(1);
				
				while(truth != 1) {
					switch (choice) {
						case 1:
						truth = 1;	
                        printf("\n\t\tCustomer name is: ");
                        scanf(" %[^\n]s", &name);
                        printf("\n\t\tWhat items did the customer purchase?");
                        printf("\n\t\t1. Plants.\n\t\t2. Equipment.\n\t\t3. Plants and Equipment.\n\t\t");
                        type = checknum(1);
                        AddToSale(type, name, 1, "rb+", sale.saleid);
                        break;

                        case 2:
                        truth = 1;
                        break;

						default:
						choice = InvalidOption(choice);
						break;                        
					}
				}//end if
            }
		}

        if(found == 0)
            printf("\n\t\tRecord not found.\n");
    }
}//end of funtion

void Dequeue() {
	struct QueueInfo queue[MAX_LENGTH] = {0, 0, 0.0, "", ""};
	struct QueueInfo element = {0, 0, 0.0, "", ""};
	int i, truth = 0, choice;
	FILE *fp;//file pointer
	if	((fp = fopen("data\\queuedata.bin", "rb+")) == NULL)
		printf("\n\t\tCannot open file \n");
	
	else {
		if (!is_empty()) {
			printf("\n\t\tAre you sure you want to dequeue?\n");	
			printf("\t\t1 - yes\n\t\t2 - no\n");
			printf("\n\t\tYou chose: ");
			choice = checknum(1);
			
			while(truth != 1) {
				switch (choice) {
					case 1:
					truth = 1;
					for (i = 0; i <= read_id(); i++) {
						fread(&element, sizeof(struct QueueInfo), 1, fp);
						queue[i] = element;
						queue[i].id -= 1;
					}

					for (i = 0; i <= read_id(); i++) {
						queue[i] = queue[i+1];
					}
					decrement_id();
				
					for (i = 0; i <= read_id(); i++) {
						fseek(fp, (i) * sizeof(struct QueueInfo), SEEK_SET); 
						fwrite(&queue[i], sizeof(struct QueueInfo), 1, fp);  
					}
					break;
					
					case 2:
					truth = 1;
					break;
					
					default:
					choice = InvalidOption(choice);
					break;
				}//end switch
			}//end while
		}
	}//
    fclose(fp);
}

void CreateFile() {//Sub menu to allow user to select what type of file they would like to create
	int option, truth = 0;
	
	printf("\n\tWhat type of file would you like to create.\n\n");
	printf("\t0. Exit to main menu.\n\n");
	printf("\t1. Create a file for plant records.\n\n");
	printf("\t2. Create a file for equipment records.\n\n");
	printf("\t3. Create a file for limited item records.\n\n");
	printf("\t4. Create a file for sale records.\n\n");
	printf("\t5. Create a file for queue.\n\n");
	printf("\t\tYou chose: ");
	option = checknum(1);
	printf("\n\t--------------------------------------------------------------------");
	
	while(truth != 1) {
		switch(option) {
			case 0:
			truth = 1;
			break;
			
			case 1:
			truth = 1;
			CreateRecordFile("data\\plantdata.bin", 0);
			break;
			
			case 2:
			truth = 1;
			CreateRecordFile("data\\equipdata.bin", 0);
			break;

			case 3:
			truth = 1;
			CreateRecordFile("data\\limitemdata.bin", 0);
			break;

			case 4:
			truth = 1;
			CreateRecordFile("data\\saledata.bin", 0);
			break;

			case 5:
			truth = 1;
			CreateRecordFile("data\\queuedata.bin", 1);
			break;
			
			default:
			option = InvalidOption(option);
			break;
		}//end switch
	}//end while
	printf("\n\n\t\tPress enter to return to the main menu.\n\t\t");
}//end of funtion

void View() {//sub menu allows user to select what type of record to view
	int option, truth = 0;
	
	printf("\n\tWhat type of record would you like to view?\n\n");
	printf("\t0. Exit to main menu.\n\n");
	printf("\t1. View plant record.\n\n");
	printf("\t2. View equipment record.\n\n");
	printf("\t3. View sale record.\n\n");
	printf("\t4. View limited item.\n\n");
	printf("\t5. View queue.\n\n");
	printf("\t\tYou chose: ");
	option = checknum(1);
	printf("\n\t--------------------------------------------------------------------");
	
	while(truth != 1) {
		switch(option) {
			case 0:
			truth = 1;
			break;
			
			case 1:
			truth = 1;
			PrintLabel("|>>>>>>>>>>>>>>>>>>>>>>>>> PLANT INFO <<<<<<<<<<<<<<<<<<<<<<<<<<|", false);
			ViewItem("data\\plantdata.bin");
			break;
			
			case 2:
			truth = 1;
			PrintLabel("|>>>>>>>>>>>>>>>>>>>>>>> EQUIPMENT INFO <<<<<<<<<<<<<<<<<<<<<<<<|", false);
			ViewItem("data\\equipdata.bin");
			break;
				
			case 3:
			truth = 1;
			PrintLabel("|>>>>>>>>>>>>>>>>>>>>>>>>> SALE INFO <<<<<<<<<<<<<<<<<<<<<<<<<<<|", false);
			ViewSale();
			break;

			case 4:
			truth = 1;
			PrintLabel("|>>>>>>>>>>>>>>>>>>>>> LIMITED ITEM INFO <<<<<<<<<<<<<<<<<<<<<<<|", false);
			ViewItem("data\\limitemdata.bin");
			break;

			case 5:
			truth = 1;
			PrintLabel("|>>>>>>>>>>>>>>>>>>>>>>>>> QUEUE INFO <<<<<<<<<<<<<<<<<<<<<<<<<<|", false);
			ViewQueue();
			break;
			
			default:
			option = InvalidOption(option);
			break;
		}//end switch
	}//end while
	printf("\n\n\t\tPress enter to return to the main menu.\n\t\t");
}//end of funtion 

void Add() {//sub menu allows user to select what type of record to add
	int option, truth = 0;

	printf("\n\tWhat type of record would you like to add?\n\n");
	printf("\t0. Exit to main menu.\n\n");
	printf("\t1. Add plant record.\n\n");
	printf("\t2. Add equipment record.\n\n");
	printf("\t3. Add sale record.\n\n");
	printf("\t4. Add limited item.\n\n");
	printf("\t\tYou chose: ");
	option = checknum(1);
	printf("\n\t--------------------------------------------------------------------");
	
	while(truth != 1) {
		switch(option) {
			case 0:	
			truth = 1;
			break;
			
			case 1:
			truth = 1;
			PrintLabel("|>>>>>>>>>>>>>>>>>>>> ADD PLANT RECORD <<<<<<<<<<<<<<<<<<<<<<|", false);
	  		AddItem("data\\plantid.txt", "data\\plantdata.bin", "ab+");
			break;
			
			case 2:
			truth = 1;
			PrintLabel("|>>>>>>>>>>>>>>>>>>> ADD EQUIPMENT RECORD <<<<<<<<<<<<<<<<<<<<<<|", false);
	  		AddItem("data\\equipid.txt", "data\\equipdata.bin", "ab+");
			break;
			
			case 3:
			truth = 1;
			PrintLabel("|>>>>>>>>>>>>>>>>>>>>>> ADD SALE RECORD <<<<<<<<<<<<<<<<<<<<<<<<|", false);
	  		AddSale();
			break;

			case 4:
			truth = 1;
			PrintLabel("|>>>>>>>>>>>>>>>>>>>>> ADD LIMITED ITEM <<<<<<<<<<<<<<<<<<<<<<<<|", false);
	  		AddItem("data\\limitem.txt", "data\\limitemdata.bin", "rb+");
			break;
			
			default:
			option = InvalidOption(option);
			break;
		}//end switch
	}//end while
	printf("\n\n\t\tPress enter to return to the main menu.\n\t\t");
}//end of funtion 

void Search() {//sub menu allows user to select what type of record to search for
	int option, truth = 0;
	
	printf("\n\tWhat type of record would you like to search?\n\n");
	printf("\t0. Exit to main menu.\n\n");
	printf("\t1. Search plant record.\n\n");
	printf("\t2. Search equipment record.\n\n");
	printf("\t3. Search sale record.\n\n");
	printf("\t\tYou chose: ");
	option = checknum(1);
	printf("\n\t--------------------------------------------------------------------");
	
	while(truth != 1) {
		switch(option) {
			case 0:
			truth = 1;
			break;
			
			case 1:
			truth = 1;
			PrintLabel("|>>>>>>>>>>>>>>>>>>>> SEARCH PLANT RECORD <<<<<<<<<<<<<<<<<<<<<<|", false);
			SearchItem("data\\plantdata.bin", 0);
			break;
			
			case 2:
			truth = 1;
			PrintLabel("|>>>>>>>>>>>>>>>>>> SEARCH EQUIPMENT RECORD <<<<<<<<<<<<<<<<<<<<|", false);
			SearchItem("data\\equipdata.bin", 0);
			break;
			
			case 3:
			truth = 1;
			PrintLabel("|>>>>>>>>>>>>>>>>>>>>> SEARCH SALE RECORD <<<<<<<<<<<<<<<<<<<<<<|", false);
			SearchSale(0);
			break;
			
			default:
			option = InvalidOption(option);
			break;
		}//end switch
	}//end while
	printf("\n\n\t\tPress enter to return to the main menu.\n\t\t");
}//end of funtion 

void Update() {//sub menu allows user to select what type of record to update
	int option, truth = 0;
	
	printf("\n\tWhat type of record would you like to update?\n\n");
	printf("\t0. Exit to main menu.\n\n");
	printf("\t1. Update plant record.\n\n");
	printf("\t2. Update equipment record.\n\n");
	printf("\t3. Update sale record.\n\n");
	printf("\t\tYou chose: ");
	option = checknum(1);
	printf("\n\t--------------------------------------------------------------------");
	
	while(truth != 1) {
		switch(option) {
			case 0:
			truth = 1;
			break;
			
			case 1:
			truth = 1;
			PrintLabel("|>>>>>>>>>>>>>>>>>>>> UPDATE PLANT RECORD <<<<<<<<<<<<<<<<<<<<<<|", false);
	  		SearchItem("data\\plantdata.bin", 2);
			break;
			
			case 2:
			truth = 1;
			PrintLabel("|>>>>>>>>>>>>>>>>>> UPDATE EQUIPMENT RECORD <<<<<<<<<<<<<<<<<<<<|", false);
			SearchItem("data\\equipdata.bin", 2);
			break;
			
			case 3:
			truth = 1;
			PrintLabel("|>>>>>>>>>>>>>>>>>>>> UPDATE SALE RECORD <<<<<<<<<<<<<<<<<<<<<<<|", false);
			SearchSale(2);
			break;
			
			default:
			option = InvalidOption(option);
			break;
		}//end switch
	}//end while
	printf("\n\n\t\tPress enter to return to the main menu.\n\t\t");
}//end of funtion 

void Delete() {//sub menu allows user to select what type of record to delete
	int option, truth = 0;
	
	printf("\n\tWhat type of record would you like to delete?\n\n");
	printf("\t0. Exit to main menu.\n\n");
	printf("\t1. Delete plant record.\n\n");
	printf("\t2. Delete equipment record.\n\n");
	printf("\t3. Delete sale record.\n\n");
	printf("\t\tYou chose: ");
	option = checknum(1);
	printf("\n\t--------------------------------------------------------------------");
	
	while(truth != 1) {
		switch(option) {
			case 0:
			truth = 1;
			break;
			
			case 1:
			truth = 1;
			PrintLabel("|>>>>>>>>>>>>>>>>>>>> DELETE PLANT RECORD <<<<<<<<<<<<<<<<<<<<<<|", false);
			SearchItem("data\\plantdata.bin", 1);
			break;
			
			case 2:
			truth = 1;
			PrintLabel("|>>>>>>>>>>>>>>>>>> DELETE EQUIPMENT RECORD <<<<<<<<<<<<<<<<<<<<|", false);
			SearchItem("data\\equipdata.bin", 1);
			break;
			
			case 3:
			truth = 1;
			PrintLabel("|>>>>>>>>>>>>>>>>>>>>> DELETE SALE RECORD <<<<<<<<<<<<<<<<<<<<<<|", false);
			SearchSale(1);
			break;
			
			default:
			option = InvalidOption(option);
			break;
		}
	}
	printf("\n\n\t\tPress enter to return to the main menu.\n\t\t");
}//end of funtion 

void Queue() {
	int option, truth = 0;
	
	printf("\n\tWhat type of record would you like to delete?\n\n");
	printf("\t0. Exit to main menu.\n\n");
	printf("\t1. Add to Queue.\n\n");
	printf("\t2. Remove from Queue.\n\n");	
	printf("\t\tYou chose: ");
	option = checknum(1);
	printf("\n\t--------------------------------------------------------------------");
	
	while(truth != 1) {
		switch(option) {
			case 0:
			truth = 1;
			break;
			
			case 1:
			truth = 1;
			PrintLabel("|>>>>>>>>>>>>>>>>>>>>>>>> ADD TO QUEUE <<<<<<<<<<<<<<<<<<<<<<<<<|", false);
			Enqueue();
			break;

			case 2:
			truth = 1;
			PrintLabel("|>>>>>>>>>>>>>>>>>>>>> REMOVE FROM QUEUE <<<<<<<<<<<<<<<<<<<<<<<|", false);
			Dequeue();
			break;
		
			default:
			option = InvalidOption(option);
			break;
		}
	}
	printf("\n\n\t\tPress enter to return to the main menu.\n\t\t");
}

void menu() {//give user a list of choices
	int choice, truth = 0;
	mkdir("data");
	PrintLabel("|>>>>>>>>>>>>>>>>>>>> PLANT SHOP DATABASE <<<<<<<<<<<<<<<<<<<<<<|", false);
    printf("\n\t0.\tExit.\n");
    printf("\n\t1.\tCreate database.\n");
    printf("\n\t2.\tView records.\n");
	printf("\n\t3.\tAdd records.\n");
    printf("\n\t4.\tSearch records.\n");
	printf("\n\t5.\tUpdate records.\n");
    printf("\n\t6.\tDelete records.\n");
	printf("\n\t7.\tEdit Queue.\n");
    printf("\n\t\tYou chose: ");
	choice = checknum(1);
	
	while(truth != 1) {
        switch(choice) {
        	case 0:
        	truth = 1;
        	printf("\n\t\tExiting...");
        	exit(1);
        	break;
        	
        	case 1:
        	truth = 1;
			PrintLabel("|>>>>>>>>>>>>>>>>>>>>>>>>> CREATE FILE <<<<<<<<<<<<<<<<<<<<<<<<<|", false);
        	CreateFile();
            MenuPause();
        	break;

            case 2:
            truth = 1;
			PrintLabel("|>>>>>>>>>>>>>>>>>>>>>>>> VIEW RECORDS <<<<<<<<<<<<<<<<<<<<<<<<<|", false);
            View();
            MenuPause();
            break;
            
            case 3:
            truth = 1;
			PrintLabel("|>>>>>>>>>>>>>>>>>>>>>>>> ADD RECORDS <<<<<<<<<<<<<<<<<<<<<<<<<<|", false);
		    Add();
            MenuPause();
            break;
			
			case 4:
			truth = 1;
			PrintLabel("|>>>>>>>>>>>>>>>>>>>>>>> SEARCH RECORDS <<<<<<<<<<<<<<<<<<<<<<<<|", false);
            Search();
            MenuPause();
            break;
            	
            case 5:
            truth = 1;
			PrintLabel("|>>>>>>>>>>>>>>>>>>>>>>> UPDATE RECORDS <<<<<<<<<<<<<<<<<<<<<<<<|", false);
            Update();
            MenuPause();
            break;

            case 6:
            truth = 1;
            PrintLabel("|>>>>>>>>>>>>>>>>>>>>>>> DELETE RECORDS <<<<<<<<<<<<<<<<<<<<<<<<|", false);
            Delete();
            MenuPause();
            break;

            case 7:
            truth = 1;
            PrintLabel("|>>>>>>>>>>>>>>>>>>>>>>>>> EDIT QUEUE <<<<<<<<<<<<<<<<<<<<<<<<<<|", false);
            Queue();
			MenuPause();
            break;
       
			default:
			choice = InvalidOption(choice);
			break;
        }//end switch
    }//end while
}//end of function

void Password() {//function to prompt user to enter the password. Exits the program if the password is entered wrongly three times
	char guess[SIZE];
	int i;
	
	for (i = 3; i > 0; i--) {
		printf("\n\tEnter the password to access the database.\n\tPassword: ");
		gets(guess);
		
		if ((strcmp(guess, PASSWORD)) == 0)
			menu();
		else {
			if (i > 2)
				printf("\tWrong. You have %d tries left.\n", i-1);	
			if (i == 2)
				printf("\tWrong. You have %d try left.\n", i-1);
			if (i == 1) {
				printf("\tWrong. You have entered the incorrect password too many times.\n\tExiting...");
				exit(1);
			}//end if
		}//
	}//end for
}//end of function

int main() {
	PrintLabel("|>>>>>>>>>>>>>>>>>>>> PLANT SHOP DATABASE <<<<<<<<<<<<<<<<<<<<<<|", true);
	Password();
    return 0;
}