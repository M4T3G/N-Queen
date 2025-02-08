#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/*
@brief recursive bir �ekilde i� i�e n tane for d�ng�s� olu�turur ve her bir for bir vezirimizi temsil eder.
@param derinlik ka��nc� for i�inde oldu�umuzu ifade eder. yani ka��nc� vezirle i�lem yapt���m�z� s�yler.
@param n kullan�c�dan al�nan vezir say�s�
@param sutunlar her bir g�z� bir vezirin sat�r�n� ifade eder ve o g�zdeki de�er ise s�tundaki yerini g�sterir.
@param count toplam ��z�m say�s�n� tutar.
*/
void optimized_1_helper(int derinlik, int n, int sutunlar[],int *count) {
	int i=0,j,flag=1;
	char **board;
    if (derinlik == n) { // En i�teki d�ng�ye ula�t�ysak
        while(i<n-1 && flag){ 
        	j=i+1;
        	while(j<n && flag){
        		if(sutunlar[i]==sutunlar[j] || abs(sutunlar[i] - sutunlar[j]) == abs(i - j)){  // T�m vezirler ayn� s�tundalar m� ve �aprazlar m� kontrol�
        			flag=0; //E�er �ylelerse 
				}
				j++;
			}
			i++;
		}
		if(flag==1){  //��z�m �art�n� kar��l�yor.
			(*count)++; //Toplam ��z�m say�s�n� 1 art�r.
			// Tahta i�in bellek tahsis et
    		board = (char **)malloc(n * sizeof(char *));
    		for (i = 0; i < n; i++) {
        	board[i] = (char *)malloc(n * sizeof(char));
        		for (j = 0; j < n; j++) {
        	   		board[i][j] = '.';   //satran� tahtas�nda bo� g�zleri . ile ifade et
        		}
    		}
			for (j = 0; j < n; j++) {
            	board[j][sutunlar[j]] = 'Q';   //satran� tahtas�nda dolu g�zleri Q ile ifade et
        	}
        	// Tahtay� yazd�r
        	for (i = 0; i < n; i++) {
            	for (j = 0; j < n; j++) {
                	printf("%c", board[i][j]);  //Tahtay� yazd�r.
            	}
            	printf("\n");
        	}
        	printf("Cozum %d: ", *count);
        	for (j = 0; j < n; j++) {
            	printf("(%d,%d) ", j,sutunlar[j]);  //��z�mlerin s�ras�yla sat�r ve s�t�n numaras�n� yazd�r.
        	}		
        	printf("\n");
        	printf("\n");
        	//Tabloyu serbest b�rak.
        	for(i=0;i<n;i++){
				free(board[i]);
			}
			free(board);
		}
        return;
    }

    for ( i = 0; i < n; i++) {
        sutunlar[derinlik] = i; //Vezirin o anki yerini ata.
        optimized_1_helper(derinlik + 1, n, sutunlar,count); // Bir sonraki derinli�e in
    }
}

/*
@brief recursive bir �ekilde i� i�e n tane for d�ng�s� olu�turur ve her bir for bir vezirimizi temsil eder.
@param depth ka��nc� for i�inde oldu�umuzu ifade eder. yani ka��nc� vezirle i�lem yapt���m�z� s�yler.
@param n kullan�c�dan al�nan vezir say�s�
@param sutunlar her bir g�z� bir vezirin sat�r�n� ifade eder ve o g�zdeki de�er ise s�tundaki yerini g�sterir.
@param count toplam ��z�m say�s�n� tutar.
@param used bu dizi her bir g�z� s�tunun numaras�n� ifade eder. i�indeki de�er ise o s�tunda vezir varsa 1 yoksa 0 .
*/
void optimized_2_helper(int n, int depth, int used[], int sutunlar[],int *count) {
	int i=0,j,flag=1;
	char **board;
    if (depth == n) { // T�m elemanlar yerle�tirildi
        while(i<n-1 && flag){
        	j=i+1;
        	while(j<n && flag){
        		if(abs(sutunlar[i] - sutunlar[j]) == abs(i - j)){  //// T�m vezirler �aprazlar m� kontrol�
        			flag=0;
				}
				j++;
			}
			i++;
		}
		if(flag==1){ //�art� kar��lad�
			(*count)++;  //Toplam ��z�m say�s�n� 1 art�r.
			// Tahta i�in bellek tahsis et
    		board = (char **)malloc(n * sizeof(char *));
    		for (i = 0; i < n; i++) {
        	board[i] = (char *)malloc(n * sizeof(char));
        		for (j = 0; j < n; j++) {
        	   		board[i][j] = '.';  //satran� tahtas�nda bo� g�zleri . ile ifade et
        		}
    		}
			for (j = 0; j < n; j++) {
            	board[j][sutunlar[j]] = 'Q';  //satran� tahtas�nda dolu g�zleri Q ile ifade et
        	}
        	// Tahtay� yazd�r
        	for (i = 0; i < n; i++) {
            	for (j = 0; j < n; j++) {
                	printf("%c", board[i][j]);  //Tahtay� yazd�r.
            	}
            	printf("\n");
        	}
        	printf("Cozum %d: ", *count);
        	for (j = 0; j < n; j++) {
            	printf("(%d,%d) ", j,sutunlar[j]); //��z�mlerin s�ras�yla sat�r ve s�t�n numaras�n� yazd�r.
        	}		
        	printf("\n");
        	printf("\n");
        	//Tabloyu serbest b�rak.
        	for(i=0;i<n;i++){
				free(board[i]);
			}
			free(board);
		}
        return;
    }

    for (i = 0; i < n; i++) { // Her eleman i�in d�ng�
        if (!used[i]) { // Daha �nce kullan�lmam�� elemanlar� kontrol et
            used[i] = 1; // Eleman� i�aretle (kullan�ld�)
            sutunlar[depth] = i; // Eleman� perm�tasyona ekle
            optimized_2_helper(n, depth + 1, used, sutunlar,count); // Bir sonraki seviyeye ge�
            used[i] = 0; // Geri d�n�� (backtrack) i�in eleman� serbest b�rak
        }
    }
}

/*
@brief ��z�mler matrisindeki ��z�mler ile o anda ��z�m aday� de�erleri k�yaslar ve birbirinden farkl� ise ��z�mler matrisine ekler.
@param satirlar vezirlerin bulundu�u sat�r indisini tutar.
@param n kullan�c�dan al�nan vezir say�s�
@param sutunlar vezirlerin bulundu�u s�tun indisini tutar.
@param count toplam ��z�m say�s�n� tutar.
@param cozumler bu matris count de�erindeki sat�ra ��z�m�n sat�rlar�n�, count +1 sat�r�na ��z�m�n s�tunlar�n� atar.
*/
void tekrar_kontrol(int n, int sutunlar[], int *count, int satirlar[], int ***cozumler) {
    int i, j,k, eslesme = 0;

    if (*count == 0) {
        // �lk ��z�m bulunursa belle�i ay�r
        *cozumler = (int **)malloc(2 * sizeof(int *));
        for (i = 0; i < 2; i++) {
            (*cozumler)[i] = (int *)malloc(n * sizeof(int));
        }
        for (i = 0; i < n; i++) {
            (*cozumler)[0][i] = satirlar[i];  //��z�m�n sat�rlar�n� cozumler tablosunun ilk sat�r�na ekle.
            (*cozumler)[1][i] = sutunlar[i];  //��z�m�n s�tunlar�n� cozumler tablosunun ikinci sat�r�na ekle. Yani tablo boyutu=count*2
        }
        (*count)++;  //Toplam ��z�m say�s�n� art�r.
    } else {
        for (i = 0; i < (*count) * 2; i += 2) {  //��z�m tablosunu gez.
            for (j = 0; j < n; j++) {  // ��z�m aday�n�n sat�rlar�n� gez.
            	for(k=0;k<n;k++){  //��z�m aday�n�n s�tunlar�n� gez.
            		if ((*cozumler)[i][k] == satirlar[j] && (*cozumler)[i + 1][k] == sutunlar[j]) //��z�m aday�n�n �nceki t�m ��z�mlerle herhangi bir sat�r ve s�tun say�s� ayn� olursa
                    eslesme++;  //bu de�i�ken bir art�r.
				}
            }
            if (eslesme == n) return; // ��z�m daha �nce kaydedilmi�. Ayn� ��z�m var zaten tabloda.s
            eslesme = 0;
        }

        // Yeni ��z�m� kaydetmek i�in belle�i geni�let
        *cozumler = (int **)realloc(*cozumler, ((*count) * 2 + 2) * sizeof(int *));
        for (i = (*count) * 2; i < ((*count) * 2 + 2); i++) {
            (*cozumler)[i] = (int *)malloc(n * sizeof(int));
        }

        for (j = 0; j < n; j++) {
            (*cozumler)[(*count) * 2][j] = satirlar[j];  //Yeni ��z�m�n sat�rlar�n� tabloya ekle.
            (*cozumler)[(*count) * 2 + 1][j] = sutunlar[j]; //Yeni ��z�m�n sutunlar�n� tabloya ekle.
        }
        (*count)++;  //Toplam ��z�m say�s�n� art�r.
    }
}

/*
@brief recursive �ekilde vezirlerin s�tunlar�n� de�i�tirerek ��z�m olma ihtimallerini de�erlendirir.
@param derinlik ka��nc� for i�inde oldu�umuzu ifade eder. yani ka��nc� vezirle i�lem yapt���m�z� s�yler.
@param satirlar vezirlerin bulundu�u sat�r indisini tutar.
@param n kullan�c�dan al�nan vezir say�s�
@param sutunlar vezirlerin bulundu�u s�tun indisini tutar.
@param count toplam ��z�m say�s�n� tutar.
@param cozumler bu matris count de�erindeki sat�ra ��z�m�n sat�rlar�n�, count +1 sat�r�na ��z�m�n s�tunlar�n� atar.
*/
void brute_force_helper2(int derinlik, int n, int sutunlar[], int *count, int satirlar[],int ***cozumler) {
    int i, j, flag;

    if (derinlik == n) { // T�m s�tunlar yerle�ti
        flag = 1;
        for (i = 0; i < n - 1 && flag; i++) {
            for (j = i + 1; j < n && flag; j++) {
                // �ak��ma kontrol�: Ayn� s�tun, ayn� sat�r veya �apraz
                if (sutunlar[i] == sutunlar[j] || 
                    satirlar[i] == satirlar[j] || 
                    abs(sutunlar[i] - sutunlar[j]) == abs(satirlar[i] - satirlar[j])) {
                    flag = 0; // �ak��ma bulundu
                }
            }
        }

        if (flag) { //�ak��ma yoksa ��z�m aday� olur.
            tekrar_kontrol(n, sutunlar, count, satirlar,cozumler);
        }
        return;
    }

    for (i = 0; i < n; i++) { // S�tunlar� s�rayla dene
        sutunlar[derinlik] = i;
        brute_force_helper2(derinlik + 1, n, sutunlar, count, satirlar,cozumler);
    }
}

/*
@brief recursive �ekilde vezirlerin sat�rlar�n� de�i�tirerek ��z�m olma ihtimallerini de�erlendirir.
@param derinlik ka��nc� for i�inde oldu�umuzu ifade eder. yani ka��nc� vezirle i�lem yapt���m�z� s�yler.
@param satirlar vezirlerin bulundu�u sat�r indisini tutar.
@param n kullan�c�dan al�nan vezir say�s�
@param sutunlar vezirlerin bulundu�u s�tun indisini tutar.
@param count toplam ��z�m say�s�n� tutar.
@param cozumler bu matris count de�erindeki sat�ra ��z�m�n sat�rlar�n�, count +1 sat�r�na ��z�m�n s�tunlar�n� atar.
*/
void brute_force_helper1(int derinlik, int n, int satirlar[], int *count, int sutunlar[],int ***cozumler) {
    int i;

    if (derinlik == n) { // T�m sat�rlar yerle�ti
        brute_force_helper2(0, n, sutunlar, count, satirlar,cozumler);
        return;
    }

    for (i = 0; i < n; i++) { // Sat�rlar� s�rayla dene
        satirlar[derinlik] = i;
        brute_force_helper1(derinlik + 1, n, satirlar, count, sutunlar,cozumler);
    }
}


/*
@brief Tahtan�n �zerindeki bir s�tunun g�venli olup olmad���n� kontrol eder.
@param s�tunlar ��z�m aday�. her bir g�z� bir vezirin sat�r�n� ifade eder ve o g�zdeki de�er ise s�tundaki yerini g�sterir.
@param row ilgili sat�r de�eri
@param ilgili sutun de�eri
@return E�er tabloya yerle�tirilmeye uygunsa 1 de�ilse 0 d�nd�r�r.
*/
int isSafe(int sutunlar[], int row, int col) {
	int i;
    for (i = 0; i < row; i++) {
        // Ayn� s�tunda veya �aprazda bir vezir varsa
        if (sutunlar[i] == col || abs(sutunlar[i] - col) == abs(i - row)) {
            return 0;
        }
    }
    return 1;
}


/*
@brief recursive �ekilde vezirlerin s�tunlar�n� de�i�tirerek ��z�m olma ihtimallerini de�erlendirir.
@param row hangi sat�rda i�lem yapt���m�z bilgisini tutar.
@param n kullan�c�dan al�nan vezir say�s�
@param sutunlar her bir g�z� bir vezirin sat�r�n� ifade eder ve o g�zdeki de�er ise s�tundaki yerini g�sterir.
@param count toplam ��z�m say�s�n� tutar.
@param cozumler bu matris ��z�mlerin s�tundaki yerlerini tutar.
*/
void backtracking_helper(int sutunlar[], int row, int n, int ***cozumler,int *count) {
	int i,col;
    // T�m vezirler yerle�tirildiyse ��z�m� kaydet
    if (row == n) {
        (*count)++;

    	// �lk ��z�m i�in veya mevcut alan� geni�letmek i�in realloc
    	(*cozumler) = realloc((*cozumler), (*count) * sizeof(int *));

    	// Yeni ��z�m i�in alan ay�r
    	(*cozumler)[(*count) - 1] = malloc(n * sizeof(int));

    	// ��z�m� ��z�m tablosuna ekleme
    	for (i = 0; i < n; i++) {
    	    (*cozumler)[(*count) - 1][i] = sutunlar[i];
    	}
    	    return;
    }

    	// S�radaki sat�rda her s�tun i�in kontrol et
   	for (col = 0; col < n; col++) {
        if (isSafe(sutunlar, row, col)) {
            sutunlar[row] = col; // Veziri bu s�tuna yerle�tir
            backtracking_helper(sutunlar, row + 1, n,cozumler,count); // Sonraki sat�ra ge�
        }
    }
}

/*
@brief optimized_1 ��z�m y�ntemini �al��t�r�r ve ekrana toplam ka� ��z�m oldu�unu ve toplam �al��ma s�resini yazd�r�r.
@param n kullan�c�dan al�nan vezir say�s�
@param solved_time2 y�ntemin �al��ma s�resi
*/
void optimized_1(int n,double *solved_time2){
	int i,j,count=0;
	clock_t start, end;
	double solved_time;
	int *sutunlar;
	sutunlar=(int*)malloc(n*sizeof(int ));
	start = clock();
	optimized_1_helper(0,n,sutunlar,&count);
	end = clock();
	*solved_time2=(double)(end - start) / CLOCKS_PER_SEC;
	printf("\nn=%d icin OPTIMIZED_1 yontemi %d cozum buldu ve %.2f saniye surdu.\n", n, count, *solved_time2);
	free(sutunlar);
}

/*
@brief optimized_2 ��z�m y�ntemini �al��t�r�r ve ekrana toplam ka� ��z�m oldu�unu ve toplam �al��ma s�resini yazd�r�r.
@param n kullan�c�dan al�nan vezir say�s�
@param solved_time3 y�ntemin �al��ma s�resi
*/
void optimized_2(int n,double *solved_time3){
	int i,j,count=0;
	clock_t start, end;
	double solved_time;
	int *used,*sutunlar;
	used=(int*)malloc(n*sizeof(int ));
	for (i = 0; i < n; i++) {
        used[i] = 0;
    }
	sutunlar=(int*)malloc(n*sizeof(int ));
	start = clock();
	optimized_2_helper(n, 0, used, sutunlar,&count);
	end = clock();
	*solved_time3=(double)(end - start) / CLOCKS_PER_SEC;
	printf("\nn=%d icin OPTIMIZED_2 yontemi %d cozum buldu ve %.2f saniye surdu.\n", n, count, *solved_time3);
	free(used);
	free(sutunlar);
}

/*
@brief brute_force ��z�m y�ntemini �al��t�r�r ve ekrana toplam ka� ��z�m oldu�unu ve toplam �al��ma s�resini yazd�r�r.
@param n kullan�c�dan al�nan vezir say�s�
@param solved_time1 y�ntemin �al��ma s�resi
*/
void brute_force(int n,double *solved_time1) {
    int count = 0, i, j,k;
    char **board=NULL;
    clock_t start, end;
    double solved_time;

    int *satirlar = (int *)malloc(n * sizeof(int));
    int *sutunlar = (int *)malloc(n * sizeof(int));
    int **cozumler = NULL; // Ba�lang��ta NULL atanmal�

    start = clock();
    brute_force_helper1(0, n, satirlar, &count, sutunlar, &cozumler);
    
    // Tahta i�in bellek tahsis et
    board = (char **)malloc(n * sizeof(char *));
    for (i = 0; i < n; i++) {
        board[i] = (char *)malloc(n * sizeof(char));
        for (j = 0; j < n; j++) {
            board[i][j] = '.';
        }
    }
    
    // ��z�mleri yazd�r ve tahta �zerinde g�ster
    if (count > 0) {
        printf("%d adet cozum bulundu:\n", count);
        for (i = 0; i < count; i++) {
        	printf("\n");   
        	printf("\n");			     	
            // Her ��z�m i�in tahtay� g�ncelle
            for (j = 0; j < n; j++) {
                board[cozumler[i * 2][j]][cozumler[i * 2 + 1][j]] = 'Q';
            }

            // Tahtay� yazd�r
            for (k = 0; k < n; k++) {
                for (j = 0; j < n; j++) {
                    printf("%c", board[k][j]);
                }
                printf("\n");
            }
            //printf("\n");
            
            printf("Cozum %d: ", i + 1);
            for (j = 0; j < n; j++) {
               	printf("(%d,%d) ", cozumler[i * 2][j], cozumler[i * 2 + 1][j]);
            }
			
            // Tahtay� temizle
            for (j = 0; j < n; j++) {
                board[cozumler[i * 2][j]][cozumler[i * 2 + 1][j]] = '.';
            }
        }
    } else {
        printf("Cozum bulunamadi.\n");
    }

    end = clock();

    *solved_time1 = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nn=%d icin BRUTE FORCE yontemi %d cozum buldu ve %.2f saniye surdu.\n", n, count, *solved_time1);

    // Belle�i serbest b�rak
    for (i = 0; i < count * 2; i++) {
        free(cozumler[i]);
    }
    free(cozumler);
    free(satirlar);
    free(sutunlar);
}

/*
@brief backtracking ��z�m y�ntemini �al��t�r�r ve ekrana toplam ka� ��z�m oldu�unu ve toplam �al��ma s�resini yazd�r�r.
@param n kullan�c�dan al�nan vezir say�s�
@param solved_time4 y�ntemin �al��ma s�resi
*/
void backtracking(int n,double *solved_time4) {
    int count = 0, i, j,k;
    char **board=NULL;
    clock_t start, end;

    int *sutunlar = (int *)malloc(n * sizeof(int));
    int **cozumler = NULL; // Ba�lang��ta NULL atanmal�

    start = clock();
    
     // Tahta i�in bellek tahsis et
    sutunlar = malloc(n * sizeof(int));
    if (sutunlar == NULL) {
        printf("Bellek tahsis hatas�!\n");
        return;
    }
    
    backtracking_helper(sutunlar, 0, n, &cozumler,&count);

	// Tahta i�in bellek tahsis et
    board = (char **)malloc(n * sizeof(char *));
    for (i = 0; i < n; i++) {
        board[i] = (char *)malloc(n * sizeof(char));
        for (j = 0; j < n; j++) {
            board[i][j] = '.';
        }
    }

    // ��z�mleri yazd�r ve tahta �zerinde g�ster
    if (count > 0) {
        printf("%d adet cozum bulundu:\n", count);
        for (i = 0; i < count; i++) {
        	printf("\n");   
        	printf("\n");			     	
            // Her ��z�m i�in tahtay� g�ncelle
            for (j = 0; j < n; j++) {
                board[j][cozumler[i][j]] = 'Q';
            }

            // Tahtay� yazd�r
            for (k = 0; k < n; k++) {
                for (j = 0; j < n; j++) {
                    printf("%c", board[k][j]);
                }
                printf("\n");
            }
            //printf("\n");
            
            printf("Cozum %d: ", i + 1);
            for (j = 0; j < n; j++) {
               	printf("(%d,%d) ", j, cozumler[i][j]);
            }
			
            // Tahtay� temizle
            for (j = 0; j < n; j++) {
                board[j][cozumler[i][j]] = '.';
            }

            free(cozumler[i]); // ��z�m belle�ini serbest b�rak
        }
    } else {
        printf("Cozum bulunamadi.\n");
    }
    
    end = clock();

    *solved_time4 = (double)(end - start) / CLOCKS_PER_SEC;
	printf("\n\n");
    printf("\nn=%d icin Backtracking yontemi %d cozum buldu ve %.2f saniye surdu.\n", n, count, *solved_time4);

	 // Belle�i temizle
    for (i = 0; i < n; i++) {
        free(board[i]);
    }
    free(cozumler);
    free(sutunlar);
}

/*
@brief t�m modlar� s�ras�yla �al��t�r�r ve ekrana �al��ma s�relerini yazd�r�r.
@param n kullan�c�dan al�nan vezir say�s�
@param solved_time1 Brute Force modunun �al��ma s�resi
@param solved_time2 Optimized_1 modunun �al��ma s�resi
@param solved_time3 Optimized_2 modunun �al��ma s�resi
@param solved_time4 Backtracking modunun �al��ma s�resi
*/
void run_all_modes(int n,double *solved_time1,double *solved_time2,double *solved_time3,double *solved_time4){
	double toplam;
	brute_force(n,solved_time1);
	optimized_1(n,solved_time2);
	optimized_2(n,solved_time3);
	backtracking(n,solved_time4);
	toplam=*solved_time1+*solved_time2+*solved_time3+*solved_time4;
	printf("Brute Force:%.2f\nOptimized_1:%.2f\nOptimized_2:%.2f\nBacktracking:%.2f\nToplam:%.2f",*solved_time1,*solved_time2,*solved_time3,*solved_time4,toplam);
}

int main(){
	int mode,n;
	double solved_time1,solved_time2,solved_time3,solved_time4;
	printf("0-Brute Force\n1-Optimized_1\n2-Optimized_2\n3-Backtracking\n4-Hepsi\nModunuzu seciniz.\n");
	do{
		scanf("%d",&mode);
	}while(mode>4 || mode<-1);
	
	printf("Boyut yani n degerini giriniz.\n");
	scanf("%d",&n);
	
	switch (mode) {
        case 0:
            brute_force(n,&solved_time1);
            break;
        case 1:
            optimized_1(n,&solved_time2);
            break;
        case 2:
            optimized_2(n,&solved_time3);
            break;
        case 3:
            backtracking(n,&solved_time4);
            break;
        case 4:
            run_all_modes(n,&solved_time1,&solved_time2,&solved_time3,&solved_time4);
            break;
        default:
            printf("Gecersiz mod.\n");
    }

	
	return 0;
}
