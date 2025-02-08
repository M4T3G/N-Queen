#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/*
@brief recursive bir þekilde iç içe n tane for döngüsü oluþturur ve her bir for bir vezirimizi temsil eder.
@param derinlik kaçýncý for içinde olduðumuzu ifade eder. yani kaçýncý vezirle iþlem yaptýðýmýzý söyler.
@param n kullanýcýdan alýnan vezir sayýsý
@param sutunlar her bir gözü bir vezirin satýrýný ifade eder ve o gözdeki deðer ise sütundaki yerini gösterir.
@param count toplam çözüm sayýsýný tutar.
*/
void optimized_1_helper(int derinlik, int n, int sutunlar[],int *count) {
	int i=0,j,flag=1;
	char **board;
    if (derinlik == n) { // En içteki döngüye ulaþtýysak
        while(i<n-1 && flag){ 
        	j=i+1;
        	while(j<n && flag){
        		if(sutunlar[i]==sutunlar[j] || abs(sutunlar[i] - sutunlar[j]) == abs(i - j)){  // Tüm vezirler ayný sütundalar mý ve çaprazlar mý kontrolü
        			flag=0; //Eðer öylelerse 
				}
				j++;
			}
			i++;
		}
		if(flag==1){  //Çözüm þartýný karþýlýyor.
			(*count)++; //Toplam çözüm sayýsýný 1 artýr.
			// Tahta için bellek tahsis et
    		board = (char **)malloc(n * sizeof(char *));
    		for (i = 0; i < n; i++) {
        	board[i] = (char *)malloc(n * sizeof(char));
        		for (j = 0; j < n; j++) {
        	   		board[i][j] = '.';   //satranç tahtasýnda boþ gözleri . ile ifade et
        		}
    		}
			for (j = 0; j < n; j++) {
            	board[j][sutunlar[j]] = 'Q';   //satranç tahtasýnda dolu gözleri Q ile ifade et
        	}
        	// Tahtayý yazdýr
        	for (i = 0; i < n; i++) {
            	for (j = 0; j < n; j++) {
                	printf("%c", board[i][j]);  //Tahtayý yazdýr.
            	}
            	printf("\n");
        	}
        	printf("Cozum %d: ", *count);
        	for (j = 0; j < n; j++) {
            	printf("(%d,%d) ", j,sutunlar[j]);  //Çözümlerin sýrasýyla satýr ve sütün numarasýný yazdýr.
        	}		
        	printf("\n");
        	printf("\n");
        	//Tabloyu serbest býrak.
        	for(i=0;i<n;i++){
				free(board[i]);
			}
			free(board);
		}
        return;
    }

    for ( i = 0; i < n; i++) {
        sutunlar[derinlik] = i; //Vezirin o anki yerini ata.
        optimized_1_helper(derinlik + 1, n, sutunlar,count); // Bir sonraki derinliðe in
    }
}

/*
@brief recursive bir þekilde iç içe n tane for döngüsü oluþturur ve her bir for bir vezirimizi temsil eder.
@param depth kaçýncý for içinde olduðumuzu ifade eder. yani kaçýncý vezirle iþlem yaptýðýmýzý söyler.
@param n kullanýcýdan alýnan vezir sayýsý
@param sutunlar her bir gözü bir vezirin satýrýný ifade eder ve o gözdeki deðer ise sütundaki yerini gösterir.
@param count toplam çözüm sayýsýný tutar.
@param used bu dizi her bir gözü sütunun numarasýný ifade eder. içindeki deðer ise o sütunda vezir varsa 1 yoksa 0 .
*/
void optimized_2_helper(int n, int depth, int used[], int sutunlar[],int *count) {
	int i=0,j,flag=1;
	char **board;
    if (depth == n) { // Tüm elemanlar yerleþtirildi
        while(i<n-1 && flag){
        	j=i+1;
        	while(j<n && flag){
        		if(abs(sutunlar[i] - sutunlar[j]) == abs(i - j)){  //// Tüm vezirler çaprazlar mý kontrolü
        			flag=0;
				}
				j++;
			}
			i++;
		}
		if(flag==1){ //Þartý karþýladý
			(*count)++;  //Toplam çözüm sayýsýný 1 artýr.
			// Tahta için bellek tahsis et
    		board = (char **)malloc(n * sizeof(char *));
    		for (i = 0; i < n; i++) {
        	board[i] = (char *)malloc(n * sizeof(char));
        		for (j = 0; j < n; j++) {
        	   		board[i][j] = '.';  //satranç tahtasýnda boþ gözleri . ile ifade et
        		}
    		}
			for (j = 0; j < n; j++) {
            	board[j][sutunlar[j]] = 'Q';  //satranç tahtasýnda dolu gözleri Q ile ifade et
        	}
        	// Tahtayý yazdýr
        	for (i = 0; i < n; i++) {
            	for (j = 0; j < n; j++) {
                	printf("%c", board[i][j]);  //Tahtayý yazdýr.
            	}
            	printf("\n");
        	}
        	printf("Cozum %d: ", *count);
        	for (j = 0; j < n; j++) {
            	printf("(%d,%d) ", j,sutunlar[j]); //Çözümlerin sýrasýyla satýr ve sütün numarasýný yazdýr.
        	}		
        	printf("\n");
        	printf("\n");
        	//Tabloyu serbest býrak.
        	for(i=0;i<n;i++){
				free(board[i]);
			}
			free(board);
		}
        return;
    }

    for (i = 0; i < n; i++) { // Her eleman için döngü
        if (!used[i]) { // Daha önce kullanýlmamýþ elemanlarý kontrol et
            used[i] = 1; // Elemaný iþaretle (kullanýldý)
            sutunlar[depth] = i; // Elemaný permütasyona ekle
            optimized_2_helper(n, depth + 1, used, sutunlar,count); // Bir sonraki seviyeye geç
            used[i] = 0; // Geri dönüþ (backtrack) için elemaný serbest býrak
        }
    }
}

/*
@brief çözümler matrisindeki çözümler ile o anda çözüm adayý deðerleri kýyaslar ve birbirinden farklý ise çözümler matrisine ekler.
@param satirlar vezirlerin bulunduðu satýr indisini tutar.
@param n kullanýcýdan alýnan vezir sayýsý
@param sutunlar vezirlerin bulunduðu sütun indisini tutar.
@param count toplam çözüm sayýsýný tutar.
@param cozumler bu matris count deðerindeki satýra çözümün satýrlarýný, count +1 satýrýna çözümün sütunlarýný atar.
*/
void tekrar_kontrol(int n, int sutunlar[], int *count, int satirlar[], int ***cozumler) {
    int i, j,k, eslesme = 0;

    if (*count == 0) {
        // Ýlk çözüm bulunursa belleði ayýr
        *cozumler = (int **)malloc(2 * sizeof(int *));
        for (i = 0; i < 2; i++) {
            (*cozumler)[i] = (int *)malloc(n * sizeof(int));
        }
        for (i = 0; i < n; i++) {
            (*cozumler)[0][i] = satirlar[i];  //Çözümün satýrlarýný cozumler tablosunun ilk satýrýna ekle.
            (*cozumler)[1][i] = sutunlar[i];  //Çözümün sütunlarýný cozumler tablosunun ikinci satýrýna ekle. Yani tablo boyutu=count*2
        }
        (*count)++;  //Toplam çözüm sayýsýný artýr.
    } else {
        for (i = 0; i < (*count) * 2; i += 2) {  //Çözüm tablosunu gez.
            for (j = 0; j < n; j++) {  // Çözüm adayýnýn satýrlarýný gez.
            	for(k=0;k<n;k++){  //Çözüm adayýnýn sütunlarýný gez.
            		if ((*cozumler)[i][k] == satirlar[j] && (*cozumler)[i + 1][k] == sutunlar[j]) //Çözüm adayýnýn önceki tüm çözümlerle herhangi bir satýr ve sütun sayýsý ayný olursa
                    eslesme++;  //bu deðiþken bir artýr.
				}
            }
            if (eslesme == n) return; // Çözüm daha önce kaydedilmiþ. Ayný çözüm var zaten tabloda.s
            eslesme = 0;
        }

        // Yeni çözümü kaydetmek için belleði geniþlet
        *cozumler = (int **)realloc(*cozumler, ((*count) * 2 + 2) * sizeof(int *));
        for (i = (*count) * 2; i < ((*count) * 2 + 2); i++) {
            (*cozumler)[i] = (int *)malloc(n * sizeof(int));
        }

        for (j = 0; j < n; j++) {
            (*cozumler)[(*count) * 2][j] = satirlar[j];  //Yeni çözümün satýrlarýný tabloya ekle.
            (*cozumler)[(*count) * 2 + 1][j] = sutunlar[j]; //Yeni çözümün sutunlarýný tabloya ekle.
        }
        (*count)++;  //Toplam çözüm sayýsýný artýr.
    }
}

/*
@brief recursive þekilde vezirlerin sütunlarýný deðiþtirerek çözüm olma ihtimallerini deðerlendirir.
@param derinlik kaçýncý for içinde olduðumuzu ifade eder. yani kaçýncý vezirle iþlem yaptýðýmýzý söyler.
@param satirlar vezirlerin bulunduðu satýr indisini tutar.
@param n kullanýcýdan alýnan vezir sayýsý
@param sutunlar vezirlerin bulunduðu sütun indisini tutar.
@param count toplam çözüm sayýsýný tutar.
@param cozumler bu matris count deðerindeki satýra çözümün satýrlarýný, count +1 satýrýna çözümün sütunlarýný atar.
*/
void brute_force_helper2(int derinlik, int n, int sutunlar[], int *count, int satirlar[],int ***cozumler) {
    int i, j, flag;

    if (derinlik == n) { // Tüm sütunlar yerleþti
        flag = 1;
        for (i = 0; i < n - 1 && flag; i++) {
            for (j = i + 1; j < n && flag; j++) {
                // Çakýþma kontrolü: Ayný sütun, ayný satýr veya çapraz
                if (sutunlar[i] == sutunlar[j] || 
                    satirlar[i] == satirlar[j] || 
                    abs(sutunlar[i] - sutunlar[j]) == abs(satirlar[i] - satirlar[j])) {
                    flag = 0; // Çakýþma bulundu
                }
            }
        }

        if (flag) { //Çakýþma yoksa çözüm adayý olur.
            tekrar_kontrol(n, sutunlar, count, satirlar,cozumler);
        }
        return;
    }

    for (i = 0; i < n; i++) { // Sütunlarý sýrayla dene
        sutunlar[derinlik] = i;
        brute_force_helper2(derinlik + 1, n, sutunlar, count, satirlar,cozumler);
    }
}

/*
@brief recursive þekilde vezirlerin satýrlarýný deðiþtirerek çözüm olma ihtimallerini deðerlendirir.
@param derinlik kaçýncý for içinde olduðumuzu ifade eder. yani kaçýncý vezirle iþlem yaptýðýmýzý söyler.
@param satirlar vezirlerin bulunduðu satýr indisini tutar.
@param n kullanýcýdan alýnan vezir sayýsý
@param sutunlar vezirlerin bulunduðu sütun indisini tutar.
@param count toplam çözüm sayýsýný tutar.
@param cozumler bu matris count deðerindeki satýra çözümün satýrlarýný, count +1 satýrýna çözümün sütunlarýný atar.
*/
void brute_force_helper1(int derinlik, int n, int satirlar[], int *count, int sutunlar[],int ***cozumler) {
    int i;

    if (derinlik == n) { // Tüm satýrlar yerleþti
        brute_force_helper2(0, n, sutunlar, count, satirlar,cozumler);
        return;
    }

    for (i = 0; i < n; i++) { // Satýrlarý sýrayla dene
        satirlar[derinlik] = i;
        brute_force_helper1(derinlik + 1, n, satirlar, count, sutunlar,cozumler);
    }
}


/*
@brief Tahtanýn üzerindeki bir sütunun güvenli olup olmadýðýný kontrol eder.
@param sütunlar çözüm adayý. her bir gözü bir vezirin satýrýný ifade eder ve o gözdeki deðer ise sütundaki yerini gösterir.
@param row ilgili satýr deðeri
@param ilgili sutun deðeri
@return Eðer tabloya yerleþtirilmeye uygunsa 1 deðilse 0 döndürür.
*/
int isSafe(int sutunlar[], int row, int col) {
	int i;
    for (i = 0; i < row; i++) {
        // Ayný sütunda veya çaprazda bir vezir varsa
        if (sutunlar[i] == col || abs(sutunlar[i] - col) == abs(i - row)) {
            return 0;
        }
    }
    return 1;
}


/*
@brief recursive þekilde vezirlerin sütunlarýný deðiþtirerek çözüm olma ihtimallerini deðerlendirir.
@param row hangi satýrda iþlem yaptýðýmýz bilgisini tutar.
@param n kullanýcýdan alýnan vezir sayýsý
@param sutunlar her bir gözü bir vezirin satýrýný ifade eder ve o gözdeki deðer ise sütundaki yerini gösterir.
@param count toplam çözüm sayýsýný tutar.
@param cozumler bu matris çözümlerin sütundaki yerlerini tutar.
*/
void backtracking_helper(int sutunlar[], int row, int n, int ***cozumler,int *count) {
	int i,col;
    // Tüm vezirler yerleþtirildiyse çözümü kaydet
    if (row == n) {
        (*count)++;

    	// Ýlk çözüm için veya mevcut alaný geniþletmek için realloc
    	(*cozumler) = realloc((*cozumler), (*count) * sizeof(int *));

    	// Yeni çözüm için alan ayýr
    	(*cozumler)[(*count) - 1] = malloc(n * sizeof(int));

    	// Çözümü çözüm tablosuna ekleme
    	for (i = 0; i < n; i++) {
    	    (*cozumler)[(*count) - 1][i] = sutunlar[i];
    	}
    	    return;
    }

    	// Sýradaki satýrda her sütun için kontrol et
   	for (col = 0; col < n; col++) {
        if (isSafe(sutunlar, row, col)) {
            sutunlar[row] = col; // Veziri bu sütuna yerleþtir
            backtracking_helper(sutunlar, row + 1, n,cozumler,count); // Sonraki satýra geç
        }
    }
}

/*
@brief optimized_1 çözüm yöntemini çalýþtýrýr ve ekrana toplam kaç çözüm olduðunu ve toplam çalýþma süresini yazdýrýr.
@param n kullanýcýdan alýnan vezir sayýsý
@param solved_time2 yöntemin çalýþma süresi
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
@brief optimized_2 çözüm yöntemini çalýþtýrýr ve ekrana toplam kaç çözüm olduðunu ve toplam çalýþma süresini yazdýrýr.
@param n kullanýcýdan alýnan vezir sayýsý
@param solved_time3 yöntemin çalýþma süresi
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
@brief brute_force çözüm yöntemini çalýþtýrýr ve ekrana toplam kaç çözüm olduðunu ve toplam çalýþma süresini yazdýrýr.
@param n kullanýcýdan alýnan vezir sayýsý
@param solved_time1 yöntemin çalýþma süresi
*/
void brute_force(int n,double *solved_time1) {
    int count = 0, i, j,k;
    char **board=NULL;
    clock_t start, end;
    double solved_time;

    int *satirlar = (int *)malloc(n * sizeof(int));
    int *sutunlar = (int *)malloc(n * sizeof(int));
    int **cozumler = NULL; // Baþlangýçta NULL atanmalý

    start = clock();
    brute_force_helper1(0, n, satirlar, &count, sutunlar, &cozumler);
    
    // Tahta için bellek tahsis et
    board = (char **)malloc(n * sizeof(char *));
    for (i = 0; i < n; i++) {
        board[i] = (char *)malloc(n * sizeof(char));
        for (j = 0; j < n; j++) {
            board[i][j] = '.';
        }
    }
    
    // Çözümleri yazdýr ve tahta üzerinde göster
    if (count > 0) {
        printf("%d adet cozum bulundu:\n", count);
        for (i = 0; i < count; i++) {
        	printf("\n");   
        	printf("\n");			     	
            // Her çözüm için tahtayý güncelle
            for (j = 0; j < n; j++) {
                board[cozumler[i * 2][j]][cozumler[i * 2 + 1][j]] = 'Q';
            }

            // Tahtayý yazdýr
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
			
            // Tahtayý temizle
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

    // Belleði serbest býrak
    for (i = 0; i < count * 2; i++) {
        free(cozumler[i]);
    }
    free(cozumler);
    free(satirlar);
    free(sutunlar);
}

/*
@brief backtracking çözüm yöntemini çalýþtýrýr ve ekrana toplam kaç çözüm olduðunu ve toplam çalýþma süresini yazdýrýr.
@param n kullanýcýdan alýnan vezir sayýsý
@param solved_time4 yöntemin çalýþma süresi
*/
void backtracking(int n,double *solved_time4) {
    int count = 0, i, j,k;
    char **board=NULL;
    clock_t start, end;

    int *sutunlar = (int *)malloc(n * sizeof(int));
    int **cozumler = NULL; // Baþlangýçta NULL atanmalý

    start = clock();
    
     // Tahta için bellek tahsis et
    sutunlar = malloc(n * sizeof(int));
    if (sutunlar == NULL) {
        printf("Bellek tahsis hatasý!\n");
        return;
    }
    
    backtracking_helper(sutunlar, 0, n, &cozumler,&count);

	// Tahta için bellek tahsis et
    board = (char **)malloc(n * sizeof(char *));
    for (i = 0; i < n; i++) {
        board[i] = (char *)malloc(n * sizeof(char));
        for (j = 0; j < n; j++) {
            board[i][j] = '.';
        }
    }

    // Çözümleri yazdýr ve tahta üzerinde göster
    if (count > 0) {
        printf("%d adet cozum bulundu:\n", count);
        for (i = 0; i < count; i++) {
        	printf("\n");   
        	printf("\n");			     	
            // Her çözüm için tahtayý güncelle
            for (j = 0; j < n; j++) {
                board[j][cozumler[i][j]] = 'Q';
            }

            // Tahtayý yazdýr
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
			
            // Tahtayý temizle
            for (j = 0; j < n; j++) {
                board[j][cozumler[i][j]] = '.';
            }

            free(cozumler[i]); // Çözüm belleðini serbest býrak
        }
    } else {
        printf("Cozum bulunamadi.\n");
    }
    
    end = clock();

    *solved_time4 = (double)(end - start) / CLOCKS_PER_SEC;
	printf("\n\n");
    printf("\nn=%d icin Backtracking yontemi %d cozum buldu ve %.2f saniye surdu.\n", n, count, *solved_time4);

	 // Belleði temizle
    for (i = 0; i < n; i++) {
        free(board[i]);
    }
    free(cozumler);
    free(sutunlar);
}

/*
@brief tüm modlarý sýrasýyla çalýþtýrýr ve ekrana çalýþma sürelerini yazdýrýr.
@param n kullanýcýdan alýnan vezir sayýsý
@param solved_time1 Brute Force modunun çalýþma süresi
@param solved_time2 Optimized_1 modunun çalýþma süresi
@param solved_time3 Optimized_2 modunun çalýþma süresi
@param solved_time4 Backtracking modunun çalýþma süresi
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
