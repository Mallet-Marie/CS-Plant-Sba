#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PASSWORD "guess"
#define SIZE 50
#define MARKUP 1.5

struct PlantInfo
{
	int plantid;
	char plantname[SIZE];
	float plantcost;
	float plantprice;
	int plantstock;
	float plantstockvalue;
	int ogplantstock;
	float ogplantstockvalue;
};

struct EquipInfo
{
	int equipid;
	char equipname[SIZE];
	float equipcost;
	float equipprice;
	int equipstock;
	float equipstockvalue;
	int ogequipstock;
	float ogequipstockvalue;
};

struct SaleInfo
{
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
};

int autoidplant()//function automatically generates a number to be used as the plant id and increments when a new record is added
{
    int i;
    FILE * fp;
	if ((fp = fopen("autoidplant.txt", "r")) == NULL)
	{
        if ((fp = fopen("autoidplant.txt", "w")) == NULL)
        {
        	printf("Error. Cannot open id file.");
		}
        fprintf(fp, "%d", 1);
        fclose(fp);
        return 1;
    }//end if
    
    fscanf(fp, "%d", &i);
    i++;

    fclose(fp); 
    fp = fopen("autoidplant.txt", "w"); 
    fprintf(fp, "%d", i);
    fclose(fp);
    return i;
}//end of funtion

int autoidequip()//function automatically generates a number to be used as the equipment id and increments when a new record is added
{
    int i ;
    FILE * fp;
	if ((fp = fopen("autoidequip.txt", "r")) == NULL)
	{
        if ((fp = fopen("autoidequip.txt", "w")) == NULL)
        {
        	printf("Error. Cannot open id file.");
		}
        fprintf(fp, "%d", 1) ;
        fclose(fp) ;
        return 1;
    }//end if
    
    fscanf(fp, "%d", &i) ;
    i++;

    fclose(fp); 
    fp = fopen("autoidequip.txt", "w") ; 
    fprintf(fp, "%d", i) ;
    fclose(fp) ;
    return i ;
}//end of funtion

int autoidsale()//function automatically generates a number to be used as the order id and increments when a new record is added
{
    int i ;
    FILE * fp;
	if ((fp = fopen("autoidsale.txt", "r")) == NULL)
	{
        if ((fp = fopen("autoidsale.txt", "w")) == NULL)
        {
        	printf("Error. Cannot open id file.");
		}
        fprintf(fp, "%d", 1) ;
        fclose(fp) ;
        return 1;
    }//end if
    
    fscanf(fp, "%d", &i) ;
    i++;

    fclose(fp); 
    fp = fopen("autoidsale.txt", "w") ; 
    fprintf(fp, "%d", i) ;
    fclose(fp) ;
    return i ;
}//end of funtion

void CreatePlantFile()//function to create a file to store plant records
{
	FILE *fptrplant;//file pointer
	if	((fptrplant = fopen("SBADATAPLANT.bin", "wb")) == NULL)
	{
		printf("\n\t\tCannot open the file \n");
	}//end if
	
	else
	{
		printf("\n\n\t\tPlant Record File created.");
	}
	
	fclose(fptrplant);
}//end of funtion

void CreateEquipmentFile()//function to create a file to store equipment records
{	
	FILE *fptrequip;//file pointer
	if	((fptrequip = fopen("SBADATAEQUIP.bin", "wb")) == NULL)
	{
		printf("\n\t\tCannot open the file \n");
	}//end if
	
	else
	{
		printf("\n\n\t\tEquipment Record File created.");
	}
	
	fclose(fptrequip);
}//end of funtion

void CreateSaleFile()//function to create a file to store sale records
{
	FILE *fptrsale;//file pointer
	if	((fptrsale = fopen("SBADATASALE.bin", "wb")) == NULL)
	{
		printf("\n\t\tCannot open the file \n");
	}//end if
	
	else
	{
		printf("\n\n\t\tSale Record File created.");
	}
	
	fclose(fptrsale);
}//end of funtion

void ViewPlant()//View plant records
{
	struct PlantInfo plant = {0, "", 0.0, 0.0, 0, 0.0, 0, 0.0};
	
	FILE *fptrplant;//file pointer
	if	((fptrplant = fopen("SBADATAPLANT.bin", "rb+")) == NULL)
	{
		printf("\n\t\tCannot open file \n");
	}//end if
	
	else
	{
		while(fread(&plant, sizeof(struct PlantInfo), 1, fptrplant)==1)//while fread returns 1, i.e there are records still to be read in the file
		{
			if (plant.plantid != 0)
			{
				printf("\n\t\tId is: %d\n", plant.plantid);
				printf("\n\t\tPlant Name is: %s\n", plant.plantname);
				printf("\n\t\tCost Price/kg is: $%.2f\n", plant.plantcost);	
				printf("\n\t\tSale Price/kg is: $%.2f\n", plant.plantprice);
				printf("\n\t\tAmount in stock is: %d\n", plant.plantstock);
				printf("\n\t\tValue of stock is: $%.2f\n", plant.plantstockvalue);
				printf("--------------------------------------------------------------------");
			}//end if
		}//end while
	
	}//end else
    fclose(fptrplant);
}//end of funtion

void ViewEquipment()//View equipment records
{
	struct EquipInfo equipment = {0, "", 0.0, 0.0, 0, 0.0, 0, 0.0};
	
	FILE *fptrequip;//file pointer
	if	((fptrequip = fopen("SBADATAEQUIP.bin", "rb+")) == NULL)
	{
		printf("\n\t\tCannot open file \n");
	}//end if
	
	else
	{
		while(fread(&equipment, sizeof(struct EquipInfo), 1, fptrequip)==1)
		{
			if (equipment.equipid != 0)
			{
				printf("\n\t\tId is: %d\n", equipment.equipid);
				printf("\n\t\tEquipment Name is: %s\n", equipment.equipname);
				printf("\n\t\tCost Price is: $%.2f\n", equipment.equipcost);
				printf("\n\t\tSale Price is: $%.2f\n", equipment.equipprice);
				printf("\n\t\tAmount in stock is %d\n", equipment.equipstock);
				printf("\n\t\tValue of stock is $%.2f\n", equipment.equipstockvalue);
				printf("--------------------------------------------------------------------");
			}//end if
		}//end while
	}//end else
    fclose(fptrequip);
}//end of funtion

void ViewSale()//View sale records
{
	struct SaleInfo sale;
	int i, j;
	FILE *fptrsale;//file pointer
	if	((fptrsale = fopen("SBADATASALE.bin", "rb+")) == NULL)
	{
		printf("\n\t\tCannot open file \n");
	}//end if
	
	else
	{
		while(fread(&sale, sizeof(struct SaleInfo), 1, fptrsale)==1)
		{
			if (sale.saleid != 0)
			{
				printf("\n\t\tOrder Id is: %d\n", sale.saleid);
				printf("\n\t\tCustomer Name is: %s\n", sale.customername);
				if (sale.totequip > 0)
				{
					printf("\n\t\tEquipment Purchased:\n");
					for(i=0;i<sale.totequip;i++)
					{
						printf("\n\t\t\tItem Name: %s", sale.equipnames + i);
						printf("\n\t\t\tItem Id: %d", sale.equipids[i]);
						printf("\n\t\t\tItem price: $%.2f", sale.equipprice[i]);
						printf("\n\t\t\tQuantity of Item: %d",sale.equipquant[i]);
						printf("\n\t\t\tTotal for Item: $%.2f\n",sale.equiptotal[i]);
					}	
				}
				
				if(sale.totplant > 0)
				{
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
				
				printf("--------------------------------------------------------------------");
			}//end if
		}//end while
	}//end else
	fclose(fptrsale);
}//end of funtion

void AddPlant()//Add a new plant record
{
	struct PlantInfo plant = {0, "", 0.0, 0.0, 0, 0.0, 0, 0.0};
	
	FILE * fptrplant;//file pointer
	if	((fptrplant = fopen("SBADATAPLANT.bin", "ab+")) == NULL)
	{
		printf("\n\t\tCannot open file \n");
	}//end if
	
	else
	{
		plant.plantid = autoidplant();
	
		printf("\n\t\tPlant name is: ");
		scanf(" %[^\n]s", &plant.plantname);
		
		printf("\n\t\tPlant Cost Price/kg is: ");
		scanf("%f", &plant.plantcost);
		
		plant.plantprice = plant.plantcost*MARKUP;
		
		printf("\n\t\tAmount in stock is: ");
		scanf("%d", &plant.plantstock);
		
		plant.ogplantstock = plant.plantstock;
			
		plant.plantstockvalue = plant.plantprice*plant.plantstock; 
		
		plant.ogplantstockvalue = plant.plantstockvalue;
		
		fseek(fptrplant, (plant.plantid-1) * sizeof(struct PlantInfo), SEEK_SET);//moves file pointer to the beginning of the file
		fwrite(&plant, sizeof(struct PlantInfo), 1, fptrplant);//write record to file
	}//end else
	fclose(fptrplant);
}//end of funtion

void AddEquip()//Add a new equipment record
{
	struct EquipInfo equipment = {0, "", 0.0, 0.0, 0, 0.0, 0, 0.0};
	
	FILE *fptrequip;//file pointer
	if	((fptrequip = fopen("SBADATAEQUIP.bin", "ab+")) == NULL)
	{
		printf("\n\t\tCannot open file \n");
	}//end if
	
	else
	{
		equipment.equipid = autoidequip();
		
		printf("\n\t\tEquipment name is: ");
		scanf(" %[^\n]s", &equipment.equipname);
		
		printf("\n\t\tEquipment cost price is: ");
		scanf("%f", &equipment.equipcost);
	
		equipment.equipprice = equipment.equipcost*MARKUP;
		
		printf("\n\t\tAmount in stock is: ");
		scanf("%d", &equipment.equipstock);
		
		equipment.ogequipstock = equipment.equipstock;
		
		equipment.equipstockvalue = equipment.equipprice*equipment.equipstock;
		
		equipment.ogequipstockvalue = equipment.equipstockvalue;
		
		fseek(fptrequip, (equipment.equipid-1) * sizeof(struct EquipInfo),SEEK_SET);//moves file pointer to the beginning of the file
		fwrite(&equipment, sizeof(struct EquipInfo), 1, fptrequip);//write record to file
	}//end else
	fclose(fptrequip);
}//end of funtion

void AddSale()//Add a new sale record
{	
	struct SaleInfo sale;
	struct PlantInfo plant = {0, "", 0.0, 0.0, 0, 0.0, 0, 0.0};
	struct EquipInfo equipment = {0, "", 0.0, 0.0, 0, 0.0, 0, 0.0};
	int i = 0, j = 0, num = 0, num2 = 0, choice, idp, ide, plantnum, equipnum;
	float cost = 0;
	
	FILE *fptrsale;//file pointer
	if	((fptrsale = fopen("SBADATASALE.bin", "ab+")) == NULL)
	{
		printf("\n\t\tCannot open file \n");
	}//end if
	
	else
	{
		sale.saleid = autoidsale();
		
		printf("\n\t\tCustomer name is: ");
		scanf(" %[^\n]s", &sale.customername);
		
		printf("\n\t\tWhat items did the customer purchase?");
		printf("\n\t\t1. Plants.\n\t\t2. Equipment.\n\t\t3. Plants and Equipment.\n\t\t");
		scanf("%d", &choice);
		
		sale.totplant = 0;
		sale.totequip = 0;
		if (choice == 1)
		{
			printf("\n\t\t|==================================================|\n");
        	printf("\t\t|>>>>>>>>>>>>>>>>>> PLANT INFO <<<<<<<<<<<<<<<<<<<<|\n");
      	  	printf("\t\t|==================================================|\n\n");
			ViewPlant();
			FILE*fptrplant;
			if	((fptrplant = fopen("SBADATAPLANT.bin", "rb+")) == NULL)
			{
				printf("\n\t\tCannot open file \n");
			}//end if
			
			else
			{
				do
				{
					printf("\n\n\t\tEnter id of the plant purchased.\n\t\t");
					scanf("%d",&idp);
				
					fseek(fptrplant, (idp-1) * sizeof(struct PlantInfo), SEEK_SET);
					fread(&plant, sizeof(struct PlantInfo), 1, fptrplant);//reads a block of data
					
					while(plant.plantstock == 0)
					{
						printf("\n\n\t\tItem out of stock.");
						printf("\n\t\tEnter a different plant id.\n\t\t");
						scanf("%d",&idp);
						fseek(fptrplant, (idp-1) * sizeof(struct PlantInfo), SEEK_SET);
						fread(&plant, sizeof(struct PlantInfo), 1, fptrplant);//reads a block of data
					}
					
					printf("\n\t\tEnter the quantity of this item that the customer purchased.\n\t\t");
					scanf("%d", &plantnum);
					
					if (plantnum>plant.plantstock)
					{
						printf("\n\t\tNot enough in stock. Please enter a value less than %d", plant.plantstock);
						printf("\n\t\tEnter the quantity of this item that the customer purchased.\n\t\t");
						scanf("%d", &plantnum);
					}
					
					sale.plantquant[j] = plantnum;
					
					sale.plantids[j] = idp;
					
					strcpy(sale.plantnames[j], plant.plantname);
					
					sale.plantprice[j] = plant.plantprice;
					sale.planttotal[j] = sale.plantprice[j]*sale.plantquant[j];
					sale.cost += sale.planttotal[j];
					
					plant.plantstock -= sale.plantquant[j];
					plant.plantstockvalue -= sale.planttotal[j];
					fseek(fptrplant, (plant.plantid-1)*sizeof(struct PlantInfo),SEEK_SET);//moves file pointer to the beginning of the file
					fwrite(&plant, sizeof(struct PlantInfo), 1, fptrplant);//write record to the file
					
					j++;
					sale.totplant++;
					printf("\n\t\tEnter -1 to stop adding items to the order. Enter 0 to continue adding items.\n\t\t");
					scanf("%d", &num);
					if (num == -1)
					{
						break;
					}
				}
				while (num == 0);
			
			}//end else
				
			fseek(fptrsale, (sale.saleid-1) * sizeof(struct SaleInfo),SEEK_SET);//moves file pointer to the beginning of the file
			fwrite(&sale, sizeof(struct SaleInfo), 1, fptrsale);//write record to file
			fclose(fptrsale);
			fclose(fptrplant);	
		}//end if
		
		if (choice == 2)
		{
			printf("\n\t\t|======================================================|\n");
        	printf("\t\t|>>>>>>>>>>>>>>>>>> EQUIPMENT INFO <<<<<<<<<<<<<<<<<<<<|\n");
      	  	printf("\t\t|======================================================|\n\n");
			ViewEquipment();
			FILE*fptrequip;
			if	((fptrequip = fopen("SBADATAEQUIP.bin", "rb+")) == NULL)
			{
				printf("\n\t\tCannot open file \n");
			}//end if
			
			else
			{
				do
				{
					printf("\n\n\t\tEnter id of the equipment purchased.\n\t\t");
					scanf("%d",&ide);
				
					fseek(fptrequip, (ide-1) * sizeof(struct EquipInfo), SEEK_SET);
					fread(&equipment, sizeof(struct EquipInfo), 1, fptrequip);//reads a block of data
					
						while(equipment.equipstock == 0)
					{
						printf("\n\n\t\tItem out of stock.");
						printf("\n\t\tEnter a different id.\n\t\t");
						scanf("%d",&ide);
						fseek(fptrequip, (ide-1) * sizeof(struct EquipInfo), SEEK_SET);
						fread(&equipment, sizeof(struct EquipInfo), 1, fptrequip);//reads a block of data
					}
					
					printf("\n\t\tEnter the quantity of this item that the customer purchased.\n\t\t");
					scanf("%d", &equipnum);
					
					if (equipnum>equipment.equipstock)
					{
						printf("\n\t\tNot enough in stock. Please enter a value less than %d", equipment.equipstock);
						printf("\n\t\tEnter the quantity of this item that the customer purchased.\n\t\t");
						scanf("%d", &equipnum);
					}
					
					sale.equipquant[i] = equipnum;
					
					sale.equipids[i] = ide;
					
					strcpy(sale.equipnames[i], equipment.equipname);
					
					sale.equipprice[i] = equipment.equipprice;
					sale.equiptotal[i] = sale.equipprice[i]*sale.equipquant[i];
					sale.cost += sale.equiptotal[i];
					
					equipment.equipstock -= sale.equipquant[i];
					equipment.equipstockvalue -= sale.equiptotal[i];
					fseek(fptrequip, (equipment.equipid-1) * sizeof(struct EquipInfo),SEEK_SET);//moves file pointer to the beginning of the file
					fwrite(&equipment, sizeof(struct EquipInfo), 1, fptrequip);//write record to file
					
					i++;
					sale.totequip++;
					printf("\n\t\tEnter -1 to stop adding items to the order. Enter 0 to continue adding items.\n\t\t");
					scanf("%d", &num);
					if (num == -1)
					{
						break;
					}
				}
				while (num == 0);
			}//end else
			fseek(fptrsale, (sale.saleid-1) * sizeof(struct SaleInfo),SEEK_SET);//moves file pointer to the beginning of the file
			fwrite(&sale, sizeof(struct SaleInfo), 1, fptrsale);//write record to file
			fclose(fptrsale);
			fclose(fptrequip);
		}//end if
		
		if (choice == 3)
		{
			printf("\n\t\t|==================================================|\n");
        	printf("\t\t|>>>>>>>>>>>>>>>>>> PLANT INFO <<<<<<<<<<<<<<<<<<<<|\n");
      	  	printf("\t\t|==================================================|\n\n");
			ViewPlant();
			printf("\n\t\t|======================================================|\n");
        	printf("\t\t|>>>>>>>>>>>>>>>>>> EQUIPMENT INFO <<<<<<<<<<<<<<<<<<<<|\n");
      	  	printf("\t\t|======================================================|\n\n");
			ViewEquipment();
			FILE*fptrequip;
			FILE*fptrplant;
			if	((fptrequip = fopen("SBADATAEQUIP.bin", "rb+")) && (fptrplant = fopen("SBADATAPLANT.bin", "rb+")) == NULL)
			{
				printf("\n\t\tCannot open file \n");
			}//end if
			
			else
			{
				do
				{
					printf("\n\n\t\tEnter id of the equipment purchased.\n\t\t");
					scanf("%d",&ide);
				
					fseek(fptrequip, (ide-1) * sizeof(struct EquipInfo), SEEK_SET);
					fread(&equipment, sizeof(struct EquipInfo), 1, fptrequip);//reads a block of data
					
					while(equipment.equipstock == 0)
					{
						printf("\n\n\t\tItem out of stock.");
						printf("\n\t\tEnter a different id.\n\t\t");
						scanf("%d",&ide);
						fseek(fptrequip, (ide-1) * sizeof(struct EquipInfo), SEEK_SET);
						fread(&equipment, sizeof(struct EquipInfo), 1, fptrequip);//reads a block of data
					}
					
					printf("\n\t\tEnter the quantity of this item that the customer purchased.\n\t\t");
					scanf("%d", &equipnum);
					
					if (equipnum>equipment.equipstock)
					{
						printf("\n\t\tNot enough in stock. Please enter a value less than %d", equipment.equipstock);
						printf("\n\t\tEnter the quantity of this item that the customer purchased.\n\t\t");
						scanf("%d", &equipnum);
					}
					
					sale.equipquant[i] = equipnum;
					
					sale.equipids[i] = ide;
					
					strcpy(sale.equipnames[i], equipment.equipname);
					
					sale.equipprice[i] = equipment.equipprice;
					sale.equiptotal[i] = sale.equipprice[i]*sale.equipquant[i];
					sale.cost += sale.equiptotal[i];
					
					equipment.equipstock -= sale.equipquant[i];
					equipment.equipstockvalue -= sale.equiptotal[i];
					fseek(fptrequip, (equipment.equipid-1) * sizeof(struct EquipInfo),SEEK_SET);//moves file pointer to the beginning of the file
					fwrite(&equipment, sizeof(struct EquipInfo), 1, fptrequip);//write record to file
					
					i++;
					sale.totequip++;
					printf("\n\t\tEnter -1 to stop adding items to the order. Enter 0 to continue adding items.\n\t\t");
					scanf("%d", &num);
					if (num == -1)
					{
						break;
					}
				}
				while (num == 0);
					
				do
				{
					printf("\n\n\t\tEnter id of the plant purchased.\n\t\t");
					scanf("%d",&idp);
				
					fseek(fptrplant, (idp-1) * sizeof(struct PlantInfo), SEEK_SET);
					fread(&plant, sizeof(struct PlantInfo), 1, fptrplant);//reads a block of data
					
					while(plant.plantstock == 0)
					{
						printf("\n\n\t\tItem out of stock.");
						printf("\n\t\tEnter a different plant id.\n\t\t");
						scanf("%d",&idp);
						fseek(fptrplant, (idp-1) * sizeof(struct PlantInfo), SEEK_SET);
						fread(&plant, sizeof(struct PlantInfo), 1, fptrplant);//reads a block of data
					}
					
					printf("\n\t\tEnter the quantity of this item that the customer purchased.\n\t\t");
					scanf("%d", &plantnum);
					
					if (plantnum>plant.plantstock)
					{
						printf("\n\t\tNot enough in stock. Please enter a value less than %d", plant.plantstock);
						printf("\n\t\tEnter the quantity of this item that the customer purchased.\n\t\t");
						scanf("%d", &plantnum);
					}
					
					sale.plantquant[j] = plantnum;
					
					sale.plantids[j] = idp;
					
					strcpy(sale.plantnames[j], plant.plantname);
					
					sale.plantprice[j] = plant.plantprice;
					sale.planttotal[j] = sale.plantprice[j]*sale.plantquant[j];
					sale.cost += sale.planttotal[j];
					
					plant.plantstock -= sale.plantquant[j];
					plant.plantstockvalue -= sale.planttotal[j];
					fseek(fptrplant, (plant.plantid-1)*sizeof(struct PlantInfo),SEEK_SET);//moves file pointer to the beginning of the file
					fwrite(&plant, sizeof(struct PlantInfo), 1, fptrplant);//write record to the file
					
					j++;
					sale.totplant++;
					printf("\n\t\tEnter -1 to stop adding items to the order. Enter 0 to continue adding items.\n\t\t");
					scanf("%d", &num);
					if (num2 == -1)
					{
						break;
					}
				}
				while (num2 == 0);
			}//end else
			fseek(fptrsale, (sale.saleid-1) * sizeof(struct SaleInfo),SEEK_SET);//moves file pointer to the beginning of the file
			fwrite(&sale, sizeof(struct SaleInfo), 1, fptrsale);//write record to file
			fclose(fptrsale);
			fclose(fptrequip);
			fclose(fptrplant);
		}//end if
	}//end else
}//end of funtion

void SearchPlantName()
{
	struct PlantInfo plant = {0, "", 0.0, 0.0, 0, 0.0, 0, 0.0};
	char name[SIZE]; 
	int found=0; 
	
	FILE *fptrplant;//file pointer
	if	((fptrplant = fopen("SBADATAPLANT.bin", "rb+")) == NULL)
	{
		printf("\n\t\tCannot open file \n");
	}//end if
	
	else
	{
		printf("\n\t\tEnter name of the record that you want to find.\n");
		printf("\t\tYou chose: ");
		scanf(" %[^\n]s", &name);//allows spaces to be read
		
		while(fread(&plant, sizeof(struct PlantInfo), 1, fptrplant)==1)
		{   
			if(stricmp(name, plant.plantname)==0)
			{                              
				found=1;
				
				printf("\n\t\tId is: %d\n", plant.plantid);
				printf("\n\t\tPlant Name is: %s\n", plant.plantname);
				printf("\n\t\tCost Price/kg is: $%.2f\n", plant.plantcost);	
				printf("\n\t\tSale Price/kg is: $%.2f\n", plant.plantprice);
				printf("\n\t\tAmount in stock is: %d\n", plant.plantstock);
				printf("\n\t\tValue of stock is: $%.2f\n", plant.plantstockvalue);
				break;
			}//end if 
		}//end while
		
		if (found == 0)
		{
			printf("\n\t\tRecord not found.\n");
		}				
	}//end else
	fclose(fptrplant);
}

void SearchPlantId()
{
	struct PlantInfo plant = {0, "", 0.0, 0.0, 0, 0.0, 0, 0.0}; 
	int id, found=0; 
	
	FILE *fptrplant;//file pointer
	if	((fptrplant = fopen("SBADATAPLANT.bin", "rb+")) == NULL)
	{
		printf("\n\t\tCannot open file \n");
	}//end if
	
	else
	{
		printf("\n\t\tEnter id of the record to find.");
		printf("\n\n\t\tYou chose: ");
		scanf("%d",&id);
		
		fseek(fptrplant, (id-1) * sizeof(struct PlantInfo), SEEK_SET);
		fread(&plant, sizeof(struct PlantInfo), 1, fptrplant);//reads a block of data
		
		if(plant.plantid != 0)
		{
			found=1;
			
			printf("\n\t\tId is: %d\n", plant.plantid);
			printf("\n\t\tPlant Name is: %s\n", plant.plantname);
			printf("\n\t\tCost Price/kg is: $%.2f\n", plant.plantcost);	
			printf("\n\t\tSale Price/kg is: $%.2f\n", plant.plantprice);
			printf("\n\t\tAmount in stock is: %d\n", plant.plantstock);
			printf("\n\t\tValue of stock is: $%.2f\n", plant.plantstockvalue);
			
		}//end if
		
		if (found == 0)
		{
			printf("\n\t\tRecord not found.\n");
		}
	}//end else
	fclose(fptrplant);
}

void SearchPlant()//Search for a plant record
{
	int choice;
	
	printf("\n\t\t1. Search by name.");
	printf("\n\t\t2. Search by ID.\n\t\t");
	scanf("%d", &choice);
	
	switch (choice)
	{
		case 1:
		SearchPlantName();
		break;

		case 2:
		SearchPlantId();
		break;
			
		default:
		printf("\n\t\tInvalid option.");
		break;
	}//end switch
}//end of funtion

void SearchEquipmentName()
{
	struct EquipInfo equipment = {0, "", 0.0, 0.0, 0, 0.0, 0, 0.0};
	char name[SIZE];
	int found=0;
	
	FILE *fptrequip;//file pointer
	if	((fptrequip = fopen("SBADATAEQUIP.bin", "rb+")) == NULL)
	{
		printf("\n\t\tCannot open file \n");
	}//end if
	
	else
	{
		printf("\n\t\tEnter name of the record that you want to find.\n");
		printf("\t\tYou chose: ");
		scanf(" %[^\n]s", &name);//allows spaces to be read
	
		while(fread(&equipment, sizeof(struct EquipInfo), 1, fptrequip)==1)
		{   
			if(stricmp(name, equipment.equipname)==0)
			{                              
				found=1;
				
				printf("\n\t\tId is: %d\n", equipment.equipid);
				printf("\n\t\tEquipment Name is: %s\n", equipment.equipname);
				printf("\n\t\tCost Price is: $%.2f\n", equipment.equipcost);
				printf("\n\t\tSale Price is: $%.2f\n", equipment.equipprice);
				printf("\n\t\tAmount in stock is %d\n", equipment.equipstock);
				printf("\n\t\tValue of stock is $%.2f\n", equipment.equipstockvalue);
		
			}//end if
		}//end while
		if (found == 0)
		{
			printf("\n\t\tRecord not found.\n");
		}
	}//end else
	fclose(fptrequip);
}

void SearchEquipmentId()
{
	struct EquipInfo equipment = {0, "", 0.0, 0.0, 0, 0.0, 0, 0.0};
	int id, found=0;
	
	FILE *fptrequip;//file pointer
	if	((fptrequip = fopen("SBADATAEQUIP.bin", "rb+")) == NULL)
	{
		printf("\n\t\tCannot open file \n");
	}//end if
	
	else
	{
		printf("\n\t\tEnter id of the record to find.");
		printf("\n\n\t\tYou chose: ");
		scanf("%d",&id);
		
		fseek(fptrequip, (id-1) * sizeof(struct EquipInfo), SEEK_SET);
		fread(&equipment, sizeof(struct EquipInfo), 1, fptrequip);//reads a block of data
		
		if(equipment.equipid != 0)
		{
			found=1;
			
			printf("\n\t\tId is: %d\n", equipment.equipid);
			printf("\n\t\tEquipment Name is: %s\n", equipment.equipname);
			printf("\n\t\tCost Price is: $%.2f\n", equipment.equipcost);
			printf("\n\t\tSale Price is: $%.2f\n", equipment.equipprice);
			printf("\n\t\tAmount in stock is %d\n", equipment.equipstock);
			printf("\n\t\tValue of stock is $%.2f\n", equipment.equipstockvalue);
			
		}
		if (found == 0)
		{
			printf("\n\t\tRecord not found.\n");
		}
	}//end else
	fclose(fptrequip);
}

void SearchEquipment()//Search for an equipment record
{
	int choice;
	
	printf("\n\t\t1. Search by name.");
	printf("\n\t\t2. Search by ID.\n\t\t");
	scanf("%d", &choice);
	
	switch (choice)
	{
		case 1:
		SearchEquipmentName();
		break;
		
		case 2:
		SearchEquipmentId();
		break;
		
		default:
		printf("\n\t\tInvalid option.");
		break;	
	}
}//end of function

void SearchSaleName()
{
	int i, j;
	struct SaleInfo sale;
	char name[SIZE]; 
	int found=0; 
	
	FILE *fptrsale;//file pointer
	if	((fptrsale = fopen("SBADATASALE.bin", "rb+")) == NULL)
	{
		printf("\n\t\tCannot open file \n");
	}//end if
	
	else
	{
		printf("\n\t\tEnter customer name of the record that you want to find.\n");
		printf("\t\tYou chose: ");
		scanf(" %[^\n]s", &name);//allows spaces to be read
		
		while(fread(&sale, sizeof(struct SaleInfo), 1, fptrsale)==1)
		{   
			if(stricmp(name, sale.customername)==0)
			{                              
				found=1;
				
				printf("\n\t\tOrder Id is: %d\n", sale.saleid);
				printf("\n\t\tCustomer Name is: %s\n", sale.customername);
				if (sale.totequip > 0)
				{
					printf("\n\t\tEquipment Purchased:\n");
					for(i=0;i<sale.totequip;i++)
					{
						printf("\n\t\t\tItem Name: %s", sale.equipnames + i);
						printf("\n\t\t\tItem Id: %d", sale.equipids[i]);
						printf("\n\t\t\tItem price: $%.2f", sale.equipprice[i]);
						printf("\n\t\t\tQuantity of Item: %d",sale.equipquant[i]);
						printf("\n\t\t\tTotal for Item: $%.2f\n",sale.equiptotal[i]);
					}	
				}
				
				if(sale.totplant > 0)
				{
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
			}//end if    
		}//end while
		
		if(found == 0)
		{
			printf("\n\t\tRecord not found.\n");
		}//end if
	}// end else
	fclose(fptrsale);
}

void SearchSaleId()
{
	int id, i, j;
	struct SaleInfo sale;
	int found=0; 
	
	FILE *fptrsale;//file pointer
	if	((fptrsale = fopen("SBADATASALE.bin", "rb+")) == NULL)
	{
		printf("\n\t\tCannot open file \n");
	}//end if
	
	else
	{
		printf("\n\t\tEnter id of the record to find.");
		printf("\n\n\t\tYou chose: ");
		scanf("%d",&id);
		
		fseek(fptrsale, (id-1) * sizeof(struct SaleInfo), SEEK_SET);
		fread(&sale, sizeof(struct SaleInfo), 1, fptrsale);//reads a block of data
	
		if(sale.saleid != 0)
		{
			found=1;
			
			printf("\n\t\tOrder Id is: %d\n", sale.saleid);
			printf("\n\t\tCustomer Name is: %s\n", sale.customername);
			if (sale.totequip > 0)
			{
				printf("\n\t\tEquipment Purchased:\n");
				for(i=0;i<sale.totequip;i++)
				{
					printf("\n\t\t\tItem Name: %s", sale.equipnames + i);
					printf("\n\t\t\tItem Id: %d", sale.equipids[i]);
					printf("\n\t\t\tItem price: $%.2f", sale.equipprice[i]);
					printf("\n\t\t\tQuantity of Item: %d",sale.equipquant[i]);
					printf("\n\t\t\tTotal for Item: $%.2f\n",sale.equiptotal[i]);
				}	
			}
			
			if(sale.totplant > 0)
			{
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
		}//end if
		
		if(found == 0)
		{
			printf("\n\t\tRecord not found.\n");
		}//end if
	}//end else
	fclose(fptrsale);
}

void SearchSale()//Search for a sale record
{
	int choice;
	
	printf("\n\t\t1. Search by name.");
	printf("\n\t\t2. Search by ID.\n\t\t");
	scanf("%d", &choice);
	
	switch (choice)
	{
		case 1:
		SearchSaleName();
		break;
		
		case 2:
		SearchSaleId();
		break;
		
		default:
		printf("\n\t\tInvalid option.");
		break;
	}
}//end of funtion

void UpdatePlantName()
{
	int option;
	char name[SIZE];
	struct PlantInfo plant = {0, "", 0.0, 0.0, 0, 0.0, 0, 0.0};
	int found=0;
	
	FILE *fptrplant;//file pointer
	if	((fptrplant = fopen("SBADATAPLANT.bin", "rb+")) == NULL)
	{
		printf("\n\t\tCannot open file \n");
	}//end if
		
	else
	{
		printf("\n\t\tEnter plant name of the record that you want to update.\n");
		printf("\t\tYou chose: ");
		scanf(" %[^\n]s", &name);//allows spaces to be read
		
		while(fread(&plant, sizeof(struct PlantInfo), 1, fptrplant)==1)
		{   
			if(stricmp(name, plant.plantname)==0)
			{                              
				found=1;
				
				printf("\n\t\tId is: %d\n", plant.plantid);
				printf("\n\t\tPlant Name is: %s\n", plant.plantname);
				printf("\n\t\tCost Price/kg is: $%.2f\n", plant.plantcost);	
				printf("\n\t\tSale Price/kg is: $%.2f\n", plant.plantprice);
				printf("\n\t\tAmount in stock is: %d\n", plant.plantstock);
				printf("\n\t\tValue of stock is: $%.2f\n", plant.plantstockvalue);
				break;
			}//end if 
		}//end while
		
		if(found == 0)
		{
			printf("\n\t\tRecord not found.\n");
		}//end if
			
		if(found == 1)
		{
			printf("\n\t\tAre you sure you want to update this record.");
			printf("\n\t\t1 - yes\n\t\t2 - no\n");
			printf("\n\t\tYou chose: ");
			scanf("%d", &option);
			
			switch (option)
			{	
				case 1:
				printf("\n\t\tNew Plant name is: ");
				scanf(" %[^\n]s", &plant.plantname);
				
				printf("\n\t\tNew Plant Cost Price/kg is: ");
				scanf("%f", &plant.plantcost);
				
				plant.plantprice = plant.plantcost*MARKUP;
				
				printf("\n\t\tNew Amount in stock is: ");
				scanf("%d", &plant.plantstock);
				
				plant.ogplantstock = plant.plantstock;
					
				plant.plantstockvalue = plant.plantprice*plant.plantstock; 
		
				plant.ogplantstockvalue = plant.plantstockvalue;
					
				fseek(fptrplant, (plant.plantid-1)*sizeof(struct PlantInfo),SEEK_SET);//moves file pointer to the beginning of the file
				fwrite(&plant, sizeof(struct PlantInfo), 1, fptrplant);//write record to the file
				break;	
			
				case 2:
				break;
				
				default:
				printf("\n\t\tInvalid option.");
				break;
			}//end switch
		}	
	}//end else
	fclose(fptrplant);
}

void UpdatePlantId()
{
	int id, option;
	struct PlantInfo plant = {0, "", 0.0, 0.0, 0, 0.0, 0, 0.0};
	int found=0;
	
	FILE *fptrplant;//file pointer
	if	((fptrplant = fopen("SBADATAPLANT.bin", "rb+")) == NULL)
	{
		printf("\n\t\tCannot open file \n");
	}//end if
		
	else
	{
		printf("\n\t\tEnter id of the record to update.");
		printf("\n\n\t\tYou chose: ");
		scanf("%d",&id);
		
		fseek(fptrplant, (id-1) * sizeof(struct PlantInfo), SEEK_SET);
		fread(&plant, sizeof(struct PlantInfo), 1, fptrplant);//reads a block of data
		
		if(plant.plantid != 0)
		{
			found=1;
			
			printf("\n\t\tId is: %d\n", plant.plantid);
			printf("\n\t\tPlant Name is: %s\n", plant.plantname);
			printf("\n\t\tCost Price/kg is: $%.2f\n", plant.plantcost);	
			printf("\n\t\tSale Price/kg is: $%.2f\n", plant.plantprice);
			printf("\n\t\tAmount in stock is: %d\n", plant.plantstock);
			printf("\n\t\tValue of stock is: $%.2f\n", plant.plantstockvalue);	
		}//end if
		
		if(found == 1)
		{
			printf("\n\t\tAre you sure you want to update this record.");
			printf("\n\t\t1 - yes\n\t\t2 - no\n");
			printf("\n\t\tYou chose: ");
			scanf("%d", &option);
			
			switch (option)
			{	
				case 1:
				printf("\n\t\tNew Plant name is: ");
				scanf(" %[^\n]s", &plant.plantname);
				
				printf("\n\t\tNew Plant Cost Price/kg is: ");
				scanf("%f", &plant.plantcost);
				
				plant.plantprice = plant.plantcost*MARKUP;
				
				printf("\n\t\tNew Amount in stock is: ");
				scanf("%d", &plant.plantstock);
					
				plant.ogplantstock = plant.plantstock;
					
				plant.plantstockvalue = plant.plantprice*plant.plantstock; 
		
				plant.ogplantstockvalue = plant.plantstockvalue;
		
				fseek(fptrplant, (plant.plantid-1)*sizeof(struct PlantInfo),SEEK_SET);//moves file pointer to the beginning of the file
				fwrite(&plant, sizeof(struct PlantInfo), 1, fptrplant);//write record to the file
				break;	
			
				case 2:
				break;
				
				default:
				printf("\n\t\tInvalid option.");
				break;
			}//end switch
		}
		
		if(found == 0)
		{
			printf("\n\t\tRecord not found.\n");
		}//end if
	}//end else
	fclose(fptrplant);
}

void UpdatePlant()//Update a plant record
{
	int choice;
	printf("\n\t\t1. Search by name to update.");
	printf("\n\t\t2. Search by ID to update.\n\t\t");
	scanf("%d", &choice);
	
	switch (choice)
	{
		case 1:
		UpdatePlantName();
		break;
	
		case 2:
		UpdatePlantId();
		break;
		
		default:
		printf("\n\t\tInvalid option.");
		break;
	}
}//end of funtion

void UpdateEquipmentName()//Update a equipment record
{
	int option, found = 0;
	char name[SIZE];
	struct EquipInfo equipment = {0, "", 0.0, 0.0, 0, 0.0, 0, 0.0};
	
	FILE *fptrequip;//file pointer
	if	((fptrequip = fopen("SBADATAEQUIP.bin", "rb+")) == NULL)
	{
		printf("\n\t\tCannot open file \n");
	}//end if
	
	else
	{
		printf("\n\t\tEnter name of the record that you want to update.\n");
		printf("\t\tYou chose: ");
		scanf(" %[^\n]s", &name);//allows spaces to be read
		
		while(fread(&equipment, sizeof(struct EquipInfo), 1, fptrequip)==1)
		{   
			if(stricmp(name, equipment.equipname)==0)
			{                              
				found=1;
				
				printf("\n\t\tId is: %d\n", equipment.equipid);
				printf("\n\t\tName is: %s\n", equipment.equipname);
				printf("\n\t\tCost Price is: $%.2f\n", equipment.equipcost);	
				printf("\n\t\tSale Price is: $%.2f\n", equipment.equipprice);
				printf("\n\t\tAmount in stock is: %d\n", equipment.equipstock);
				printf("\n\t\tValue of stock is: $%.2f\n", equipment.equipstockvalue);
				break;
			}//end if 
		}//end while
			
		if(found == 1)
		{
			printf("\n\t\tAre you sure you want to update this record.");
			printf("\n\t\t1 - yes\n\t\t2 - no\n");
			printf("\n\t\tYou chose: ");
			scanf("%d", &option);
			
			switch (option)
			{	
				case 1:
				printf("\n\t\tNew name is: ");
				scanf(" %[^\n]s", &equipment.equipname);
				
				printf("\n\t\tNew Cost Price is: ");
				scanf("%f", &equipment.equipcost);
				
				equipment.equipprice = equipment.equipcost*MARKUP;
				
				printf("\n\t\tNew Amount in stock is: ");
				scanf("%d", &equipment.equipstock);
				
				equipment.ogequipstock = equipment.equipstock;
					
				equipment.equipstockvalue = equipment.equipprice*equipment.equipstock; 
		
				equipment.ogequipstockvalue = equipment.equipstockvalue;
		
				fseek(fptrequip, (equipment.equipid-1)*sizeof(struct EquipInfo),SEEK_SET);//moves file pointer to the beginning of the file
				fwrite(&equipment, sizeof(struct EquipInfo), 1, fptrequip);//write record to the file
				break;	
			
				case 2:
				break;
				
				default:
				printf("\n\t\tInvalid option.");
				break;
			}//end switch
		}
			
		if(found == 0)
		{
			printf("\n\t\tRecord not found.\n");
		}//end if
	}//end else
	fclose(fptrequip);
}

void UpdateEquipmentId()//Update a equipment record
{
	int id, option, found = 0;
	struct EquipInfo equipment = {0, "", 0.0, 0.0, 0, 0.0, 0, 0.0};
	
	FILE *fptrequip;//file pointer
	if	((fptrequip = fopen("SBADATAEQUIP.bin", "rb+")) == NULL)
	{
		printf("\n\t\tCannot open file \n");
	}//end if
	
	else
	{
		printf("\n\t\tEnter id of the record to update.");
		printf("\n\n\t\tYou chose: ");
		scanf("%d",&id);
		
		fseek(fptrequip, (id-1) * sizeof(struct EquipInfo), SEEK_SET);
		fread(&equipment, sizeof(struct EquipInfo), 1, fptrequip);//reads a block of data
		
		if(equipment.equipid != 0)
		{
			found=1;
			
			printf("\n\t\tId is: %d\n", equipment.equipid);
			printf("\n\t\tName is: %s\n", equipment.equipname);
			printf("\n\t\tCost Price is: $%.2f\n", equipment.equipcost);	
			printf("\n\t\tSale Price is: $%.2f\n", equipment.equipprice);
			printf("\n\t\tAmount in stock is: %d\n", equipment.equipstock);
			printf("\n\t\tValue of stock is: $%.2f\n", equipment.equipstockvalue);
		}//end if
		
		if(found == 1)
		{
			printf("\n\t\tAre you sure you want to update this record.");
			printf("\n\t\t1 - yes\n\t\t2 - no\n");
			printf("\n\t\tYou chose: ");
			scanf("%d", &option);
			
			switch (option)
			{	
				case 1:
				printf("\n\t\tNew name is: ");
				scanf(" %[^\n]s", &equipment.equipname);
				
				printf("\n\t\tNew Cost Price is: ");
				scanf("%f", &equipment.equipcost);
				
				equipment.equipprice = equipment.equipcost*MARKUP;
				
				printf("\n\t\tNew Amount in stock is: ");
				scanf("%d", &equipment.equipstock);
					
				equipment.ogequipstock = equipment.equipstock;
					
				equipment.equipstockvalue = equipment.equipprice*equipment.equipstock; 
		
				equipment.ogequipstockvalue = equipment.equipstockvalue;
		
				fseek(fptrequip, (equipment.equipid-1)*sizeof(struct EquipInfo),SEEK_SET);//moves file pointer to the beginning of the file
				fwrite(&equipment, sizeof(struct EquipInfo), 1, fptrequip);//write record to the file
				break;	
			
				case 2:
				break;
				
				default:
				printf("\n\t\tInvalid option.");
				break;
			}//end switch
		}
			
		if(found == 0)
		{
			printf("\n\t\tRecord not found.\n");
		}//end if
	}
	fclose(fptrequip);
}

void UpdateEquipment()//Update a equipment record
{
	int choice;	
	
	printf("\n\t\t1. Search by name to update.");
	printf("\n\t\t2. Search by ID to update.\n\t\t");
	scanf("%d", &choice);
	
	switch (choice)
	{
		case 1:
		UpdateEquipmentName();
		break;
	
		case 2:
		UpdateEquipmentId();
		break;
		
		default:
		printf("\n\t\tInvalid option.");
		break;
	}
}//end of funtion

void UpdateSaleName()
{
	struct SaleInfo sale;
	struct PlantInfo plant = {0, "", 0.0, 0.0, 0, 0.0, 0, 0.0};
	struct EquipInfo equipment = {0, "", 0.0, 0.0, 0, 0.0, 0, 0.0};
	int i = 0, j = 0, num = 0, num2 = 0, found = 0, choice, option, idp, ide, plantnum, equipnum;
	char name[SIZE];
	 
	FILE*fptrplant;
	fptrplant = fopen("SBADATAPLANT.bin", "rb+");
	if (fptrplant == NULL)
		printf("\n\t\tCannot open plant file \n");

	FILE*fptrequip;
	fptrequip = fopen("SBADATAEQUIP.bin", "rb+");	
	if (fptrequip == NULL)
		printf("\n\t\tCannot open equipment file \n");
		
	FILE *fptrsale;//file pointer
	if	((fptrsale = fopen("SBADATASALE.bin", "rb+")) == NULL)
	{
		printf("\n\t\tCannot open file \n");
	}//end if
	
	else
	{
		sale.totplant = 0;
		sale.totequip = 0;
		printf("\n\t\tEnter customer name of the record that you want to find.\n");
		printf("\t\tYou chose: ");
		scanf(" %[^\n]s", &name);//allows spaces to be read
		
		while(fread(&sale, sizeof(struct SaleInfo), 1, fptrsale)==1)
		{   
			if(stricmp(name, sale.customername)==0)
			{                              
				found=1;
				printf("\n\t\tOrder Id is: %d\n", sale.saleid);
				printf("\n\t\tCustomer Name is: %s\n", sale.customername);
				if (sale.totequip > 0)
				{
					printf("\n\t\tEquipment Purchased:\n");
					for(i=0;i<sale.totequip;i++)
					{
						printf("\n\t\t\tItem Name: %s", sale.equipnames + i);
						printf("\n\t\t\tItem Id: %d", sale.equipids[i]);
						printf("\n\t\t\tItem price: $%.2f", sale.equipprice[i]);
						printf("\n\t\t\tQuantity of Item: %d",sale.equipquant[i]);
						printf("\n\t\t\tTotal for Item: $%.2f\n",sale.equiptotal[i]);
					}	
				}
				
				if(sale.totplant > 0)
				{
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
				break;	
			}//end if    
		}//end while
		
		if(found == 0)
		{
			printf("\n\t\tRecord not found.\n");
		}//end if
		
		printf("\n\t\tAre you sure you want to update this record.");
		printf("\n\t\t1 - yes\n\t\t2 - no\n");
		printf("\n\t\tYou chose: ");
		scanf("%d", &option);
		
		switch (option)
		{
			case 1:
			printf("\n\t\tNew Customer name is: ");
			scanf(" %[^\n]s", &sale.customername);	
			printf("\n\t\tWhat items did the customer purchase?");
			printf("\n\t\t1. Plants.\n\t\t2. Equipment.\n\t\t3. Plants and Equipment.\n\t\t");
			scanf("%d", &choice);
			
			switch (choice)
			{
				case 1:
				j=0;
				sale.totplant=0;
				printf("\n\t\t|==================================================|\n");
	        	printf("\t\t|>>>>>>>>>>>>>>>>>> PLANT INFO <<<<<<<<<<<<<<<<<<<<|\n");
	      	  	printf("\t\t|==================================================|\n\n");
				ViewPlant();
	
				do
				{	
					printf("\n\n\t\tEnter the new id of the plant purchased.\n\t\t");
					scanf("%d",&idp);
				
					fseek(fptrplant, (idp-1) * sizeof(struct PlantInfo), SEEK_SET);
					fread(&plant, sizeof(struct PlantInfo), 1, fptrplant);//reads a block of data
					
					while(plant.plantstock == 0)
					{
						printf("\n\n\t\tItem out of stock.");
						printf("\n\t\tEnter a different plant id.\n\t\t");
						scanf("%d",&idp);
						fseek(fptrplant, (idp-1) * sizeof(struct PlantInfo), SEEK_SET);
						fread(&plant, sizeof(struct PlantInfo), 1, fptrplant);//reads a block of data
					}
					
					printf("\n\t\tEnter the new quantity of this item that the customer purchased.\n\t\t");
					scanf("%d", &plantnum);
					
					if (plantnum>plant.plantstock)
					{
						printf("\n\t\tNot enough in stock. Please enter a value less than %d", plant.plantstock);
						printf("\n\t\tEnter the quantity of this item that the customer purchased.\n\t\t");
						scanf("%d", &plantnum);
					}
				
					sale.plantquant[j] = plantnum;
					
					sale.plantids[j] = idp;
					
					strcpy(sale.plantnames[j], plant.plantname);
					
					sale.plantprice[j] = plant.plantprice;
					sale.planttotal[j] = sale.plantprice[j]*sale.plantquant[j];
					sale.cost += sale.planttotal[j];
					
					plant.plantstock = plant.ogplantstock;
					plant.plantstockvalue = plant.ogplantstockvalue;
					
					plant.plantstock -= sale.plantquant[j];
					plant.plantstockvalue -= sale.planttotal[j];
					fseek(fptrplant, (plant.plantid-1)*sizeof(struct PlantInfo),SEEK_SET);//moves file pointer to the beginning of the file
					fwrite(&plant, sizeof(struct PlantInfo), 1, fptrplant);//write record to the file
					
					j++;
					sale.totplant++;
					printf("\n\t\tEnter -1 to stop adding items to the order. Enter 0 to continue adding items.\n\t\t");
					scanf("%d", &num);
					if (num == -1)
					{
						break;
					}
				}
				while (num == 0);
				break;
				
				case 2:
				i=0;
				sale.totequip=0;
				printf("\n\t\t|======================================================|\n");
		    	printf("\t\t|>>>>>>>>>>>>>>>>>> EQUIPMENT INFO <<<<<<<<<<<<<<<<<<<<|\n");
		  	  	printf("\t\t|======================================================|\n\n");
				ViewEquipment();
				do
				{
					printf("\n\n\t\tEnter new id of the equipment purchased.\n\t\t");
					scanf("%d",&ide);
				
					fseek(fptrequip, (ide-1) * sizeof(struct EquipInfo), SEEK_SET);
					fread(&equipment, sizeof(struct EquipInfo), 1, fptrequip);//reads a block of data
					
					while(equipment.equipstock == 0)
					{
						printf("\n\n\t\tItem out of stock.");
						printf("\n\t\tEnter a different id.\n\t\t");
						scanf("%d",&ide);
						fseek(fptrequip, (ide-1) * sizeof(struct EquipInfo), SEEK_SET);
						fread(&equipment, sizeof(struct EquipInfo), 1, fptrequip);//reads a block of data
					}
					
					printf("\n\t\tEnter the quantity of this item that the customer purchased.\n\t\t");
					scanf("%d", &equipnum);
					
					if (equipnum>equipment.equipstock)
					{
						printf("\n\t\tNot enough in stock. Please enter a value less than %d", equipment.equipstock);
						printf("\n\t\tEnter the quantity of this item that the customer purchased.\n\t\t");
						scanf("%d", &equipnum);
					}
					
					sale.equipquant[i] = equipnum;
					
					sale.equipids[i] = ide;
					
					strcpy(sale.equipnames[i], equipment.equipname);
					
					sale.equipprice[i] = equipment.equipprice;
					sale.equiptotal[i] = sale.equipprice[i]*sale.equipquant[i];
					sale.cost += sale.equiptotal[i];
					
					equipment.equipstock=equipment.ogequipstock;
					equipment.equipstockvalue=equipment.ogequipstockvalue;
					
					equipment.equipstock -= sale.equipquant[i];
					equipment.equipstockvalue -= sale.equiptotal[i];
					fseek(fptrequip, (equipment.equipid-1) * sizeof(struct EquipInfo),SEEK_SET);//moves file pointer to the beginning of the file
					fwrite(&equipment, sizeof(struct EquipInfo), 1, fptrequip);//write record to file
					
					i++;
					sale.totequip++;
					printf("\n\t\tEnter -1 to stop adding items to the order. Enter 0 to continue adding items.\n\t\t");
					scanf("%d", &num);
					if (num == -1)
					{
						break;
					}
				}
				while (num == 0);
				break;
				
				case 3:
				i=0;
				j=0;
				sale.totplant=0;
				sale.totequip=0;
				printf("\n\t\t|==================================================|\n");
	        	printf("\t\t|>>>>>>>>>>>>>>>>>> PLANT INFO <<<<<<<<<<<<<<<<<<<<|\n");
	      	  	printf("\t\t|==================================================|\n\n");
				ViewPlant();
				printf("\n\t\t|======================================================|\n");
	        	printf("\t\t|>>>>>>>>>>>>>>>>>> EQUIPMENT INFO <<<<<<<<<<<<<<<<<<<<|\n");
	      	  	printf("\t\t|======================================================|\n\n");
				ViewEquipment();
				do
				{
					printf("\n\n\t\tEnter id of the equipment purchased.\n\t\t");
					scanf("%d",&ide);
				
					fseek(fptrequip, (ide-1) * sizeof(struct EquipInfo), SEEK_SET);
					fread(&equipment, sizeof(struct EquipInfo), 1, fptrequip);//reads a block of data
					
					printf("\n\t\tEnter the quantity of this item that the customer purchased.\n\t\t");
					scanf("%d", &equipnum);
					
					sale.equipquant[i] = equipnum;
					
					sale.equipids[i] = ide;
					
					strcpy(sale.equipnames[i], equipment.equipname);
					
					sale.equipprice[i] = equipment.equipprice;
					sale.cost += sale.equipprice[i]*sale.equipquant[i];
					
					equipment.equipstock=equipment.ogequipstock;
					equipment.equipstockvalue=equipment.ogequipstockvalue;
					
					equipment.equipstock -= sale.equipquant[i];
					equipment.equipstockvalue -= sale.equipprice[i]*sale.equipquant[i];
					fseek(fptrequip, (equipment.equipid-1) * sizeof(struct EquipInfo),SEEK_SET);//moves file pointer to the beginning of the file
					fwrite(&equipment, sizeof(struct EquipInfo), 1, fptrequip);//write record to file
					
					i++;
					sale.totequip++;
					printf("\n\t\tEnter -1 to stop adding equipment to the order. Enter 0 to continue adding equipment.\n\t\t");
					scanf("%d", &num);
					if (num == -1)
					{
						break;
					}
				}
				while (num == 0);
					
				do
				{
					printf("\n\n\t\tEnter id of the plant purchased.\n\t\t");
					scanf("%d",&idp);
				
					fseek(fptrplant, (idp-1) * sizeof(struct PlantInfo), SEEK_SET);
					fread(&plant, sizeof(struct PlantInfo), 1, fptrplant);//reads a block of data
					
					printf("\n\t\tEnter the quantity of this item that the customer purchased.\n\t\t");
					scanf("%d", &plantnum);
					
					if (plantnum>plant.plantstock)
					{
						printf("\n\t\tNot enough in stock. Please enter a value less than %d", plant.plantstock);
						printf("\n\t\tEnter the quantity of this item that the customer purchased.\n\t\t");
						scanf("%d", &plantnum);
					}
					
					sale.plantquant[j] = plantnum;
					
					sale.plantids[j] = idp;
					
					strcpy(sale.plantnames[j], plant.plantname);
					
					sale.plantprice[j] = plant.plantprice;
					sale.cost += sale.plantprice[j]*sale.plantquant[j];
					
					plant.plantstock = plant.ogplantstock;
					plant.plantstockvalue = plant.ogplantstockvalue;
					
					plant.plantstock -= sale.plantquant[j];
					plant.plantstockvalue -= sale.plantprice[j]*sale.plantquant[j];
					fseek(fptrplant, (plant.plantid-1)*sizeof(struct PlantInfo),SEEK_SET);//moves file pointer to the beginning of the file
					fwrite(&plant, sizeof(struct PlantInfo), 1, fptrplant);//write record to the file
					
					j++;
					sale.totplant++;
					printf("\n\t\tEnter -1 to stop adding plants to the order. Enter 0 to continue adding plants.\n\t\t");
					scanf("%d", &num2);
					if (num2 == -1)
					{
						break;
					}
				}
				while (num2 == 0);
				break;
			}
			break;
			
			case 2:
			break;
			
			default:
			printf("\n\t\tInvalid option.");
			break;
		}
		fseek(fptrsale, (sale.saleid-1) * sizeof(struct SaleInfo),SEEK_SET);//moves file pointer to the beginning of the file
		fwrite(&sale, sizeof(struct SaleInfo), 1, fptrsale);//write record to file	
	}
	fclose(fptrsale);
	fclose(fptrplant);
	fclose(fptrequip);
}


void UpdateSaleId()
{
	struct SaleInfo sale;
	struct PlantInfo plant = {0, "", 0.0, 0.0, 0, 0.0, 0, 0.0};
	struct EquipInfo equipment = {0, "", 0.0, 0.0, 0, 0.0, 0, 0.0};
	int i = 0, j = 0, num = 0, num2 = 0, found = 0, choice, option, idp, ide, plantnum, equipnum, id;
	 
	FILE*fptrplant;
	fptrplant = fopen("SBADATAPLANT.bin", "rb+");
	if (fptrplant == NULL)
		printf("\n\t\tCannot open plant file \n");

	FILE*fptrequip;
	fptrequip = fopen("SBADATAEQUIP.bin", "rb+");	
	if (fptrequip == NULL)
		printf("\n\t\tCannot open equipment file \n");
	
	FILE *fptrsale;//file pointer
	if	((fptrsale = fopen("SBADATASALE.bin", "rb+")) == NULL)
	{
		printf("\n\t\tCannot open file \n");
	}//end if
	
	else
	{
		printf("\n\t\tEnter id of the record to update.");
		printf("\n\n\t\tYou chose: ");
		scanf("%d",&id);
		
		fseek(fptrsale, (id-1) * sizeof(struct SaleInfo), SEEK_SET);
		fread(&sale, sizeof(struct SaleInfo), 1, fptrsale);//reads a block of data
		
		if (sale.saleid != 0)
		{
			found=1;
			printf("\n\t\tOrder Id is: %d\n", sale.saleid);
			printf("\n\t\tCustomer Name is: %s\n", sale.customername);
			if (sale.totequip > 0)
			{
				printf("\n\t\tEquipment Purchased:\n");
				for(i=0;i<sale.totequip;i++)
				{
					printf("\n\t\t\tItem Name: %s", sale.equipnames + i);
					printf("\n\t\t\tItem Id: %d", sale.equipids[i]);
					printf("\n\t\t\tItem price: $%.2f", sale.equipprice[i]);
					printf("\n\t\t\tQuantity of Item: %d",sale.equipquant[i]);
					printf("\n\t\t\tTotal for Item: $%.2f\n",sale.equiptotal[i]);
				}	
			}
			
			if(sale.totplant > 0)
			{
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
		}//end if
		
		if(found == 0)
		{
			printf("\n\t\tRecord not found.\n");
		}//end if
		
		printf("\n\t\tAre you sure you want to update this record.");
		printf("\n\t\t1 - yes\n\t\t2 - no\n");
		printf("\n\t\tYou chose: ");
		scanf("%d", &option);
		
		switch (option)
		{
			case 1:
			printf("\n\t\tNew Customer name is: ");
			scanf(" %[^\n]s", &sale.customername);	
			printf("\n\t\tWhat items did the customer purchase?");
			printf("\n\t\t1. Plants.\n\t\t2. Equipment.\n\t\t3. Plants and Equipment.\n\t\t");
			scanf("%d", &choice);
			
			switch (choice)
			{
				case 1:
				j=0;
				sale.totplant=0;
				printf("\n\t\t|==================================================|\n");
	        	printf("\t\t|>>>>>>>>>>>>>>>>>> PLANT INFO <<<<<<<<<<<<<<<<<<<<|\n");
	      	  	printf("\t\t|==================================================|\n\n");
				ViewPlant();
	
				do
				{	
					printf("\n\n\t\tEnter the new id of the plant purchased.\n\t\t");
					scanf("%d",&idp);
				
					fseek(fptrplant, (idp-1) * sizeof(struct PlantInfo), SEEK_SET);
					fread(&plant, sizeof(struct PlantInfo), 1, fptrplant);//reads a block of data
					
					while(plant.plantstock == 0)
					{
						printf("\n\n\t\tItem out of stock.");
						printf("\n\t\tEnter a different plant id.\n\t\t");
						scanf("%d",&idp);
						fseek(fptrplant, (idp-1) * sizeof(struct PlantInfo), SEEK_SET);
						fread(&plant, sizeof(struct PlantInfo), 1, fptrplant);//reads a block of data
					}
					
					printf("\n\t\tEnter the new quantity of this item that the customer purchased.\n\t\t");
					scanf("%d", &plantnum);
					
					if (plantnum>plant.plantstock)
					{
						printf("\n\t\tNot enough in stock. Please enter a value less than %d", plant.plantstock);
						printf("\n\t\tEnter the quantity of this item that the customer purchased.\n\t\t");
						scanf("%d", &plantnum);
					}
					
					sale.plantquant[j] = plantnum;
					
					sale.plantids[j] = idp;
					
					strcpy(sale.plantnames[j], plant.plantname);
					
					sale.plantprice[j] = plant.plantprice;
					sale.planttotal[j] = sale.plantprice[j]*sale.plantquant[j];
					sale.cost += sale.planttotal[j];
					
					plant.plantstock = plant.ogplantstock;
					plant.plantstockvalue = plant.ogplantstockvalue;
					
					plant.plantstock -= sale.plantquant[j];
					plant.plantstockvalue -= sale.planttotal[j];
					fseek(fptrplant, (plant.plantid-1)*sizeof(struct PlantInfo),SEEK_SET);//moves file pointer to the beginning of the file
					fwrite(&plant, sizeof(struct PlantInfo), 1, fptrplant);//write record to the file
					
					j++;
					sale.totplant++;
					printf("\n\t\tEnter -1 to stop adding items to the order. Enter 0 to continue adding items.\n\t\t");
					scanf("%d", &num);
					if (num == -1)
					{
						break;
					}
				}
				while (num == 0);
				break;
				
				case 2:
				i=0;
				sale.totequip=0;
				printf("\n\t\t|======================================================|\n");
		    	printf("\t\t|>>>>>>>>>>>>>>>>>> EQUIPMENT INFO <<<<<<<<<<<<<<<<<<<<|\n");
		  	  	printf("\t\t|======================================================|\n\n");
				ViewEquipment();
				do
				{
					printf("\n\n\t\tEnter new id of the equipment purchased.\n\t\t");
					scanf("%d",&ide);
				
					fseek(fptrequip, (ide-1) * sizeof(struct EquipInfo), SEEK_SET);
					fread(&equipment, sizeof(struct EquipInfo), 1, fptrequip);//reads a block of data
					
					while(equipment.equipstock == 0)
					{
						printf("\n\n\t\tItem out of stock.");
						printf("\n\t\tEnter a different id.\n\t\t");
						scanf("%d",&ide);
						fseek(fptrequip, (ide-1) * sizeof(struct EquipInfo), SEEK_SET);
						fread(&equipment, sizeof(struct EquipInfo), 1, fptrequip);//reads a block of data
					}
					
					printf("\n\t\tEnter the quantity of this item that the customer purchased.\n\t\t");
					scanf("%d", &equipnum);
					
					if (equipnum>equipment.equipstock)
					{
						printf("\n\t\tNot enough in stock. Please enter a value less than %d", equipment.equipstock);
						printf("\n\t\tEnter the quantity of this item that the customer purchased.\n\t\t");
						scanf("%d", &equipnum);
					}
					
					sale.equipquant[i] = equipnum;
					
					sale.equipids[i] = ide;
					
					strcpy(sale.equipnames[i], equipment.equipname);
					
					sale.equipprice[i] = equipment.equipprice;
					sale.equiptotal[i] = sale.equipprice[i]*sale.equipquant[i];
					sale.cost += sale.equiptotal[i];
					
					equipment.equipstock=equipment.ogequipstock;
					equipment.equipstockvalue=equipment.ogequipstockvalue;
					
					equipment.equipstock -= sale.equipquant[i];
					equipment.equipstockvalue -= sale.equiptotal[i];
					fseek(fptrequip, (equipment.equipid-1) * sizeof(struct EquipInfo),SEEK_SET);//moves file pointer to the beginning of the file
					fwrite(&equipment, sizeof(struct EquipInfo), 1, fptrequip);//write record to file
					
					i++;
					sale.totequip++;
					printf("\n\t\tEnter -1 to stop adding items to the order. Enter 0 to continue adding items.\n\t\t");
					scanf("%d", &num);
					if (num == -1)
					{
						break;
					}
				}
				while (num == 0);
				break;
				
				case 3:
				i=0;
				j=0;
				sale.totplant=0;
				sale.totequip=0;
				printf("\n\t\t|==================================================|\n");
	        	printf("\t\t|>>>>>>>>>>>>>>>>>> PLANT INFO <<<<<<<<<<<<<<<<<<<<|\n");
	      	  	printf("\t\t|==================================================|\n\n");
				ViewPlant();
				printf("\n\t\t|======================================================|\n");
	        	printf("\t\t|>>>>>>>>>>>>>>>>>> EQUIPMENT INFO <<<<<<<<<<<<<<<<<<<<|\n");
	      	  	printf("\t\t|======================================================|\n\n");
				ViewEquipment();
				do
				{
					printf("\n\n\t\tEnter id of the equipment purchased.\n\t\t");
					scanf("%d",&ide);
				
					fseek(fptrequip, (ide-1) * sizeof(struct EquipInfo), SEEK_SET);
					fread(&equipment, sizeof(struct EquipInfo), 1, fptrequip);//reads a block of data
					
					printf("\n\t\tEnter the quantity of this item that the customer purchased.\n\t\t");
					scanf("%d", &equipnum);
					
					sale.equipquant[i] = equipnum;
					
					sale.equipids[i] = ide;
					
					strcpy(sale.equipnames[i], equipment.equipname);
					
					sale.equipprice[i] = equipment.equipprice;
					sale.cost += sale.equipprice[i]*sale.equipquant[i];
					
					equipment.equipstock=equipment.ogequipstock;
					equipment.equipstockvalue=equipment.ogequipstockvalue;
					
					equipment.equipstock -= sale.equipquant[i];
					equipment.equipstockvalue -= sale.equipprice[i]*sale.equipquant[i];
					fseek(fptrequip, (equipment.equipid-1) * sizeof(struct EquipInfo),SEEK_SET);//moves file pointer to the beginning of the file
					fwrite(&equipment, sizeof(struct EquipInfo), 1, fptrequip);//write record to file
					
					i++;
					sale.totequip++;
					printf("\n\t\tEnter -1 to stop adding equipment to the order. Enter 0 to continue adding equipment.\n\t\t");
					scanf("%d", &num);
					if (num == -1)
					{
						break;
					}
				}
				while (num == 0);
					
				do
				{
					printf("\n\n\t\tEnter id of the plant purchased.\n\t\t");
					scanf("%d",&idp);
				
					fseek(fptrplant, (idp-1) * sizeof(struct PlantInfo), SEEK_SET);
					fread(&plant, sizeof(struct PlantInfo), 1, fptrplant);//reads a block of data
					
					printf("\n\t\tEnter the quantity of this item that the customer purchased.\n\t\t");
					scanf("%d", &plantnum);
					
					if (plantnum>plant.plantstock)
					{
						printf("\n\t\tNot enough in stock. Please enter a value less than %d", plant.plantstock);
						printf("\n\t\tEnter the quantity of this item that the customer purchased.\n\t\t");
						scanf("%d", &plantnum);
					}
					
					sale.plantquant[j] = plantnum;
					
					sale.plantids[j] = idp;
					
					strcpy(sale.plantnames[j], plant.plantname);
					
					sale.plantprice[j] = plant.plantprice;
					sale.cost += sale.plantprice[j]*sale.plantquant[j];
					
					plant.plantstock = plant.ogplantstock;
					plant.plantstockvalue = plant.ogplantstockvalue;
					
					plant.plantstock -= sale.plantquant[j];
					plant.plantstockvalue -= sale.plantprice[j]*sale.plantquant[j];
					fseek(fptrplant, (plant.plantid-1)*sizeof(struct PlantInfo),SEEK_SET);//moves file pointer to the beginning of the file
					fwrite(&plant, sizeof(struct PlantInfo), 1, fptrplant);//write record to the file
					
					j++;
					sale.totplant++;
					printf("\n\t\tEnter -1 to stop adding plants to the order. Enter 0 to continue adding plants.\n\t\t");
					scanf("%d", &num2);
					if (num2 == -1)
					{
						break;
					}
				}
				while (num2 == 0);
				
				break;
			}
			break;
			
			case 2:
			break;
			
			default:
			printf("\n\t\tInvalid option.");
			break;
		}
		fseek(fptrsale, (sale.saleid-1) * sizeof(struct SaleInfo),SEEK_SET);//moves file pointer to the beginning of the file
		fwrite(&sale, sizeof(struct SaleInfo), 1, fptrsale);//write record to file	
	}
	fclose(fptrsale);
	fclose(fptrplant);
	fclose(fptrequip);
}

void UpdateSale()//Update a sale record
{
	int choice;
	printf("\n\t\t1. Search by name to update.");
	printf("\n\t\t2. Search by ID to update.\n\t\t");
	scanf("%d", &choice);
	
	switch (choice)
	{
		case 1:
		UpdateSaleName();
		break;
		
		case 2:
		UpdateSaleId();
		break;
		
		default:
		printf("\n\t\tInvalid option.");
		break;
	}
}//end of funtion

void DeletePlantName()
{
	struct PlantInfo plant = {0, "", 0.0, 0.0, 0, 0.0, 0, 0.0};
	struct PlantInfo deleteplant = {0, "", 0.0, 0.0, 0, 0.0, 0, 0.0};
	char name[SIZE]; 
	int option, found=0; 
	
	FILE *fptrplant;//file pointer
	if	((fptrplant = fopen("SBADATAPLANT.bin", "rb+")) == NULL)
	{
		printf("\n\t\tCannot open file \n");
	}//end if
	
	else
	{
		printf("\n\t\tEnter name of the record that you want to delete.\n");
		printf("\t\tYou chose: ");
		scanf(" %[^\n]s", &name);//allows spaces to be read
		
		while(fread(&plant, sizeof(struct PlantInfo), 1, fptrplant)==1)
		{   
			if(stricmp(name, plant.plantname)==0)
			{                              
				found=1;
				
				printf("\n\t\tId is: %d\n", plant.plantid);
				printf("\n\t\tPlant Name is: %s\n", plant.plantname);
				printf("\n\t\tCost Price/kg is: $%.2f\n", plant.plantcost);	
				printf("\n\t\tSale Price/kg is: $%.2f\n", plant.plantprice);
				printf("\n\t\tAmount in stock is: %d\n", plant.plantstock);
				printf("\n\t\tValue of stock is: $%.2f\n", plant.plantstockvalue);
				break;
			}//end if 
		}//end while
		
		if (found == 1)
		{
			printf("\n\t\tAre you sure you want to delete this record?\n");	
			printf("\t\t1 - yes\n\t\t2 - no\n");
			printf("\n\t\tYou chose: ");
			scanf("%d", &option);
			
			switch (option)
			{
				case 1:
				fseek(fptrplant, (plant.plantid-1)*sizeof(struct PlantInfo), SEEK_SET);//moves file pointer to the beginning of the file
				fwrite(&deleteplant, sizeof(struct PlantInfo), 1, fptrplant);//deletes record by overwriting with a blank record
				break;
				
				case 2:
				break;
				
				default:
				printf("\n\t\tInvalid option.");
				break;
			}//end switch		
		}
			
		if (found == 0)
		{
			printf("\n\t\tRecord not found.\n");
		}				
	}//end else
	fclose(fptrplant);
}

void DeletePlantId()//Delete a plant record
{
	int id, option;
	struct PlantInfo plant = {0, "", 0.0, 0.0, 0, 0.0, 0, 0.0};
	struct PlantInfo deleteplant = {0, "", 0.0, 0.0, 0, 0.0, 0, 0.0};
	int found=0; 
	
	FILE *fptrplant;//file pointer
	if	((fptrplant = fopen("SBADATAPLANT.bin", "rb+")) == NULL)
	{
		printf("\n\t\tCannot open file \n");
	}//end if
		
	else
	{
		printf("\n\t\tEnter id of the record to delete.");
		printf("\n\n\t\tYou chose: ");
		scanf("%d",&id);
		
		fseek(fptrplant, (id-1) * sizeof(struct PlantInfo), SEEK_SET);
		fread(&plant, sizeof(struct PlantInfo), 1, fptrplant);//reads a block of data
		
		if(plant.plantid != 0)
		{
			found=1;
				
			printf("\n\t\tId is: %d\n", plant.plantid);
			printf("\n\t\tPlant Name is: %s\n", plant.plantname);
			printf("\n\t\tCost Price/kg is: $%.2f\n", plant.plantcost);	
			printf("\n\t\tSale Price/kg is: $%.2f\n", plant.plantprice);
			printf("\n\t\tAmount in stock is: %d\n", plant.plantstock);
			printf("\n\t\tValue of stock is: $%.2f\n", plant.plantstockvalue);
			
			printf("\n\t\tAre you sure you want to delete this record?\n");
			printf("\t\t1 - yes\n\t\t2 - no\n");
			printf("\n\t\tYou chose: ");
			scanf("%d", &option);
			
			switch (option)
			{
				case 1:
				fseek(fptrplant, (plant.plantid-1)*sizeof(struct PlantInfo), SEEK_SET);//moves file pointer to the beginning of the file
				fwrite(&deleteplant, sizeof(struct PlantInfo), 1, fptrplant);//deletes record by overwriting with a blank record
				break;
				
				case 2:
				break;
				
				default:
				printf("\n\t\tInvalid option.");
				break;
			}//end switch		
		}//end if
		
		if(found == 0)
		{
			printf("\n\t\tRecord not found.\n");
		}//end if
	}//end else
	fclose(fptrplant);	
}//end of function

void DeletePlant()
{
	int choice;
	
	printf("\n\t\t1. Search by name to delete.");
	printf("\n\t\t2. Search by ID to delete.\n\t\t");
	scanf("%d", &choice);
	
	switch (choice)
	{
		case 1:
		DeletePlantName();
		break;
		
		case 2:
		DeletePlantId();
		break;
		
		default:
		printf("\n\t\tInvalid option.");
		break;
	}
}

void DeleteEquipmentName()
{
	struct EquipInfo equipment = {0, "", 0.0, 0.0, 0, 0.0, 0, 0.0};
	struct EquipInfo deleteequipment = {0, "", 0.0, 0.0, 0, 0.0};
	char name[SIZE];
	int option, found=0;
	
	FILE *fptrequip;//file pointer
	if	((fptrequip = fopen("SBADATAEQUIP.bin", "rb+")) == NULL)
	{
		printf("\n\t\tCannot open file \n");
	}//end if
	
	else
	{
		printf("\n\t\tEnter name of the record that you want to delete.\n");
		printf("\t\tYou chose: ");
		scanf(" %[^\n]s", &name);//allows spaces to be read
	
		while(fread(&equipment, sizeof(struct EquipInfo), 1, fptrequip)==1)
		{   
			if(stricmp(name, equipment.equipname)==0)
			{                              
				found=1;
				
				printf("\n\t\tId is: %d\n", equipment.equipid);
				printf("\n\t\tEquipment Name is: %s\n", equipment.equipname);
				printf("\n\t\tCost Price is: $%.2f\n", equipment.equipcost);
				printf("\n\t\tSale Price is: $%.2f\n", equipment.equipprice);
				printf("\n\t\tAmount in stock is %d\n", equipment.equipstock);
				printf("\n\t\tValue of stock is $%.2f\n", equipment.equipstockvalue);
		
			}//end if
		}//end while
		
		if (found == 1)
		{
			printf("\n\t\tAre you sure you want to delete this record?\n");
			printf("\t\t1 - yes\n\t\t2 - no\n");
			printf("\n\t\tYou chose: ");
			scanf("%d", &option);
			
			switch (option)
			{
				case 1:
				fseek(fptrequip, (equipment.equipid-1) * sizeof(struct EquipInfo), SEEK_SET);//moves file pointer to the beginning of the file
				fwrite(&deleteequipment, sizeof(struct EquipInfo), 1, fptrequip);//deletes record by overwriting with a blank record
				break;
				
				case 2:
				break;
				
				default:
				printf("\n\t\tInvalid option.");
				break;
			}
		}
		
		if (found == 0)
		{
			printf("\n\t\tRecord not found.\n");
		}
	}//end else
	fclose(fptrequip);
}

void DeleteEquipmentId()//Delete an equipment record
{
	int id, option;
	struct EquipInfo equipment = {0, "", 0.0, 0.0, 0, 0.0, 0, 0.0};
	struct EquipInfo deleteequipment = {0, "", 0.0, 0.0, 0, 0.0};
	int found=0; 
	
	FILE *fptrequip;//file pointer
	if	((fptrequip = fopen("SBADATAEQUIP.bin", "rb+")) == NULL)
	{
		printf("\n\t\tCannot open file \n");
	}//end if
		
	else
	{
		printf("\n\t\tEnter id of the record to delete.");
		printf("\n\n\t\tYou chose: ");
		scanf("%d",&id);
		
		fseek(fptrequip, (id-1) * sizeof(struct EquipInfo), SEEK_SET);
		fread(&equipment, sizeof(struct EquipInfo), 1, fptrequip);//reads a block of data
		
		if(equipment.equipid != 0)
		{
			found=1;
			
			printf("\n\t\tId is: %d\n", equipment.equipid);
			printf("\n\t\tEquipment Name is: %s\n", equipment.equipname);
			printf("\n\t\tCost Price is: $%.2f\n", equipment.equipcost);
			printf("\n\t\tSale Price is: $%.2f\n", equipment.equipprice);
			printf("\n\t\tAmount in stock is %d\n", equipment.equipstock);
			printf("\n\t\tValue of stock is $%.2f\n", equipment.equipstockvalue);
			
			printf("\n\t\tAre you sure you want to delete this record?\n");
			printf("\t\t1 - yes\n\t\t2 - no\n");
			printf("\n\t\tYou chose: ");
			scanf("%d", &option);
			
			switch (option)
			{
				case 1:
				fseek(fptrequip, (equipment.equipid-1) * sizeof(struct EquipInfo), SEEK_SET);//moves file pointer to the beginning of the file
				fwrite(&deleteequipment, sizeof(struct EquipInfo), 1, fptrequip);//deletes record by overwriting with a blank record
				break;
				
				case 2:
				break;
				
				default:
				printf("\n\t\tInvalid option.");
				break;
			}
		}//end if

		if(found == 0)
		{
			printf("\n\t\tRecord not found.\n");
		}//end if

	}//end else	
	fclose(fptrequip);
}//end of funtion

void DeleteEquipment()
{
	int choice;
	
	printf("\n\t\t1. Search by name to delete.");
	printf("\n\t\t2. Search by ID to delete.\n\t\t");
	scanf("%d", &choice);
	
	switch (choice)
	{
		case 1:
		DeleteEquipmentName();
		break;
		
		case 2:
		DeleteEquipmentId();
		break;
		
		default:
		printf("\n\t\tInvalid option.");
		break;
	}
}

void DeleteSaleName()
{
	int option, i, j, found = 0;
	char name[SIZE];
	struct SaleInfo sale;
	struct SaleInfo deletesale = {
	0,
	"",
	0.0,
	{0, 0, 0},
	{0, 0, 0},
	{0.0, 0.0, 0.0},	
	{0.0, 0.0, 0.0},	
	{"", "", ""},	
	{"", "", ""},	
	{0, 0, 0},
	{0, 0, 0},
	0,
	0,
	{0.0, 0.0, 0.0},	
	{0.0, 0.0, 0.0}
};
	
	FILE *fptrsale;//file pointer
	if	((fptrsale = fopen("SBADATASALE.bin", "rb+")) == NULL)
	{
		printf("\n\t\tCannot open file \n");
	}//end if
	
	else
	{
		printf("\n\t\tEnter name of the record that you want to delete.\n");
		printf("\t\tYou chose: ");
		scanf(" %[^\n]s", &name);//allows spaces to be read
		
		while(fread(&sale, sizeof(struct SaleInfo), 1, fptrsale)==1)
		{
			if(stricmp(name, sale.customername)==0)
			{
				found=1;
			
				printf("\n\t\tOrder Id is: %d\n", sale.saleid);
				printf("\n\t\tCustomer Name is: %s\n", sale.customername);
				if (sale.totequip > 0)
				{
					printf("\n\t\tEquipment Purchased:\n");
					for(i=0;i<sale.totequip;i++)
					{
						printf("\n\t\t\tItem Name: %s", sale.equipnames + i);
						printf("\n\t\t\tItem Id: %d", sale.equipids[i]);
						printf("\n\t\t\tItem price: $%.2f", sale.equipprice[i]);
						printf("\n\t\t\tQuantity of Item: %d",sale.equipquant[i]);
						printf("\n\t\t\tTotal for Item: $%.2f\n",sale.equiptotal[i]);
					}	
				}
				
				if(sale.totplant > 0)
				{
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
			}
		}
		
		if (found == 1)
		{
			printf("\n\t\tAre you sure you want to delete this record?\n");
			printf("\t\t1 - yes\n\t\t2 - no\n");
			printf("\n\t\tYou chose: ");
			scanf("%d", &option);
			
			switch (option)
			{
				case 1:
				fseek(fptrsale, (sale.saleid-1) * sizeof(struct SaleInfo),SEEK_SET);//moves file pointer to the beginning of the file
				fwrite(&deletesale, sizeof(struct SaleInfo), 1, fptrsale);//write record to file
				break;
				
				case 2:
				break;
				
				default:
				printf("\n\t\tInvalid option.");
				break;
			}	
		}
		
		if(found == 0)
		{
			printf("\n\t\tRecord not found.\n");
		}//end if
	}
	fclose(fptrsale);
}

void DeleteSaleId()//Delete a sale record
{
	int id, option, i, j;
	struct SaleInfo sale;
	struct SaleInfo deletesale = {
	0,
	"",
	0.0,
	{0, 0, 0},
	{0, 0, 0},
	{0.0, 0.0, 0.0},	
	{0.0, 0.0, 0.0},	
	{"", "", ""},	
	{"", "", ""},	
	{0, 0, 0},
	{0, 0, 0},
	0,
	0,
	{0.0, 0.0, 0.0},	
	{0.0, 0.0, 0.0}
};
	int found=0; 
	
	FILE *fptrsale;//file pointer
	if	((fptrsale = fopen("SBADATASALE.bin", "rb+")) == NULL)
	{
		printf("\n\t\tCannot open file \n");
	}//end if
	
	else
	{
		printf("\n\t\tEnter id of the record to delete.");
		printf("\n\n\t\tYou chose: ");
		scanf("%d",&id);
		
		fseek(fptrsale, (id-1) * sizeof(struct SaleInfo), SEEK_SET);
		fread(&sale, sizeof(struct SaleInfo), 1, fptrsale);//reads a block of data
		
		if(sale.saleid != 0)
		{
			found=1;
			
			printf("\n\t\tOrder Id is: %d\n", sale.saleid);
			printf("\n\t\tCustomer Name is: %s\n", sale.customername);
			if (sale.totequip > 0)
			{
				printf("\n\t\tEquipment Purchased:\n");
				for(i=0;i<sale.totequip;i++)
				{
					printf("\n\t\t\tItem Name: %s", sale.equipnames + i);
					printf("\n\t\t\tItem Id: %d", sale.equipids[i]);
					printf("\n\t\t\tItem price: $%.2f", sale.equipprice[i]);
					printf("\n\t\t\tQuantity of Item: %d",sale.equipquant[i]);
					printf("\n\t\t\tTotal for Item: $%.2f\n",sale.equiptotal[i]);
				}	
			}
			
			if(sale.totplant > 0)
			{
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
			
		}
		
		if (found == 1)
		{
			printf("\n\t\tAre you sure you want to delete this record?\n");
			printf("\t\t1 - yes\n\t\t2 - no\n");
			printf("\n\t\tYou chose: ");
			scanf("%d", &option);
			
			switch (option)
			{
				case 1:
				fseek(fptrsale, (sale.saleid-1) * sizeof(struct SaleInfo),SEEK_SET);//moves file pointer to the beginning of the file
				fwrite(&deletesale, sizeof(struct SaleInfo), 1, fptrsale);//write record to file
				break;
				
				case 2:
				break;
				
				default:
				printf("\n\t\tInvalid option.");
				break;
			}	
		}
		
		if(found == 0)
		{
			printf("\n\t\tRecord not found.\n");
		}//end if
	}//end else
	fclose(fptrsale);
}//end of funtion

void DeleteSale()
{
	int choice;
	
	printf("\n\t\t1. Search by name to delete.");
	printf("\n\t\t2. Search by ID to delete.\n\t\t");
	scanf("%d", &choice);
	
	switch (choice)
	{
		case 1:
		DeleteSaleName();
		break;
		
		case 2:
		DeleteSaleId();
		break;
		
		default:
		printf("\n\t\tInvalid option.");
		break;
	}
	
}

void CreateFile()//Sub menu to allow user to select what type of file they would like to create
{
	int option;
	printf("\n\tWhat type of file would you like to create.\n\n");
	printf("\t0. Exit to main menu.\n\n");
	printf("\t1. Create a file for plant records.\n\n");
	printf("\t2. Create a file for equipment records.\n\n");
	printf("\t3. Create a file for sale records.\n\n");
	printf("\t\tYou chose: ");
	scanf("%d", &option);
	printf("\n\t--------------------------------------------------------------------");
	
	switch(option)
	{
		case 0:
		break;
		
		case 1:
		CreatePlantFile();
		break;
		
		case 2:
		CreateEquipmentFile();
		break;
		
		case 3:
		CreateSaleFile();
		break;
	}
	printf("\n\n\t\tPress enter to return to the main menu.\n\t\t");
}//end of funtion

void View()//sub menu allows user to select what type of record to view
{
	int option;
	
	printf("\n\tWhat type of record would you like to view?\n\n");
	printf("\t0. Exit to main menu.\n\n");
	printf("\t1. View plant record.\n\n");
	printf("\t2. View equipment record.\n\n");
	printf("\t3. View sale record.\n\n");
	printf("\t\tYou chose: ");
	scanf("%d", &option);
	printf("\n\t--------------------------------------------------------------------");
	
	switch(option)
	{
		case 0:
		break;
		
		case 1:
		system("cls");
		printf("\n\t\t|==================================================|\n");
    	printf("\t\t|>>>>>>>>>>>>>>>>>> PLANT INFO <<<<<<<<<<<<<<<<<<<<|\n");
  	  	printf("\t\t|==================================================|\n\n");
		ViewPlant();
		break;
		
		case 2:
		system("cls");
		printf("\n\t\t|======================================================|\n");
    	printf("\t\t|>>>>>>>>>>>>>>>>>> EQUIPMENT INFO <<<<<<<<<<<<<<<<<<<<|\n");
  	  	printf("\t\t|======================================================|\n\n");
		ViewEquipment();
		break;
			
		case 3:
		system("cls");
		printf("\n\t\t|=================================================|\n");
    	printf("\t\t|>>>>>>>>>>>>>>>>>> SALE INFO <<<<<<<<<<<<<<<<<<<<|\n");
  	  	printf("\t\t|=================================================|\n\n");
		ViewSale();
		break;
		
		default:
		printf("\n\t\tInvalid option.");
		break;
	}
	printf("\n\n\t\tPress enter to return to the main menu.\n\t\t");
}//end of funtion 

void Add()//sub menu allows user to select what type of record to add
{
	int option;

	printf("\n\tWhat type of record would you like to add?\n\n");
	printf("\t0. Exit to main menu.\n\n");
	printf("\t1. Add plant record.\n\n");
	printf("\t2. Add equipment record.\n\n");
	printf("\t3. Add sale record.\n\n");
	printf("\t\tYou chose: ");
	scanf("%d", &option);
	printf("\n\t--------------------------------------------------------------------");
	
	switch(option)
	{
		case 0:
		break;
		
		case 1:
		system("cls");
		printf("\n\t|========================================================|\n");
 		printf("\t|>>>>>>>>>>>>>>>>>> ADD PLANT RECORD <<<<<<<<<<<<<<<<<<<<|\n");
  		printf("\t|========================================================|\n\n");
  		AddPlant();
		break;
		
		case 2:
		system("cls");
		printf("\n\t|============================================================|\n");
 		printf("\t|>>>>>>>>>>>>>>>>>> ADD EQUIPMENT RECORD <<<<<<<<<<<<<<<<<<<<|\n");
  		printf("\t|============================================================|\n\n");
  		AddEquip();
		break;
		
		case 3:
		system("cls");
		printf("\n\t|=======================================================|\n");
 		printf("\t|>>>>>>>>>>>>>>>>>> ADD SALE RECORD <<<<<<<<<<<<<<<<<<<<|\n");
  		printf("\t|=======================================================|\n\n");
  		AddSale();
		break;
		
		default:
		printf("\n\t\tInvalid option.");
		break;
	}
	printf("\n\n\t\tPress enter to return to the main menu.\n\t\t");
}//end of funtion 

void Search()//sub menu allows user to select what type of record to search for
{
	int option;
	
	printf("\n\tWhat type of record would you like to search?\n\n");
	printf("\t0. Exit to main menu.\n\n");
	printf("\t1. Search plant record.\n\n");
	printf("\t2. Search equipment record.\n\n");
	printf("\t3. Search sale record.\n\n");
	printf("\t\tYou chose: ");
	scanf("%d", &option);
	printf("\n\t--------------------------------------------------------------------");
	
	switch(option)
	{
		case 0:
		break;
		
		case 1:
		system("cls");
		printf("\n\t|===========================================================|\n");
 		printf("\t|>>>>>>>>>>>>>>>>>> SEARCH PLANT RECORD <<<<<<<<<<<<<<<<<<<<|\n");
  		printf("\t|===========================================================|\n\n");
		SearchPlant();
		break;
		
		case 2:
		system("cls");
		printf("\n\t|===============================================================|\n");
 		printf("\t|>>>>>>>>>>>>>>>>>> SEARCH EQUIPMENT RECORD <<<<<<<<<<<<<<<<<<<<|\n");
  		printf("\t|===============================================================|\n\n");
		SearchEquipment();
		break;
		
		case 3:
		system("cls");
		printf("\n\t|==========================================================|\n");
 		printf("\t|>>>>>>>>>>>>>>>>>> SEARCH SALE RECORD <<<<<<<<<<<<<<<<<<<<|\n");
  		printf("\t|==========================================================|\n\n");
		SearchSale();
		break;
		
		default:
		printf("\n\t\tInvalid option.");
		break;
	}
	printf("\n\n\t\tPress enter to return to the main menu.\n\t\t");
}//end of funtion 

void Update()//sub menu allows user to select what type of record to update
{
	int option;
	
	printf("\n\tWhat type of record would you like to update?\n\n");
	printf("\t0. Exit to main menu.\n\n");
	printf("\t1. Update plant record.\n\n");
	printf("\t2. Update equipment record.\n\n");
	printf("\t3. Update sale record.\n\n");
	printf("\t\tYou chose: ");
	scanf("%d", &option);
	printf("\n\t--------------------------------------------------------------------");
	
	switch(option)
	{
		case 0:
		break;
		
		case 1:	
		system("cls");
		printf("\n\t|===========================================================|\n");
 		printf("\t|>>>>>>>>>>>>>>>>>> UPDATE PLANT RECORD <<<<<<<<<<<<<<<<<<<<|\n");
  		printf("\t|===========================================================|\n\n");
  		UpdatePlant();
		break;
		
		case 2:
		system("cls");
		printf("\n\t|===============================================================|\n");
 		printf("\t|>>>>>>>>>>>>>>>>>> UPDATE EQUIPMENT RECORD <<<<<<<<<<<<<<<<<<<<|\n");
  		printf("\t|===============================================================|\n\n");
		UpdateEquipment();
		break;
		
		case 3:
		system("cls");
		printf("\n\t|==========================================================|\n");
 		printf("\t|>>>>>>>>>>>>>>>>>> SEARCH SALE RECORD <<<<<<<<<<<<<<<<<<<<|\n");
  		printf("\t|==========================================================|\n\n");
		UpdateSale();
		break;
		
		default:
		printf("\n\t\tInvalid option.");
		break;
	}
	printf("\n\n\t\tPress enter to return to the main menu.\n\t\t");
}//end of funtion 

void Delete()//sub menu allows user to select what type of record to delete
{
	int option;
	
	printf("\n\tWhat type of record would you like to delete?\n\n");
	printf("\t0. Exit to main menu.\n\n");
	printf("\t1. Delete plant record.\n\n");
	printf("\t2. Delete equipment record.\n\n");
	printf("\t3. Delete sale record.\n\n");
	printf("\t\tYou chose: ");
	scanf("%d", &option);
	printf("\n\t--------------------------------------------------------------------");
	
	switch(option)
	{
		case 0:
		break;
		
		case 1:
		system("cls");
		printf("\n\t|===========================================================|\n");
 		printf("\t|>>>>>>>>>>>>>>>>>> DELETE PLANT RECORD <<<<<<<<<<<<<<<<<<<<|\n");
  		printf("\t|===========================================================|\n\n");
		DeletePlant();
		break;
		
		case 2:
		system("cls");
		printf("\n\t|===============================================================|\n");
 		printf("\t|>>>>>>>>>>>>>>>>>> DELETE EQUIPMENT RECORD <<<<<<<<<<<<<<<<<<<<|\n");
  		printf("\t|===============================================================|\n\n");
		DeleteEquipment();
		break;
		
		case 3:
		system("cls");
		printf("\n\t|==========================================================|\n");
 		printf("\t|>>>>>>>>>>>>>>>>>> DELETE SALE RECORD <<<<<<<<<<<<<<<<<<<<|\n");
  		printf("\t|==========================================================|\n\n");
		DeleteSale();
		break;
		
		default:
		printf("\n\t\tInvalid option.");
		break;
	}
	printf("\n\n\t\tPress enter to return to the main menu.\n\t\t");
}//end of funtion 

void menu()//give user a list of choices
{
	system("cls");
	int choice;
    do
    {
    	printf("\n\n\n\t|===========================================================|\n");
        printf("\t|>>>>>>>>>>>>>>>>>> PLANT SHOP DATABASE <<<<<<<<<<<<<<<<<<<<|\n");
        printf("\t|===========================================================|\n\n");
        printf("\n\t0.\tExit.\n");
        printf("\n\t1.\tCreate database.\n");
        printf("\n\t2.\tView records.\n");
		printf("\n\t3.\tAdd records.\n");
        printf("\n\t4.\tSearch records.\n");
		printf("\n\t5.\tUpdate records.\n");
        printf("\n\t6.\tDelete records.\n");
        printf("\n\t\tWhat would you like to do?\n");
        printf("\n\t\tYou chose: ");
        
       	while (scanf("%d",&choice)!=1)
       	{	
       		printf("\n\t\tInput must be an integer\n");
			printf("\n\t\tWhat would you like to do?\n");
       		printf("\n\t\tYou chose: ");
       		scanf("%d",&choice);
       		while ((getchar()) != '\n');
		}
		
        switch(choice)
        {
        	case 0:
        	printf("\n\t\tExiting...");
        	exit(1);
        	break;
        	
        	case 1:
        	system("cls");
        	printf("\n\t|===========================================================|\n");
        	printf("\t|>>>>>>>>>>>>>>>>>>>>>>> CREATE FILE <<<<<<<<<<<<<<<<<<<<<<<|\n");
        	printf("\t|===========================================================|\n\n");
        	CreateFile();
        	while ((getchar()) != '\n');
			while ((getchar()) != '\n');
        	system("cls");
        	break;

            case 2:
            system("cls");
            printf("\n\t|===========================================================|\n");
        	printf("\t|>>>>>>>>>>>>>>>>>>>>>> VIEW RECORDS <<<<<<<<<<<<<<<<<<<<<<<|\n");
        	printf("\t|===========================================================|\n\n");
            View();
            while ((getchar()) != '\n');
			while ((getchar()) != '\n');
            system("cls");
            break;
            
            case 3:
            system("cls");	
			printf("\n\t|===========================================================|\n");
		    printf("\t|>>>>>>>>>>>>>>>>>>>>>> ADD RECORDS <<<<<<<<<<<<<<<<<<<<<<<<|\n");
		    printf("\t|===========================================================|\n\n");
		    Add();
		    while ((getchar()) != '\n');
			while ((getchar()) != '\n');
            system("cls");
            break;
			
			case 4:
            system("cls");	
            printf("\n\t|===========================================================|\n");
        	printf("\t|>>>>>>>>>>>>>>>>>>>>> SEARCH RECORDS <<<<<<<<<<<<<<<<<<<<<<|\n");
        	printf("\t|===========================================================|\n\n");
            Search();
            while ((getchar()) != '\n');
			while ((getchar()) != '\n');
            system("cls");
            break;
            	
            case 5:
            system("cls");	
            printf("\n\t|===========================================================|\n");
        	printf("\t|>>>>>>>>>>>>>>>>>>>>> UPDATE RECORDS <<<<<<<<<<<<<<<<<<<<<<|\n");
        	printf("\t|===========================================================|\n\n");
            Update();
            while ((getchar()) != '\n');
			while ((getchar()) != '\n');
            system("cls");
            break;

            case 6:
            system("cls");	
            printf("\n\t|===========================================================|\n");
        	printf("\t|>>>>>>>>>>>>>>>>>>>>> DELETE RECORDS <<<<<<<<<<<<<<<<<<<<<<|\n");
        	printf("\t|===========================================================|\n\n");
            Delete();
            while ((getchar()) != '\n');
			while ((getchar()) != '\n');
            system("cls");
            break;
       
            default :
            printf("\n\t\tInvalid option\n");
            printf("\n\n\t\tPress enter to return to the main menu.\n\t\t");
			while ((getchar()) != '\n');
			while ((getchar()) != '\n');
            menu();
            break;
        }
    }
    while(choice != 0);
}//end of function

void Password()//function to prompt user to enter the password. Exits the program if the password is entered wrongly three times
{
	char guess[SIZE];
	int i, ret;
	
	for (i = 3; i > 0; i--)
	{
		printf("\n\tEnter the password to access the database.\n\tPassword: ");
		gets(guess);
		
		ret = strcmp(guess, PASSWORD);
		
		if (ret == 0)
		{
			menu();
		}//end if
		
		else
		{
			if (i > 2)
			{
				printf("\tWrong. You have %d tries left.\n", i-1);	
			}//end if
			
			if (i == 2)
			{
				printf("\tWrong. You have %d try left.\n", i-1);
			}//end if
			
			if (i == 1)
			{
				printf("\tWrong. You have entered the incorrect password too many times.\n\tExiting...");
				exit(1);
			}//end if
			
		}//end else
		
	}//end for
}//end of function

main()
{
	printf("\n\n\n\t|===========================================================|\n");
    printf("\t|>>>>>>>>>>>>>>>>>> PLANT SHOP DATABASE <<<<<<<<<<<<<<<<<<<<|\n");
    printf("\t|===========================================================|\n\n");
        
    Password();
    
    return 0;
}
