#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct futbolcu{
	int formaNo;
	char futbolcuIsmi[25];
	struct futbolcu *left, *right;
}futbolcuKaydi;

futbolcuKaydi *kok=NULL;

futbolcuKaydi *search(), *del(),*scankey();
void add(),listing(), printTree();

int main(int argc, char *argv[]) {
futbolcuKaydi *newData,*adres;
int forma,secim;
while(1){
	printf("#########################################\n\t\t\t\t\t#\n");
	printf("[1]Ekleme\t\t\t\t#\n[2]Listeleme\t\t\t\t#\n[3]Arama\t\t\t\t#\n[4]Silme\t\t\t\t#\n[0]Cikis\t\t\t\t#\nSeciminizi giriniz: \t\t\t#\n");
	scanf("%d",&secim);
	switch(secim){
		case 1:
			newData=scankey();
			add(kok,newData);
			break;
		case 2:
			if(kok!=NULL)
				listing(kok);
			else
				printf("BOS LiSTE\n\n");
			break;
		case 3:
			printf("Aranan: ");
			scanf("%d",&forma);
			adres=search(kok,forma);
			if(adres==NULL)
				printf("!!!Aranan Bulunamadi!!!\n\n");
			else
				printTree(adres);
				break;
			case 4:
				printf("Silinecek: ");
				scanf("%d",&forma);
				adres=del(kok,forma);
				if(adres!=NULL)
					printf("Silme islemi Basarili...\n\n");
				else
					printf("!!!Silmek istediginiz eleman yok!!!\n\n");
				break;
			case 0:
				printf("Cikis Yapiliyor....");
				exit(0);
			default:
				printf("!!!Yanlis secim!!!");
	}
}
}

void add(futbolcuKaydi *root, futbolcuKaydi *eklenen){ //düğüm ekleme fonksiyonumuz

	if(root==NULL)
		kok=eklenen;  //ağacımızın kökü boşsa eklenecek olan düğüm kök olur
	else{
		if(eklenen->formaNo<=root->formaNo){  //eklenen kökten küçükse sola, büyükse sağa eklenir
			if(root->left==NULL)     //kökün solu boşsa soluna eklenir, değilse yeni dal eklenir
				root->left=eklenen;
			else 
				add(root->left,eklenen);
		}
		else{
		
				if(root->right==NULL)
					root->right=eklenen;
				else 
					add(root->right,eklenen);
		}
	}
}
void listing(futbolcuKaydi *root){
	if(root!=NULL){
		listing(root->left);
		printTree(root);
		listing(root->right);
	}
}
futbolcuKaydi *search(futbolcuKaydi *root, int aranan){
	while(root!=NULL && root->formaNo!=aranan){
		if(aranan<=root->formaNo)
			root=root->left;
		else
			root=root->right;
	}
	return root;
}
futbolcuKaydi *del(futbolcuKaydi *root, int silinecek){//düğüm sil
	futbolcuKaydi *pa, *p, *pc, *r,*l;
	if(root==NULL)
		return NULL;
	p=root;
	pa=NULL;
	
while(p!=NULL && p->formaNo!=silinecek){//silinenin ailesini bul
		pa=p;	
		if(silinecek<=p->formaNo)
		p=p->left;
	else
		p=p->right;
	}
	if(p==NULL) //bulunmazsa null döndür
		return NULL;
	if(p->left!=NULL&&p->right!=NULL){//2 çocuk varsa
		l=p->left;
		r=p;
		while(l->right!=NULL){ //sol alt ağacın en büyük düğümünü arar
			r=l;
			l=l->right;
		}
		p->formaNo=l->formaNo; //silinen düğümün üstüne kopyalama
		strcpy(p->futbolcuIsmi,l->futbolcuIsmi);
		p=l;
		pa=r;}
		if(p->left!=NULL) //artık p'nin çocuk sayısı en fazla 1'dir
			pc=p->left;
		else
			pc=p->right;
		
		 //düğüm silme işlemi:
		if(p==root) //kök mü silinecek
			kok=pc;
		else{//veri sağda mı solda mı 
			if(p=pa->left)
				pa->left=pc;
			else
				pa->right=pc;
		}
		free(p);
		return p;
}
void printTree(futbolcuKaydi *giris){ //düğüm bilgisini yazdırma fonksiyonu
	printf("\n--------------------------------------------\n");
	printf("Forma No: %d\tFutbolcu ismi%s\n",giris->formaNo,giris->futbolcuIsmi);
		printf("\n--------------------------------------------\n");
}
futbolcuKaydi *scankey() {  //kayıt bilgisi okuma fonksiyonu
	futbolcuKaydi *yeni;
	yeni = malloc(sizeof(futbolcuKaydi));
	if(yeni==NULL){
		printf("!!!HAFIZA DOLU!!!");
		return NULL;
	}

		printf("Forma Numarasi Gir: ");
		scanf("%d",&(yeni->formaNo));
		printf("Futbolcu ismini gir: ");
		scanf("%s",yeni->futbolcuIsmi);
		yeni->right=NULL;
		yeni->left=NULL;
		return yeni;
}
