#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 30

// func that mimics strcpy
void copy(char* a, char* b );

//func that mimics strlen
int lengthof(char* a);


// func that changes board, keeping in mind the spaces between words.
int cboard(char* board, char* word, char letter);


// func that prints the hangman


//func that checks if letter in word. Then, it changes board using cboard. 
int checkletter(char letter, char* word);

//makes capital letters lowercase or the opposite
char changecase(char letter);



// func that prints a line with 20 =
void grammi();


//func that returns a random word from an array of strings
char *chosen_word( char* capitals[], int * used_numbers);


//func pou elegxei an o arithmos exei janaxrisimopoihthei. AN oxi tote ton vazei sto array used_numbers
//xrisi mono apo chosen_word
int num_already_used(int num, int *used_numbers);

//idia me thn proigoumeni apla gia chars
int letter_already_used(char letter, char *used_letters);


int check_spaces(int i, char *capital);


// tsekarei an to onoma pou pliktrologise o xristis einai egkyro (mexri N -1)
int nameIsValid(char *name);


//tsekarei an to gramma pou edwse o xristis einai gramma kai oxi symvolo i arithmos
int charIsValid(char letter);



int main() {

    // array of strings me oles tis proteuouses 
        char *capitals[] = {
        "Amsterdam", "Andorra la Vella", "Ankara", "Athens", "Belgrade", "Berlin", "Bern",
        "Bratislava", "Brussels", "Bucharest", "Budapest", "Chisinau", "Copenhagen", "Dublin",
        "Helsinki", "Kyiv", "Lisbon", "Ljubljana", "London", "Luxembourg City", "Madrid", "Minsk",
        "Monaco", "Moscow", "Nicosia", "Oslo", "Paris", "Podgorica", "Prague", "Pristina",
        "Reykjavik", "Riga", "Rome", "San Marino", "Sarajevo", "Skopje", "Sofia", "Stockholm",
        "Tallinn", "Tbilisi", "Tirana", "Vaduz", "Valletta", "Vatican City", "Vienna", "Vilnius",
        "Warsaw", "Yerevan", "Zagreb"
    };


    //used numbers, diladi oi tyxaioi arithmoi pou exoun xrisimopoihthei kai pou antistoixoun
    //se mia thesi tou pinaka capitals
    int used_numbers[3] = {};

    printf("==========ΚΡΕΜΑΛΑ==========\nΚΑΛΩΣΟΡΙΣΑΤΕ! ΠΛΗΚΤΡΟΛΟΓΗΣΤΕ ΤΟ ΟΝΟΜΑ ΣΑΣ: ");
    char name[N];
    
    do {
    int res = scanf("%s", name);
    if (res != 1) exit(1);
    }while(!nameIsValid(name));
    
    char letter;
    int found_words = 0;
    char word[N] = {};
    char board[N];
    int lives = 10;
    




     while (found_words<3 &&lives !=0) {
        



        
        //pinakas me used letters
        char usedletters[N] = {};
        
        int pavles =0;
        int i;
        // otan oi pavles ginetai 0, tote o xristis exei vrei tin lexi kai ara synexizei me tis epomenes
        
        //a word is chosen randomly
        copy(word, chosen_word(capitals, used_numbers));
        int num_of_spaces = 0;
        int len = lengthof(word);
        for ( i = 0; i<len; i++) {
            if (check_spaces(i, word)) {
                board[i] = ' ';
                num_of_spaces++;
            }
            else  board[i] = '_';
            board[i+1] = '\0';
        }
        pavles = i - num_of_spaces;
        
    

        while (lives!=0 && pavles) {
            printf("%s\n", board);
            printf("%d\n", pavles);
            

            printf("ΜΑΝΤΕΨΕ ΕΝΑ ΓΡΑΜΜΑ!\n");
            printf("ΖΩΕΣ: %d\n", lives);
            //user input
            do {
               int res = scanf(" %1c", &letter);
               if (res != 1) exit(1);
            }while(letter_already_used(letter, usedletters));
            

            int cond = cboard(board, word, letter);
            pavles -= cond;
            if(cond > 0) {
            printf("ΕΥΓΕ %s! ΤΟ ΓΡΑΜΜΑ ΣΟΥ ΗΤΑΝ ΣΤΗ ΛΕΞΗ %d %s!!!\n", name, cond, (cond>1)?"ΦΟΡΕΣ":"ΦΟΡΑ");

           }
           else if (cond == 0) {
            lives--;
            printf("ΛΥΠΑΜΑΙ %s, ΤΟ ΓΡΑΜΜΑ  %c ΔΕΝ ΥΠΑΡΧΕΙ ΣΤΗΝ ΛΕΞΗ...\n", name, letter);
            }
            
           if (pavles == 0) {
            printf("ΣΥΓΧΑΡΗΤΗΡΙΑ %s ΒΡΗΚΕΣ ΤΗΝ ΛΕΞΗ %s!!!\n", name, word);
            grammi();
            found_words++;
            lives = 10;
           }
           if (lives == 0) printf("ΛΥΠΑΜΑΙ, ΕΧΑΣΕΣ...\nΗ ΛΕΞΗ ΗΤΑΝ %s\n", word);

        }

    }
}


int lengthof(char* a) {
    int i=0;
    while (a[i] != '\0') {
        i++;
    }
   return i;
}

void copy(char*a, char*b) {
    int i = 0;
    while (b[i] != '\0') {
        a[i] = b[i];
        i++;
    }
    a[i] = '\0';
}



char changecase(char letter){
    if (letter >= 97) letter -= 32;
    else if (letter>=65) letter += 32;
    return letter;

}

int cboard(char* board, char * word, char letter) {

    int a =0;



    for (int i = 0; i<lengthof(word); i++) {
        if (letter == word[i] || changecase(letter) == word[i]) {

            board[i] = word[i];
            a++;

    
        }
    }
    return a;

}

void grammi() {
    for (int i=0; i<50; i++) printf("%c", '=');
    printf("\n");
}


int check_spaces(int i,char *capital) {
   return (capital[i] == ' ')? 1 : 0;
    
}
char * chosen_word(  char* capitals[], int *used_numbers){
    int num;
    srand(time(NULL));
    do{
    num = (rand() %49);
    }while (num_already_used(num, used_numbers));


    return capitals[num];

    
    


}

int letter_already_used(char letter, char* used_letters) {
    static int length = 0;
    int a =0;
    int i;

    if (!charIsValid(letter)) return 1;
   
    if (length == 0 ){
        used_letters[0] = letter;
        length ++;
        return a;
    }
    for (i =0; i<length; i++) {
        if (letter == used_letters[i] || changecase(letter) == used_letters[i]){
             a = 1;
             printf("ΤΟ ΓΡΑΜΜΑ ΑΥΤΟ ΤΟ ΕΧΕΙΣ ΗΔΗ ΓΡΑΨΕΙ! ΞΑΝΑΠΡΟΣΠΑΘΗΣΕ! \n");
             break;

        }
    }
    if (a==0) {
    used_letters[i] = letter;
    length++;
    }
    return a;
    }



int num_already_used(int num, int *used_numbers){
    static int length = 0;
    int a =0;
    int i;
    if (length == 0 ){
        used_numbers[0] = num;
        length ++;
        return a;
    }
    for (i =0; i<length; i++) {
        if (num == used_numbers[i]){
             a = 1;
             
             break;

        }
    }
    if (a==0) {used_numbers[i] = num;
    length++;
    }
    return a;
    }


 int nameIsValid(char *name) {
        if ( lengthof(name) >= N ) {
            printf("ΠΟΛΥ ΜΕΓΑΛΟ ΟΝΟΜΑ! ΠΛΗΚΤΡΟΛΟΓΗΣΤΕ ΟΝΟΜΑ ΤΟ ΠΟΛΥ %d ΧΑΡΑΚΤΗΡΩΝ: ", N -1);
            return 0;
            

        }
        return 1;
    }
   
    
int charIsValid(char letter) {
    if ( (letter >= 'A' && letter <= 'Z') || (letter >= 'a' && letter <='z') ){
        return 1;

    }
    printf("ΜΗ ΕΠΙΤΡΕΠΤΟΣ ΧΑΡΑΚΤΗΡΑΣ! ΠΑΡΑΚΑΛΩ ΠΛΗΚΤΡΟΛΟΓΗΣΤΕ ΜΟΝΟ ΛΑΤΙΝΙΚΑ ΓΡΑΜΜΑΤΑ (ΚΕΦΑΛΑΙΑ Η ΜΙΚΡΑ)!\n");
    return 0;

    
}
